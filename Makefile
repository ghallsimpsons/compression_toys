SOURCE_DIR=src
TESTS_DIR=tests
INCLUDE_DIR=include

CC=g++
CC_LIB_OPT=-c --shared
CC_OPT=--std=c++11 -fPIC -I${INCLUDE_DIR}

all: tests clean

compression: compression.o;

compression.o:
	${CC} ${CC_OPT} ${CC_LIB_OPT} ${SOURCE_DIR}/compression.cpp -o compression.o

bitmask: bitmask.o;

bitmask.o:
	${CC} ${CC_OPT} ${CC_LIB_OPT} ${SOURCE_DIR}/bitmask.cpp -o bitmask.o

tests: compression bitmask
	${CC} ${CC_OPT} ${TESTS_DIR}/load_csv_test.cpp -o loadcsv_test compression.o bitmask.o
	${CC} ${CC_OPT} ${TESTS_DIR}/compression_test.cpp -o compression_test compression.o

clean:
	rm -f *.o *.so

clean-testdata:
	rm -rf *.bin *.xz
