################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../control\ utility/libusb/lib/dynamic/libusb_dyn.c 

OBJS += \
./control\ utility/libusb/lib/dynamic/libusb_dyn.o 

C_DEPS += \
./control\ utility/libusb/lib/dynamic/libusb_dyn.d 


# Each subdirectory must supply rules for building sources it contributes
control\ utility/libusb/lib/dynamic/libusb_dyn.o: ../control\ utility/libusb/lib/dynamic/libusb_dyn.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\WinAVR-20100110\avr\include" -I"C:\Users\Anthony\Java\EclipseWork\LCD-USB\usbdrv" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"control utility/libusb/lib/dynamic/libusb_dyn.d" -MT"control\ utility/libusb/lib/dynamic/libusb_dyn.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


