all:
	avr-gcc -mmcu=atmega328p -DF_CPU=16000000UL -Os -o main.elf main.c
	avr-objcopy -O ihex -R .eeprom main.elf main.hex

flash:
	sudo avrdude -c arduino -p m328p -P /dev/ttyACM0 -b115200 -U flash:w:main.hex

disasm:
	avr-objdump -d main.elf

size:
	avr-size main.elf

clean:
	rm -f main.elf main.hex