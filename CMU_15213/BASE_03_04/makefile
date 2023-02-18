# 当前是在window下测试makefile，可做linux下重新编写
CC = g++
# CFLAGS = -Wall -g -O2 -Werror 
CFLAGS = -g

EXECUTABLE = csapp

SRC = ./src

CODE = ./src/memory/instruction.cpp ./src/disk/code.cpp ./src/memory/dram.cpp ./src/cpu/mmu.cpp ./src/cpu/register.cpp ./src/main.cpp 

.PHONY: csapp
csapp:
	$(CC) $(CFLAGS) -I$(SRC) $(CODE) -o $(EXECUTABLE) -std=c++11 # 后续需要更新gcc的版本
	./$(EXECUTABLE)

add:
	$(CC) $(CFLAGS) -I$(SRC) add.cpp -o add -std=c++11

run:
	./$(EXECUTABLE)

clean:
# rm -rf ./$(EXECUTABLE) ./add
	rm -f *.o *~ $(EXECUTABLE) ./add