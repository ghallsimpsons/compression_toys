SOURCE_DIR=src
INCLUDE_DIR=include

CC=g++
CC_LIB_OPT=-c --shared
CC_OPT=--std=c++11 -fPIC -I${INCLUDE_DIR}

all: tests clean

compression: compression.o;

compression.o:
	${CC} ${CC_OPT} ${CC_LIB_OPT} ${SOURCE_DIR}/compression.cpp -o compression.o

loadcsv: loadcsv.o;

loadcsv.o:
	${CC} ${CC_OPT} ${CC_LIB_OPT} ${SOURCE_DIR}/loadcsv.cpp -o loadcsv.o

tests: compression loadcsv
	${CC} ${CC_OPT} ${SOURCE_DIR}/load_csv_test.cpp -o loadcsv_test compression.o loadcsv.o
	${CC} ${CC_OPT} ${SOURCE_DIR}/compression_test.cpp -o compression_test compression.o

clean:
	rm -f *.o *.so

clean-testdata:
	rm -rf *.bin *.xz
