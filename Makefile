main : main.o inout.o SAT.o
	gcc -o main main.o inout.o SAT.o -Wall

SAT.o : SAT.c SAT.h
	gcc -c SAT.c -Wall

inout.o : inout.c inout.h
	gcc -c inout.c -Wall

all : main

clean :
	rm *.o *~

cleanall : clean
