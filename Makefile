SRC_FILE=src/
LIBS_FILE=src/libs/
C_FLAGS=-Wall -Wno-unknown-pragmas
CC=gcc

all: build cleanup

build: libs main  
	$(CC) main.o helper.o tree.o dict.o compactor.o -o huffmaninator $(C_FLAGS)

main:
	$(CC) -c $(SRC_FILE)main.c -o main.o $(C_FLAGS)

libs:
	$(CC) -c $(LIBS_FILE)helper.c -o helper.o $(C_FLAGS)
	$(CC) -c $(LIBS_FILE)tree.c -o tree.o $(C_FLAGS)
	$(CC) -c $(LIBS_FILE)dict.c -o dict.o $(C_FLAGS)
	$(CC) -c $(LIBS_FILE)compactor.c -o compactor.o $(C_FLAGS)

cleanup:
	rm *.o

exec:
	./huffmaninator -c -f test.txt -o archive.hca
	./huffmaninator -x -f archive.hca -o out.txt
