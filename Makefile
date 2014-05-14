all: main

CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lSDL -lSDL_image -lSDL_ttf
TARGET=spacefight
TESTAPP=testapp

main: main.o game.o utils.o
	 $(CC) game.o main.o utils.o -o $(TARGET) $(LDFLAGS)

main.o:
	$(CC) $(CFLAGS) main.cpp

utils.o:
	$(CC) $(CFLAGS) utils.cpp

game.o:
	$(CC) $(CFLAGS) game.cpp

clean:
	rm -f spacefight testapp *.o

testapp:
	$(CC) -Wall testapp.cpp -o $(TESTAPP) $(LDFLAGS)
