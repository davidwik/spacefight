all: main

CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
TARGET=spacefight
TESTAPP=testapp

main: main.o game.o gameobject.o player.o utils.o animation.o animationlibrary.o enemy.o collision.o fire.o explosion.o sound.o
	 $(CC) game.o main.o gameobject.o player.o utils.o animation.o animationlibrary.o explosion.o enemy.o collision.o fire.o sound.o -o $(TARGET) $(LDFLAGS)

main.o:
	$(CC) $(CFLAGS) main.cpp

enemy.o:
	$(CC) $(CFLAGS) enemy.cpp

sound.o:
	$(CC) $(CFLAGS) sound.cpp

utils.o:
	$(CC) $(CFLAGS) utils.cpp

game.o:
	$(CC) $(CFLAGS) game.cpp

gameobject.o:
	$(CC) $(CFLAGS) gameobject.cpp

explosion.o:
	$(CC) $(CFLAGS) explosion.cpp

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

clean:
	rm -f spacefight *.o

run:
	./spacefight
