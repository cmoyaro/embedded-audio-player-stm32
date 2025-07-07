################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl.c \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq.c \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq_tsc.c \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl_dxs.c \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl_ecs.c \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl_filter.c \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl_globals.c \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl_linrot.c \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl_object.c \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl_time.c \
../Middlewares/ST/STM32_TouchSensing_Library/src/tsl_touchkey.c 

OBJS += \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl.o \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq.o \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq_tsc.o \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_dxs.o \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_ecs.o \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_filter.o \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_globals.o \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_linrot.o \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_object.o \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_time.o \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_touchkey.o 

C_DEPS += \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl.d \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq.d \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq_tsc.d \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_dxs.d \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_ecs.d \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_filter.d \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_globals.d \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_linrot.d \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_object.d \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_time.d \
./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_touchkey.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_TouchSensing_Library/src/%.o Middlewares/ST/STM32_TouchSensing_Library/src/%.su Middlewares/ST/STM32_TouchSensing_Library/src/%.cyclo: ../Middlewares/ST/STM32_TouchSensing_Library/src/%.c Middlewares/ST/STM32_TouchSensing_Library/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../TOUCHSENSING/App -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_TouchSensing_Library/inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STM32_TouchSensing_Library-2f-src

clean-Middlewares-2f-ST-2f-STM32_TouchSensing_Library-2f-src:
	-$(RM) ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl.su ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq.su ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq_tsc.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq_tsc.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq_tsc.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_acq_tsc.su ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_dxs.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_dxs.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_dxs.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_dxs.su ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_ecs.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_ecs.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_ecs.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_ecs.su ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_filter.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_filter.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_filter.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_filter.su ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_globals.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_globals.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_globals.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_globals.su ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_linrot.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_linrot.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_linrot.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_linrot.su ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_object.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_object.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_object.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_object.su ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_time.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_time.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_time.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_time.su ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_touchkey.cyclo ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_touchkey.d ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_touchkey.o ./Middlewares/ST/STM32_TouchSensing_Library/src/tsl_touchkey.su

.PHONY: clean-Middlewares-2f-ST-2f-STM32_TouchSensing_Library-2f-src

