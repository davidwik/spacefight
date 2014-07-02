all: main

CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lphysfs
TARGET=spacefight

main: main.o physfsrwops.o game.o gameobject.o player.o utils.o animation.o \
animationlibrary.o enemy.o collision.o fire.o bonus.o explosion.o sound.o soundlibrary.o \
base64.o
	$(CC) game.o main.o gameobject.o player.o utils.o animation.o \
animationlibrary.o physfsrwops.o explosion.o enemy.o bonus.o collision.o fire.o sound.o \
soundlibrary.o base64.o -o $(TARGET) $(LDFLAGS)

physfsrwops.o:
	$(CC) $(CFLAGS) physfsrwops.c

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

bonus.o:
	$(CC) $(CFLAGS) bonus.cpp

fire.o:
	$(CC) $(CFLAGS) fire.cpp

base64.o:
	$(CC) $(CFLAGS) base64.cpp

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

sound.o:
	$(CC) $(CFLAGS) sound.cpp

soundlibrary.o:
	$(CC) $(CFLAGS) soundlibrary.cpp

clean:
	rm -f spacefight *.o

run:
	./spacefight
