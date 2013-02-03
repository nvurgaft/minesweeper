# makefile for minesweeper

all:
	
	gcc -g -I. -Wall colorPrint.c getch.c mineSweeper.c  game.c -lm -o game
