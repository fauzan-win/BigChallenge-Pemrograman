CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJS = main.o process.o io.o

program: $(OBJS)
	$(CC) $(CFLAGS) -o program $(OBJS)

main.o: main.c process.h io.h
	$(CC) $(CFLAGS) -c main.c

process.o: process.c process.h
	$(CC) $(CFLAGS) -c process.c

io.o: io.c io.h process.h
	$(CC) $(CFLAGS) -c io.c

clean:
	del *.o 2>nul || true
	del program.exe 2>nul || true
