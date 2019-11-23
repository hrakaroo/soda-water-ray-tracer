CPP = g++

INC = -I/usr/lib/qt-2.3.1/include -I./include
LIB = -L/usr/lib/qt-2.3.1/lib -L./lib
LINK = -lANN -lm -lqt -ldl
LIBS   = basics/*.o objects/*.o

swray : swray.o main.o
	$(CPP) $(LIB) $(LIBS) main.o swray.o -o swray $(LINK)

SWbasic:
	cd basics; make all

swray.o : swray.cpp swray.h
	$(CPP) -c $(INC) swray.cpp

main.o : main.cpp
	$(CPP) -c $(INC) main.cpp

force : clean swray

clean:
	- rm -rf *.o *~ swray
