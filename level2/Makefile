CC = gcc
CFLAGS = -Wall -Wextra -O0 -g
TARGET = level2

all: $(TARGET)

$(TARGET): invaders.c
	$(CC) $(CFLAGS) -o $(TARGET) invaders.c

run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all run debug clean
