main : main.c inout.o SAT.o
	gcc -o main main.c inout.o SAT.o -Wall

sudoku : sudoku_encoder.c sudoku_encoder.h
	gcc -o sudoku sudoku_encoder.c -Wall

SAT.o : SAT.c SAT.h
	gcc -c SAT.c -Wall

inout.o : inout.c inout.h
	gcc -c inout.c -Wall

all : main sudoku

clean :
	rm *.o main sudoku tmp.sat

cleanall : clean
