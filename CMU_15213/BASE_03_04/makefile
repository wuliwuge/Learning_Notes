# 当前是在window下测试makefile，可做linux下重新编写
CC = g++
CFLAGS = -Wall -g -O2 -Werror -std=g++17

EXE = program

CODE = ./memory/instruction.cpp ./disk/code.cpp

.PHONY: program
main:
	$(CC) $(CFLAGS) -I $(CODE) -o $(EXE)

run:
	./$(EXE)