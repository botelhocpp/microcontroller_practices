################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_smc.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_smc.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_smc.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_K32L2B31VLH0A -DCPU_K32L2B31VLH0A_cm0plus -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=0 -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/board" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/source" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/drivers" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/component/serial_manager" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/component/uart" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/utilities" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/component/lists" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/CMSIS" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


