EXE_NAME = p3
CFLAGS = -Wall -g
CC = gcc

all: clean p3

p3:	commands.o list.o
	$(CC) $(CFLAGS) -o $(EXE_NAME) p3.c commands.o list.o

commands.o:
	$(CC) $(CFLAGS) -c commands.c

list.o:
	$(CC) $(CFLAGS) -c list.c
	
clean:
	rm -f $(EXE_NAME) commands.o list.o
	
valgrind_check:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=leaks.txt ./$(EXE_NAME)
	cat leaks.txt
