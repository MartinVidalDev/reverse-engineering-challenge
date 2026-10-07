CC = gcc
CFLAGS = -Wall -Wextra -O0 -g
LDFLAGS = 
TARGET = level3

all: $(TARGET)

$(TARGET): invaders.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) invaders.c

run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

frida: $(TARGET)
	frida -l hook.js ./$(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all run debug frida clean
