################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/common/core/qbuffer.c 

OBJS += \
./src/common/core/qbuffer.o 

C_DEPS += \
./src/common/core/qbuffer.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/core/%.o src/common/core/%.su src/common/core/%.cyclo: ../src/common/core/%.c src/common/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F051x8 -c -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/ap" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/bsp" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/common" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/hw" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/lib" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/lib/cube_f051/Drivers/CMSIS/Include" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/lib/cube_f051/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/lib/cube_f051/Drivers/STM32F0xx_HAL_Driver/Inc" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/common/hw/include" -I"D:/001.Device/07.FireKIm_CC_Board/stm32f051_fw/src/common/core" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-common-2f-core

clean-src-2f-common-2f-core:
	-$(RM) ./src/common/core/qbuffer.cyclo ./src/common/core/qbuffer.d ./src/common/core/qbuffer.o ./src/common/core/qbuffer.su

.PHONY: clean-src-2f-common-2f-core

