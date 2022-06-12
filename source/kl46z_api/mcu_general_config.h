#ifndef MCU_GENERAL_CONFIG_H_
#define MCU_GENERAL_CONFIG_H_

/* TODO: insert other definitions and declarations here. */
#include <stdint.h>
#include "MKL46Z4.h"
#include "fsl_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup mcu_general_config
 * @{
 */


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!< If FreeRTOS is present, uncomment this macro.*/
//#define __FREERTOS_H

/*!< MCU specific port register type for write or read logic values in pins.*/
typedef GPIO_Type* portPinsRegister_t;
/*!< Mask type with the MCU ports width.*/
typedef uint32_t portPinMask_t;


/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief Set the port pins.
 *
 * @param portPinsRegister - port register.
 * @param portPinMask      - pin mask, bits equal 1 set the correspondingly pin.
 *
 */
#define MCU_PortSet(portPinsRegister, portPinMask) portPinsRegister->PSOR = portPinMask;


/**
 * @brief Clear the port pins.
 *
 * @param portPinsRegister - port register.
 * @param portPinMask      - pin mask, bits equal 1 clear the correspondingly pin.
 *
 */
#define MCU_PortClear(portPinsRegister, portPinMask) portPinsRegister->PCOR = portPinMask;

#ifdef __cplusplus
}  /* extern "C" */
#endif

/*! @}*/

#endif
