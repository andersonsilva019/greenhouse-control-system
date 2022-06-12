################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c \
../utilities/fsl_io.c \
../utilities/fsl_log.c \
../utilities/fsl_str.c 

OBJS += \
./utilities/fsl_debug_console.o \
./utilities/fsl_io.o \
./utilities/fsl_log.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_debug_console.d \
./utilities/fsl_io.d \
./utilities/fsl_log.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL46Z256VLH4 -DCPU_MKL46Z256VLH4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DFSL_RTOS_FREE_RTOS -DSDK_OS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=0 -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/board" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/source" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/amazon-freertos/FreeRTOS/portable" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/freertos/portable" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/amazon-freertos/include" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/drivers" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/utilities" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/startup" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/Estufa-RTOS-KL46Z/CMSIS" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


