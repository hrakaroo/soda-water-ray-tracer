CPP  = g++

INCS = -I../include
LIBS = ../basics/*.o ../objects/*.o

all : matrix list env plane vector ann

matrix : matrixTest.cpp
	$(CPP) $(INCS) $(LIBS) matrixTest.cpp -o matrix

list : listTest.cpp
	$(CPP) $(INCS) $(LIBS) listTest.cpp -o list

env : envTest.cpp
	$(CPP) $(INCS) $(LIBS) envTest.cpp -o env

plane : planeTest.cpp
	$(CPP) $(INCS) $(LIBS) planeTest.cpp -o plane

vector : vectorTest.cpp
	$(CPP) $(INCS) $(LIBS) vectorTest.cpp -o vector

ann    : annTest.cpp
	$(CPP) $(INCS) $(LIBS) -L../lib annTest.cpp -o ann -lANN -lm 

clean :
	- rm -f *.o *~ matrix list env plane ann vector

force : clean all
