################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../control\ utility/usblcd.c 

OBJS += \
./control\ utility/usblcd.o 

C_DEPS += \
./control\ utility/usblcd.d 


# Each subdirectory must supply rules for building sources it contributes
control\ utility/usblcd.o: ../control\ utility/usblcd.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\WinAVR-20100110\avr\include" -I"C:\Users\Anthony\Java\EclipseWork\LCD-USB\usbdrv" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"control utility/usblcd.d" -MT"control\ utility/usblcd.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


