flags=$(shell pkg-config --cflags gtk4)
libs=$(shell pkg-config --libs gtk4)
bin=mp3
cfiles=main.c
cc=gcc

all:
	$(cc) $(flags) -o $(bin) $(cfiles) $(libs)
