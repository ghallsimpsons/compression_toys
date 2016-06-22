CC=g++
CC_LIB_OPT=-c --shared
CC_OPT=--std=c++11 -fPIC

all: compression loadcsv tests

compression: compression.o;

compression.o:
	${CC} ${CC_OPT} ${CC_LIB_OPT} compression.cpp -o compression.o

loadcsv: loadcsv.o;

loadcsv.o:
	${CC} ${CC_OPT} ${CC_LIB_OPT} loadcsv.cpp -o loadcsv.o

tests: compression loadcsv
	${CC} ${CC_OPT} load_csv_test.cpp -o loadcsv_test.o compression.o loadcsv.o

clean:
	rm -f *.o *.so
