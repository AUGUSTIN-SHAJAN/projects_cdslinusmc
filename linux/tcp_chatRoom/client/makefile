CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = $(wildcard *.c)					\
		../../../lib/input/input.c		\
		$(wildcard clientFunk/*.c)		\
# 		../../../lib/strtomat/strtomat.c\
# 		../../../lib/parse_file/parse_file.c
		
OBJ = $(SRC:.c=.o)

TARGET = client

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
run:
	./client 127.0.0.1