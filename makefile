CC=g++

LFLAGS=-luser32 -lgdi32 -lopengl32 -lgdiplus 
CFLAGS=-mwindows -fopenmp

main: main.cpp
	${CC} -o $@ $? ${LFLAGS} ${CFLAGS}
