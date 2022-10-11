SRC_FILE=src/
LIBS_FILE=src/libs/
C_FLAGS=-Wall
CC=gcc

all: build cleanup

build: libs main  
	$(CC) main.o helper.o -o space_invaders.exe $(C_FLAGS)

main:
	$(CC) -c $(SRC_FILE)main.c -o main.o $(C_FLAGS)

libs:
	$(CC) -c $(LIBS_FILE)helper.c -o helper.o $(C_FLAGS)

cleanup:
	rm *.o

exec:
	./space_invaders.exe