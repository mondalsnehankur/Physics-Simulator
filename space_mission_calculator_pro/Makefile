CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude -O2
LDLIBS = -lm
TARGET = space_mission_calculator
SOURCES = src/main.c src/physics.c src/planets.c src/ui.c

.PHONY: all clean run
all: $(TARGET)

$(TARGET): $(SOURCES) include/space.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe planet_report.csv planets.csv
