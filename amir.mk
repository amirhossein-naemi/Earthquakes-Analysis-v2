# <--- Amir Makefile --->   

# Compiler

CC = g++

# Flags to the compiler

CFLAGS = -Wall

OBJECTS = amir

all: ${OBJECTS}

amir: amir.cpp
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -rf ${OBJECTS}

