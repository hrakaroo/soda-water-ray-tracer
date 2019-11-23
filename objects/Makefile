
#CPP  = g++ -DSAMPLE9
CPP = g++
INCS = -I../include

all : object.o light.o env.o material.o camera.o econe.o mesh.o sphere.o\
      photon.o

object.o : object.cpp
	$(CPP) $(CFLAGS) -c $(INCS) object.cpp

light.o : light.cpp
	$(CPP) $(CFLAGS) -c $(INCS) light.cpp

env.o : env.cpp
	$(CPP) $(CFLAGS) -c $(INCS) env.cpp

material.o : material.cpp
	$(CPP) $(CFLAGS) -c $(INCS) material.cpp

camera.o : camera.cpp
	$(CPP) $(CFLAGS) -c $(INCS) camera.cpp

sphere.o : sphere.cpp
	$(CPP) $(CFLAGS) -c $(INCS) sphere.cpp

mesh.o : mesh.cpp
	$(CPP) $(CFLAGS) -c $(INCS) mesh.cpp

econe.o : econe.cpp
	$(CPP) $(CFLAGS) -c $(INCS) econe.cpp

photon.o : photon.cpp
	$(CPP) $(CFLAGS) -c $(INCS) photon.cpp

clean :
	- rm -f *.o *~

force : clean all

