CC = gcc

CFLAGS = -Wall -Wextra -g
LDFLAGS = -lbluetooth

TARGET = bluetooth_uart

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

cleaner:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)