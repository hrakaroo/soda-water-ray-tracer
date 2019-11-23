CPP = g++ -g -I../include 

all : point.o vector.o line.o plane.o matrix.o color.o list.o \
      rotation.o intersect.o

point.o     : point.cpp
	$(CPP) -c point.cpp

vector.o    : vector.cpp
	$(CPP) -c vector.cpp

line.o      : line.cpp
	$(CPP) -c line.cpp

plane.o     : plane.cpp
	$(CPP) -c plane.cpp

matrix.o    : matrix.cpp
	$(CPP) -c matrix.cpp

color.o     : color.cpp
	$(CPP) -c color.cpp

list.o      : list.cpp
	$(CPP) -c list.cpp

rotation.o  : rotation.cpp
	$(CPP) -c rotation.cpp

intersect.o : intersect.cpp
	$(CPP) -c intersect.cpp

clean : 
	- rm -rf *.o *~

force : clean all
