CC=g++

LFLAGS=-luser32 -lgdi32 -lopengl32 -lgdiplus -O3

main: main.cpp
	${CC} -o $@ $? ${LFLAGS} -mwindows
