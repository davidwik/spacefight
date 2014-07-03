CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lphysfs
TARGET=spacefight

SOURCES=$(wildcard *.cpp)
SOURCES+=$(wildcard *.c)
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC)  $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(OBJECTS) $(TARGET)
