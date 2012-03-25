################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../control\ utility/libusb/examples/benchmark.c \
../control\ utility/libusb/examples/bulk.c 

OBJS += \
./control\ utility/libusb/examples/benchmark.o \
./control\ utility/libusb/examples/bulk.o 

C_DEPS += \
./control\ utility/libusb/examples/benchmark.d \
./control\ utility/libusb/examples/bulk.d 


# Each subdirectory must supply rules for building sources it contributes
control\ utility/libusb/examples/benchmark.o: ../control\ utility/libusb/examples/benchmark.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\WinAVR-20100110\avr\include" -I"C:\Users\Anthony\Java\EclipseWork\LCD-USB\usbdrv" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"control utility/libusb/examples/benchmark.d" -MT"control\ utility/libusb/examples/benchmark.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

control\ utility/libusb/examples/bulk.o: ../control\ utility/libusb/examples/bulk.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\WinAVR-20100110\avr\include" -I"C:\Users\Anthony\Java\EclipseWork\LCD-USB\usbdrv" -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=20000000UL -MMD -MP -MF"control utility/libusb/examples/bulk.d" -MT"control\ utility/libusb/examples/bulk.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


