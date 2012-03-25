################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../control\ utility/usbdrv/oddebug.o \
../control\ utility/usbdrv/usbdrv.o \
../control\ utility/usbdrv/usbdrvasm.o 

C_SRCS += \
../control\ utility/usbdrv/oddebug.c \
../control\ utility/usbdrv/usbdrv.c 

S_UPPER_SRCS += \
../control\ utility/usbdrv/usbdrvasm.S 

ASM_SRCS += \
../control\ utility/usbdrv/usbdrvasm.asm 

OBJS += \
./control\ utility/usbdrv/oddebug.o \
./control\ utility/usbdrv/usbdrv.o \
./control\ utility/usbdrv/usbdrvasm.o 

C_DEPS += \
./control\ utility/usbdrv/oddebug.d \
./control\ utility/usbdrv/usbdrv.d 

ASM_DEPS += \
./control\ utility/usbdrv/usbdrvasm.d 

S_UPPER_DEPS += \
./control\ utility/usbdrv/usbdrvasm.d 


# Each subdirectory must supply rules for building sources it contributes
control\ utility/usbdrv/oddebug.o: ../control\ utility/usbdrv/oddebug.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\WinAVR-20100110\avr\include" -I"C:\Users\Anthony\Java\EclipseWork\LCD-USB\usbdrv" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"control utility/usbdrv/oddebug.d" -MT"control\ utility/usbdrv/oddebug.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

control\ utility/usbdrv/usbdrv.o: ../control\ utility/usbdrv/usbdrv.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\WinAVR-20100110\avr\include" -I"C:\Users\Anthony\Java\EclipseWork\LCD-USB\usbdrv" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"control utility/usbdrv/usbdrv.d" -MT"control\ utility/usbdrv/usbdrv.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

control\ utility/usbdrv/usbdrvasm.o: ../control\ utility/usbdrv/usbdrvasm.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -mmcu=atmega328p -MMD -MP -MF"control utility/usbdrv/usbdrvasm.d" -MT"control\ utility/usbdrv/usbdrvasm.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

control\ utility/usbdrv/usbdrvasm.o: ../control\ utility/usbdrv/usbdrvasm.asm
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -mmcu=atmega328p -MMD -MP -MF"control utility/usbdrv/usbdrvasm.d" -MT"control\ utility/usbdrv/usbdrvasm.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


