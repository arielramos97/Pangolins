CC=gcc
CFLAGS=-g -std=c99 -Wall
#LDFLAGS=-lm

pangolins_part1:
	$(CC) $(CFLAGS) pangolins_part1.c methods.c -o pangolins_part1
