all: main

CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lSDL -lSDL_image -lSDL_ttf
TARGET=spacefight
TESTAPP=testapp

main: main.o game.o gameobject.o player.o utils.o
	 $(CC) game.o main.o gameobject.o player.o utils.o -o $(TARGET) $(LDFLAGS)

main.o:
	$(CC) $(CFLAGS) main.cpp

utils.o:
	$(CC) $(CFLAGS) utils.cpp

game.o:
	$(CC) $(CFLAGS) game.cpp

gameobject.o:
	$(CC) $(CFLAGS) gameobject.cpp

player.o:
	$(CC) $(CFLAGS) player.cpp

clean:
	rm -f spacefight testapp *.o

testapp.o:
	$(CC) $(CFLAGS) testapp.cpp

testapp: utils.o testapp.o
	$(CC) utils.o testapp.o -o $(TESTAPP) $(LDFLAGS)
