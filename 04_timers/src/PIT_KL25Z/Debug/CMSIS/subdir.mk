################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/system_MKL25Z4.c 

OBJS += \
./CMSIS/system_MKL25Z4.o 

C_DEPS += \
./CMSIS/system_MKL25Z4.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/%.o: ../CMSIS/%.c CMSIS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/pedrobotelho15/Área de Trabalho/Projetos com NXP/PIT_KL25Z/board" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com NXP/PIT_KL25Z/source" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com NXP/PIT_KL25Z" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com NXP/PIT_KL25Z/startup" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com NXP/PIT_KL25Z/CMSIS" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com NXP/PIT_KL25Z/drivers" -I"/home/pedrobotelho15/Área de Trabalho/Projetos com NXP/PIT_KL25Z/utilities" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


