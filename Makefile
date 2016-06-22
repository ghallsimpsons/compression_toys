SOURCE_DIR=src
TESTS_DIR=tests
INCLUDE_DIR=include
MAKE_DIR=.make

CC=g++
CC_LIB_OPT=-c --shared
CC_OPT=--std=c++11 -fPIC -I${INCLUDE_DIR}

all: transpose_test load_csv_test;

${SOURCE_DIR}/transpose.cpp: ${INCLUDE_DIR}/transpose.h

${SOURCE_DIR}/bitmask.cpp: ${INCLUDE_DIR}/bitmask.h

${TESTS_DIR}/transpose_test.cpp: ${INCLUDE_DIR}/transpose.h

${TESTS_DIR}/load_csv_test.cpp: ${INCLUDE_DIR}/bitmask.h ${INCLUDE_DIR}/transpose.h

${MAKE_DIR}/transpose.o: ${SOURCE_DIR}/transpose.cpp
	@mkdir -p ${MAKE_DIR}
	${CC} ${CC_OPT} ${CC_LIB_OPT} ${SOURCE_DIR}/transpose.cpp -o ${MAKE_DIR}/transpose.o

${MAKE_DIR}/bitmask.o: ${SOURCE_DIR}/bitmask.cpp
	@mkdir -p ${MAKE_DIR}
	${CC} ${CC_OPT} ${CC_LIB_OPT} ${SOURCE_DIR}/bitmask.cpp -o ${MAKE_DIR}/bitmask.o

tests: transpose_test load_csv_test;

transpose_test: ${MAKE_DIR}/transpose.o ${TESTS_DIR}/transpose_test.cpp
	${CC} ${CC_OPT} ${TESTS_DIR}/transpose_test.cpp ${MAKE_DIR}/transpose.o -o transpose_test

load_csv_test: ${MAKE_DIR}/transpose.o ${MAKE_DIR}/bitmask.o ${TESTS_DIR}/load_csv_test.cpp
	${CC} ${CC_OPT} ${TESTS_DIR}/load_csv_test.cpp ${MAKE_DIR}/transpose.o ${MAKE_DIR}/bitmask.o -o load_csv_test

clean:
	rm -f ${MAKE_DIR}/*.o

clean-testdata:
	rm -rf *.bin *.xz
