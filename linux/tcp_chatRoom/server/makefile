CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = $(wildcard *.c)					\
		$(wildcard userInfo/*.c)		\
		../../../lib/input/input.c		\
		../../../lib/strtomat/strtomat.c\
		../../../lib/parse_file/parse_file.c
OBJ = $(SRC:.c=.o)

TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
run:
	./program