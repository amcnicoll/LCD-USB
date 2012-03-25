################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include usbdrv/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
LCD-USB.lss \

FLASH_IMAGE += \
LCD-USB.hex \

EEPROM_IMAGE += \
LCD-USB.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: LCD-USB.elf secondary-outputs

# Tool invocations
LCD-USB.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,LCD-USB.map -mmcu=atmega328p -o "LCD-USB.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

LCD-USB.lss: LCD-USB.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S LCD-USB.elf  >"LCD-USB.lss"
	@echo 'Finished building: $@'
	@echo ' '

LCD-USB.hex: LCD-USB.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex LCD-USB.elf  "LCD-USB.hex"
	@echo 'Finished building: $@'
	@echo ' '

LCD-USB.eep: LCD-USB.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex LCD-USB.elf  "LCD-USB.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: LCD-USB.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p LCD-USB.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) LCD-USB.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
