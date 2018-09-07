################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/nrf24/nrf24.c \
../src/nrf24/radioPinFunctions.c 

OBJS += \
./src/nrf24/nrf24.o \
./src/nrf24/radioPinFunctions.o 

C_DEPS += \
./src/nrf24/nrf24.d \
./src/nrf24/radioPinFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
src/nrf24/%.o: ../src/nrf24/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


