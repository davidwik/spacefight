CC=g++
CFLAGS=-c -Wall -Werror -std=c++11 -O2
LDFLAGS=-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lphysfs
TARGET=spacefight

SOURCES=$(wildcard *.cpp)
SOURCES+=$(wildcard *.c)
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(TARGET)

# pull inn dependency info for *existing* .o files
DEPS := $(OBJECTS:.o=.d)
-include $(DEPS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $<
	@$(CC) -MM -MT $@ $(CFLAGS) $< > $*.d
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

clean:
	rm -f $(TARGET) *.d *.o
