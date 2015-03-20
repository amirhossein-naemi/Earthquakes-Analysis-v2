# <--- Amir Makefile --->   

# Compiler

CC = g++

# Flags to the compiler

CFLAGS = -Wall

OBJECTS = amir

all: amir

amir: amir.o earthquake.o station.o
    ${CC} -o amir amir.o earthquake.o station.o

amir.o: amir.cpp
    ${CC} -c amir.cpp

earthquake.o: earthquake.cpp
    ${CC} -c earthquake.cpp

station.o: station.cpp
    ${CC} -c station.cpp 

clean:
    rm -rf ${OBJECTS}

