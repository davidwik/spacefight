all: main

CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-lSDL -lSDL_image -lSDL_ttf
TARGET=spacefight
TESTAPP=testapp

main: clean main.o game.o gameobject.o player.o utils.o animation.o
	 $(CC) game.o main.o gameobject.o player.o utils.o animation.o -o $(TARGET) $(LDFLAGS)

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

animation.o:
	$(CC) $(CFLAGS) animation.cpp

testapp: utils.o testapp.o
	$(CC) utils.o testapp.o -o $(TESTAPP) $(LDFLAGS)
