################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ap/ap.c \
../src/ap/ap_cli.c 

OBJS += \
./src/ap/ap.o \
./src/ap/ap_cli.o 

C_DEPS += \
./src/ap/ap.d \
./src/ap/ap_cli.d 


# Each subdirectory must supply rules for building sources it contributes
src/ap/%.o src/ap/%.su src/ap/%.cyclo: ../src/ap/%.c src/ap/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F051x8 -c -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/ap" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/bsp" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/common" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/hw" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/lib" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/lib/cube_f051/Drivers/CMSIS/Include" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/lib/cube_f051/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/lib/cube_f051/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/common/hw/include" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-ap

clean-src-2f-ap:
	-$(RM) ./src/ap/ap.cyclo ./src/ap/ap.d ./src/ap/ap.o ./src/ap/ap.su ./src/ap/ap_cli.cyclo ./src/ap/ap_cli.d ./src/ap/ap_cli.o ./src/ap/ap_cli.su

.PHONY: clean-src-2f-ap

