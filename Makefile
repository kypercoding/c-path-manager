# macros
CC = clang

# rules for non-file targets
all: main clean-o rename

rename: main
	mv main cm

clean: clean-o
	rm -rf main cm

clean-o:
	rm -rf *.o

main: main.o db.o
	${CC} main.o db.o -o main -lhiredis

main.o: main.c db.h
	${CC} -c main.c

db.o: db.c db.h
	${CC} -c db.c
