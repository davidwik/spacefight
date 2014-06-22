all: main

CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=-lSDL -lSDL_image -lSDL_ttf
TARGET=spacefight
TESTAPP=testapp

main: clean main.o game.o gameobject.o player.o utils.o animation.o animationlibrary.o enemy.o collision.o fire.o
	 $(CC) game.o main.o gameobject.o player.o utils.o animation.o animationlibrary.o enemy.o collision.o fire.o -o $(TARGET) $(LDFLAGS)

main.o:
	$(CC) $(CFLAGS) main.cpp

enemy.o:
	$(CC) $(CFLAGS) enemy.cpp

utils.o:
	$(CC) $(CFLAGS) utils.cpp

game.o:
	$(CC) $(CFLAGS) game.cpp

gameobject.o:
	$(CC) $(CFLAGS) gameobject.cpp

collision.o:
	$(CC) $(CFLAGS) collision.cpp

player.o:
	$(CC) $(CFLAGS) player.cpp

testapp.o:
	$(CC) $(CFLAGS) testapp.cpp

animation.o:
	$(CC) $(CFLAGS) animation.cpp

animationlibrary.o:
	$(CC) $(CFLAGS) animationlibrary.cpp

fire.o:
	$(CC) $(CFLAGS) fire.cpp

testapp: clean utils.o animation.o animationlibrary.o testapp.o
	$(CC) animationlibrary.o animation.o utils.o testapp.o -o $(TESTAPP) $(LDFLAGS)

clean:
	rm -f spacefight testapp *.o

run:
	./testapp
