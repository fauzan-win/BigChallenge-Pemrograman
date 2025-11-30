all: program

program: main.o textutil.o datastore.o
	gcc main.o textutil.o datastore.o -o program

main.o: main.c textutil.h datastore.h
	gcc -c main.c

textutil.o: textutil.c textutil.h
	gcc -c textutil.c

datastore.o: datastore.c datastore.h
	gcc -c datastore.c

clean:
	rm -f *.o program
