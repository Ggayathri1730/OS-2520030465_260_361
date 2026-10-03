CC = gcc
CFLAGS = -Wall -Wextra -std=c11
CPPFLAGS = -Isrc -Iprocess_management
LDLIBS = -pthread

TARGET = task_processing_system

SOURCES = src/main.c \
          src/student_input.c \
          src/memory.c \
          src/student_processing.c \
          src/report.c \
          process_management/process.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	find . -type f -name '*.o' -delete
	rm -f $(TARGET) test_memory test_process test_student_input test_student_processing test_task_input test_threads

.PHONY: all run clean
