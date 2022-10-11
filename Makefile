SRC_FILE=src/
LIBS_FILE=src/libs/
C_FLAGS=-Wall

all: main libs cleanup
	cc main.o helper.o -o space_invaders.exe

main:
	cc -c $(SRC_FILE)main.c -o main.o

libs:
	cc -c $(LIBS_FILE)helper.c -o helper.o

cleanup:
	rm *.o

exec:
	./space_invaders.exe