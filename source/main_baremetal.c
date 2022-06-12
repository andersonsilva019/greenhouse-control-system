#include "ProjectSelect.h"
#if PROJECT == 1

#include "MKL46Z4.h"

#include <stdio.h>

#include "kl46z_api/drivers.h"
#include "kl46z_api/gpio.h"
#include "kl46z_api/lcd.h"
#include "kl46z_api/delay.h"

const uint8_t lcd_degree_char[] = {
		0b00110,
		0b01001,
		0b00110,
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b00000
};

#define LCD_DEGREE_CHAR 0x00

static lcdConfig_t* lcd_config;
static lcdHandle_t lcd_handle;

void adcInitModule(void);

long adcReadInput(uint8_t channel);

void drvLedOk(void);

void drvLedError(void);

void lcdInitModule(void);

void lcdDisplayBootScreen(void);

void lcdDisplayHumidity(void);

void lcdDisplayTemperature(void);

int main (void) {

	__disable_irq();

	Delay_Init();

	drvCpuClockInit();
	drvLedInit();
	drvButtonInit();

	adcInitModule();
	lcdInitModule();

	lcdDisplayBootScreen();

	__enable_irq();

	drvLedOk();

	while (1) {
		lcdDisplayHumidity();
		lcdDisplayTemperature();
	}
}

void drvLedOk(void) {
	drvLedSet(DRV_LED_RED, DRV_LED_CLEAR);
	drvLedSet(DRV_LED_GREEN, DRV_LED_SET);
}

void drvLedError(void) {
	drvLedSet(DRV_LED_RED, DRV_LED_SET);
	drvLedSet(DRV_LED_GREEN, DRV_LED_CLEAR);
}

void lcdInitModule(void) {

	SIM->SCGC5     |= (1U << 10) | (1U << 13);

	PORTE->PCR[1]  |= (0b001U << 8); // PTE1 = RS
	PORTE->PCR[0]  |= (0b001U << 8); // PTE0 = EN

	PORTE->PCR[22]  |= (0b001U << 8); //PTE22 = D4
	PORTE->PCR[23]  |= (0b001U << 8); //PTE23 = D5
	PORTB->PCR[20]  |= (0b001U << 8); //PTB20 = D6
	PORTE->PCR[30]  |= (0b001U << 8); //PTE30 = D7

	GPIOE->PDDR |= (1U << 0) | (1U << 1) | (1U << 22) | (1U << 23) | (1U << 30);
	GPIOB->PDDR |= (1U << 20);

	lcd_config = LCD_CreateConfig();

	lcd_config->lines = 2;
	lcd_config->cols = 16;
	lcd_config->charsize = LCD_5x8DOTS;

	lcd_config->bus.rs.portRegister = GPIOE;
	lcd_config->bus.rs.pinMask =  (1U << 1);

	lcd_config->bus.en.portRegister = GPIOE;
	lcd_config->bus.en.pinMask =  (1U << 0);

	lcd_config->bus.data[0].portRegister = GPIOE;
	lcd_config->bus.data[0].pinMask =  (1U << 22);

	lcd_config->bus.data[1].portRegister = GPIOE;
	lcd_config->bus.data[1].pinMask =  (1U << 23);

	lcd_config->bus.data[2].portRegister = GPIOB;
	lcd_config->bus.data[2].pinMask =  (1U << 20);

	lcd_config->bus.data[3].portRegister = GPIOE;
	lcd_config->bus.data[3].pinMask =  (1U << 30);

	// INIT THE LCD WITH THE GIVEN CONFIG
	lcd_handle = LCD_Init(lcd_config);

	// CREATE THE DEGGRE SPECIAL CHAR
	LCD_CreateChar(lcd_handle, 0, lcd_degree_char);
}

void lcdDisplayBootScreen(void) {
	// DISPLAY THE BOOT SCREEN IN THE LCD
	LCD_Clear(lcd_handle);
	LCD_SetCursor(lcd_handle, 0, 0);
	LCD_WriteString(lcd_handle, "   Controle de");
	LCD_SetCursor(lcd_handle, 0, 1);
	LCD_WriteString(lcd_handle, "   Estufa v1.1");
	Delay_Waitms(3000);
}

void lcdDisplayHumidity(void) {
	// GET HUMIDITY FROM SENSOR
	int humidity = 100 - (adcReadInput(0) / 65535.0) * 100;

	// CONVERT THE HUMIDITY TO INTEGER
	char humid_str[10];
	itoa(humidity, humid_str, 10);

	// DISPLAY THE HUMIDITY IN THE LCD
	LCD_Clear(lcd_handle);
    LCD_SetCursor(lcd_handle, 0, 0);
	LCD_WriteString(lcd_handle, "Umidade: ");
	LCD_WriteString(lcd_handle, humid_str);
	LCD_WriteString(lcd_handle, "%");
	Delay_Waitms(3000);
}

void lcdDisplayTemperature(void) {
	// GET TEMPERATURE FROM SENSOR
	int temperature = adcReadInput(9) * 330.0 / 65536.0;
	char temp_str[10];

	// CONVERT THE TEMPERATURE TO INTEGER
	itoa(temperature, temp_str, 10);

	// DISPLAY THE TEMPERATURE IN THE LCD
	LCD_Clear(lcd_handle);
    LCD_SetCursor(lcd_handle, 0, 0);
	LCD_WriteString(lcd_handle, "Temp. : ");
	LCD_WriteString(lcd_handle, temp_str);
	LCD_Write(lcd_handle, LCD_DEGREE_CHAR);
	LCD_WriteString(lcd_handle, "C");
	Delay_Waitms(3000);
}

void adcInitModule(void) {
	// ENABLE CLOCK TO PORTB AND PORTE
	SIM->SCGC5 |= (1 << 10) | (1 << 13);

	// TEMP. SENSOR IN PTE20 (ADC CHANNEL 0)
	PORTE->PCR[20] = 0;

	// TEMP. SENSOR IN PTB1 (ADC CHANNEL 9)
	PORTB->PCR[1] = 0;

	// ENABLE CLOCK TO ADC0
	SIM->SCGC6 |= (1U << 27);

	// SOFTWARE TRIGGER
	ADC0->SC2 &= ~(1U << 6);

	// AVERAGE OF 32 SAMPLES
	ADC0->SC3 |= (0b111 << 0);

	// CLOCK DIVIDED BY 4
	ADC0->CFG1 |= (0b10U << 5);

	// LONG SAMPLE TIME
	ADC0->CFG1 |= (1U << 4);

	// SINGLE ENDED 16-BITS
	ADC0->CFG1 |= (0b11U << 2);
}

long adcReadInput(uint8_t channel) {
	// START CONVERSION ON THE GIVEN CHANNEL
	ADC0->SC1[0] = channel;

	// WAIT FOR CONVERSION TO COMPLETE
	while(!(ADC0->SC1[0] & (1U << 7)));

	// READ CONVERSION RESULT AND CLEAR COCO FLAG
	return ADC0->R[0];
}
#endif
