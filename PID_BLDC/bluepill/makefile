all:
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -DSTM32F103xE -I. -c startup.c -o startup.o
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -DSTM32F103xE -I. -c main.c -o main.o
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -DSTM32F103xE -I. -c handlers.c -o handlers.o
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -T linker.ld -nostdlib handlers.o startup.o main.o -o firmware.elf
	arm-none-eabi-objcopy -O ihex firmware.elf firmware.hex

clean:
	rm -f *.o *.elf *.hex *.bin

flash:
	arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
	st-flash write firmware.bin 0x08000000


probe:
	st-info --probe