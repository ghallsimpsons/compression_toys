#include "compression.h"
#include <stdlib.h>

int
main()
{
	size_t elems = 1024*1024;

	float stddevs[] = {0.0, 0.1, 1.0, 5.0, 100.0, 500.0};

	size_t len = sizeof(stddevs)/sizeof(stddevs[0]);
	for (size_t i=0; i<len; i++){
		test_type(int, elems, 1024., stddevs[i]);
		test_type(float, elems, 1024., stddevs[i]);
		test_type(double, elems, 1024., stddevs[i]);
		test_type(long, elems, 1024., stddevs[i]);
	}

	exit(0);
}
