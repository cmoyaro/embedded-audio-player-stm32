################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TOUCHSENSING/App/stmCriticalSection.c \
../TOUCHSENSING/App/touchsensing.c \
../TOUCHSENSING/App/tsl_user.c 

OBJS += \
./TOUCHSENSING/App/stmCriticalSection.o \
./TOUCHSENSING/App/touchsensing.o \
./TOUCHSENSING/App/tsl_user.o 

C_DEPS += \
./TOUCHSENSING/App/stmCriticalSection.d \
./TOUCHSENSING/App/touchsensing.d \
./TOUCHSENSING/App/tsl_user.d 


# Each subdirectory must supply rules for building sources it contributes
TOUCHSENSING/App/%.o TOUCHSENSING/App/%.su TOUCHSENSING/App/%.cyclo: ../TOUCHSENSING/App/%.c TOUCHSENSING/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../TOUCHSENSING/App -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_TouchSensing_Library/inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TOUCHSENSING-2f-App

clean-TOUCHSENSING-2f-App:
	-$(RM) ./TOUCHSENSING/App/stmCriticalSection.cyclo ./TOUCHSENSING/App/stmCriticalSection.d ./TOUCHSENSING/App/stmCriticalSection.o ./TOUCHSENSING/App/stmCriticalSection.su ./TOUCHSENSING/App/touchsensing.cyclo ./TOUCHSENSING/App/touchsensing.d ./TOUCHSENSING/App/touchsensing.o ./TOUCHSENSING/App/touchsensing.su ./TOUCHSENSING/App/tsl_user.cyclo ./TOUCHSENSING/App/tsl_user.d ./TOUCHSENSING/App/tsl_user.o ./TOUCHSENSING/App/tsl_user.su

.PHONY: clean-TOUCHSENSING-2f-App

