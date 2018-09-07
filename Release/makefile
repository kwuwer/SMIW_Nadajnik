################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/oled/subdir.mk
-include src/nrf24/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
10_LED_WIFI_RX.lss \

FLASH_IMAGE += \
10_LED_WIFI_RX.hex \

EEPROM_IMAGE += \
10_LED_WIFI_RX.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 10_LED_WIFI_RX.elf secondary-outputs

# Tool invocations
10_LED_WIFI_RX.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,10_LED_WIFI_RX.map -Wl,--gc-sections -L/Users/kwuwer/eclipse-workspace/10_LED_WIFI_RX/src -mmcu=atmega32 -o "10_LED_WIFI_RX.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

10_LED_WIFI_RX.lss: 10_LED_WIFI_RX.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 10_LED_WIFI_RX.elf  >"10_LED_WIFI_RX.lss"
	@echo 'Finished building: $@'
	@echo ' '

10_LED_WIFI_RX.hex: 10_LED_WIFI_RX.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 10_LED_WIFI_RX.elf  "10_LED_WIFI_RX.hex"
	@echo 'Finished building: $@'
	@echo ' '

10_LED_WIFI_RX.eep: 10_LED_WIFI_RX.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 10_LED_WIFI_RX.elf  "10_LED_WIFI_RX.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 10_LED_WIFI_RX.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 10_LED_WIFI_RX.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 10_LED_WIFI_RX.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
