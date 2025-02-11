CC = gcc
CFLAGS = -Wall -Wextra -std=c17
TARGET = process_simulator

all: $(TARGET)

$(TARGET): lab2.c
	$(CC) $(CFLAGS) -o $(TARGET) lab2.c

clean:
	rm -f $(TARGET)
