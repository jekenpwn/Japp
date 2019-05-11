#!/bin/sh

#CROSS_COMPILE := "/home/jeken/hdddisk_1T/orangepi3/OrangePiH6/toolchain/gcc-linaro-aarch/bin/aarch64-linux-gnu-"
#CC := $(CROSS_COMPILE)gcc
#LD := $(CROSS_COMPILE)ld
CC := gcc

DEP_I := jpipe.h
DEP_S := hello_ipc.c 
OBJ := hello_ipc.o jpipe.o
APP := jhello_ipc 

INC:= -I .
SRC:= -L.

CFLAG:= -Wall -pthread 

$(APP) : $(OBJ)
	$(CC) $(OBJ) -o $@ $(CFLAG) 

%.o : %.c %.h
	$(CC) -c $< -o $@

clean:
	rm *.o $(APP)