CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = producer_ipc
SRC = producer_ipc.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
