################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/peripherals.c \
../board/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/peripherals.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/peripherals.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_K32L2B31VLH0A -DCPU_K32L2B31VLH0A_cm0plus -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=0 -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/board" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/source" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/drivers" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/component/serial_manager" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/component/uart" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/utilities" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/component/lists" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/CMSIS" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com K32L2B3/ADC_Practices/device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


