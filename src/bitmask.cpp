#include "bitmask.h"
#include <limits.h>

#define BIT(x) ((unsigned long long) 1 << x)

using namespace std;

union float_view {
	float f;
	unsigned char bytes[sizeof(f)];
};

void
mask(float *f, size_t bits)
{
	/*
	 * Mask the last (bits) bits of a float value.
	 */
	union float_view fv;
	fv.f = *f;

	for (size_t b=0; b<bits; b++)
		fv.bytes[b/CHAR_BIT] &= ~BIT(b%CHAR_BIT);

	*f = fv.f;
}
