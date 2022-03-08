objects = unittest.o ublox7rx.o

all: $(objects)
	gcc -o program $(objects)

unittest.o: unittest.c ublox7rx.h ublox7rx.c
	gcc -c -g unittest.c

ublox7rx.o: ublox7rx.c ublox7rx.h
	gcc -c -g ublox7rx.c

run:
	./program

clean: 
	rm -f *.o


