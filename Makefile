CC=g++
CC_LIB_OPT=-c --shared
CC_OPT=--std=c++11 -fPIC

all: compression loadcsv tests clean

compression: compression.o;

compression.o:
	${CC} ${CC_OPT} ${CC_LIB_OPT} compression.cpp -o compression.o

loadcsv: loadcsv.o;

loadcsv.o:
	${CC} ${CC_OPT} ${CC_LIB_OPT} loadcsv.cpp -o loadcsv.o

tests: compression loadcsv
	${CC} ${CC_OPT} load_csv_test.cpp -o loadcsv_test compression.o loadcsv.o
	${CC} ${CC_OPT} compression_test.cpp -o compression_test compression.o

clean:
	rm -f *.o *.so
