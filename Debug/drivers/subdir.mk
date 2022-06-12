################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_ftfx_cache.c \
../drivers/fsl_ftfx_controller.c \
../drivers/fsl_ftfx_flash.c \
../drivers/fsl_ftfx_flexnvm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_lpsci.c \
../drivers/fsl_sim.c \
../drivers/fsl_smc.c \
../drivers/fsl_tpm.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_ftfx_cache.o \
./drivers/fsl_ftfx_controller.o \
./drivers/fsl_ftfx_flash.o \
./drivers/fsl_ftfx_flexnvm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_lpsci.o \
./drivers/fsl_sim.o \
./drivers/fsl_smc.o \
./drivers/fsl_tpm.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_ftfx_cache.d \
./drivers/fsl_ftfx_controller.d \
./drivers/fsl_ftfx_flash.d \
./drivers/fsl_ftfx_flexnvm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_lpsci.d \
./drivers/fsl_sim.d \
./drivers/fsl_smc.d \
./drivers/fsl_tpm.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLH4 -DCPU_MKL46Z256VLH4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=0 -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/board" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/source" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/amazon-freertos/FreeRTOS/portable" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/freertos/portable" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/amazon-freertos/include" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/drivers" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/utilities" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/startup" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


