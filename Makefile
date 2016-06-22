SOURCE_DIR=src
TESTS_DIR=tests
INCLUDE_DIR=include

CC=g++
CC_LIB_OPT=-c --shared
CC_OPT=--std=c++11 -fPIC -I${INCLUDE_DIR}

all: transpose_test load_csv_test clean

transpose.o:
	${CC} ${CC_OPT} ${CC_LIB_OPT} ${SOURCE_DIR}/transpose.cpp -o transpose.o

bitmask.o:
	${CC} ${CC_OPT} ${CC_LIB_OPT} ${SOURCE_DIR}/bitmask.cpp -o bitmask.o

tests: transpose_test load_csv_test;

transpose_test: transpose.o
	${CC} ${CC_OPT} ${TESTS_DIR}/transpose_test.cpp transpose.o -o transpose_test

load_csv_test: transpose.o bitmask.o
	${CC} ${CC_OPT} ${TESTS_DIR}/load_csv_test.cpp transpose.o bitmask.o -o load_csv_test

clean:
	rm -f *.o *.so

clean-testdata:
	rm -rf *.bin *.xz
