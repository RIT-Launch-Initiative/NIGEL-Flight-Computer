TARGET=unit_test
objects = unit_test.o ublox7rx.o

all: $(objects)
	gcc -o ${TARGET} $(objects)

unit_test.o: unit_test.c ../ublox7rx.h ../ublox7rx.c
	gcc -I.. -c -g unit_test.c

ublox7rx.o: ../ublox7rx.c ../ublox7rx.h
	gcc -I.. -c -g ../ublox7rx.c

run:
	./${TARGET}

clean: 
	rm -f *.o ${TARGET}
