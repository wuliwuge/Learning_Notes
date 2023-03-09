CC = g++
CFLAGS = -Wall -g -O2 -std=c++20 

EXE_HARDWARE = test


# SRC_DIR = ./src
SRC_DIR = ./.

# debug
# COMMON = $(SRC_DIR)/common/print.c $(SRC_DIR)/common/convert.c
COMMON = $(SRC_DIR)/book01.cpp

# hardware
CPU =$(SRC_DIR)/hardware/cpu/mmu.c $(SRC_DIR)/hardware/cpu/isa.c
MEMORY = $(SRC_DIR)/hardware/memory/dram.c

# main
MAIN_HARDWARE = $(SRC_DIR)/main_hardware.c

.PHONY:test
test:
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(COMMON) -o $(EXE_HARDWARE)
#	./$(EXE_HARDWARE)

clean:
	rm -f *.o *~ $(EXE_HARDWARE)
