#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <limits.h>
#include <random>

#include "transpose.h"

#define BIT(x) ((unsigned long long) 1 << x)

template <typename T>
union container {
	T native;
	unsigned char bytes[sizeof(T)];
};

template <typename T>
void
assign_bit(T *in_ptr, T *out_ptr, size_t elem_index_out, size_t sig_bit, size_t out_bit)
{
	/*
	 * Part of the transpose operation. Take the (sig_bit) bit of the (out_bit)
	 * element of (in_ptr), and move it to the (out_bit) bit of the (sig_bit)
	 * block of (out_ptr), at index elem_index_out. See README for explanation.
	 */
	container<T> in, out;
	in.native = in_ptr[out_bit];
	out.native = out_ptr[elem_index_out];

	/* Each elem has sizeof(T) "bytes". We only need one of them. */
	size_t bits_per_elem = sizeof(T)*CHAR_BIT;
	size_t in_byte_index = sig_bit/CHAR_BIT; /* Verified. */
	size_t out_byte_index = (out_bit % bits_per_elem) / CHAR_BIT; /* Verified. */
	size_t sig_bit_byte_index = sig_bit % CHAR_BIT; /* Verified. */
	size_t out_bit_byte_index = out_bit % CHAR_BIT; /* Verified. */

	out.bytes[out_byte_index] |=
		BIT(out_bit_byte_index) * !!(BIT(sig_bit_byte_index) & in.bytes[in_byte_index]);

	out_ptr[elem_index_out] = out.native;
}

template <typename T>
void
transpose(T *data_in, T *data_out, size_t len)
{
	/*
	 * Bitwise transpose elements of type T such that the n-th significant bits
	 * are stored contiguously in memory.
	 */
	size_t sig_bit, out_bit, sigbit_start, elem_index_out, bits_per_elem;
	bits_per_elem = sizeof(T)*CHAR_BIT;

	for (sig_bit=0; sig_bit<bits_per_elem; sig_bit++){
		sigbit_start = sig_bit*len/bits_per_elem;
		for (out_bit=0; out_bit<len; out_bit++){
			elem_index_out = sigbit_start + out_bit/bits_per_elem;
			assign_bit(data_in, data_out, elem_index_out, sig_bit, out_bit);
		}
	}
}

template <typename T>
void
create_test_files(size_t elems, double mean, double stddev, const char *typestr)
{
	size_t i;

	T *in = (T*) calloc(elems, sizeof(T));
	if (!in){
		printf("Could not alloc memory\n");
		exit(1);
	}
	T *out = (T*) calloc(elems, sizeof(T));
	if (!out){
		printf("Could not alloc memory\n");
		exit(1);
	}

	using namespace std;

	default_random_engine rng;
	normal_distribution<double> gaussian(mean, stddev);
	for (i=0; i<elems; i++){
		in[i] = (T) gaussian(rng);
	}

	transpose(in, out, elems);

	ofstream out_stream;
	char out_name[50];

	sprintf(out_name, "raw_%s_%.2f_pm_%.2f.bin", typestr, mean, stddev);
	out_stream.open(out_name, ios::out | ios::binary);
	out_stream.write((char*)in, elems*sizeof(T));
	out_stream.close();

	sprintf(out_name, "transposed_%s_%.2f_pm_%.2f.bin", typestr, mean, stddev);
	out_stream.open(out_name, ios::out | ios::binary);
	out_stream.write((char*)out, elems*sizeof(T));
	out_stream.close();

	free(in);
	free(out);
}

template <typename T>
void
create_test_files_from_arr(T *arr, size_t elems)
{
	T *out = (T*) calloc(elems, sizeof(T));
	if (!out){
		printf("Could not alloc memory\n");
		exit(1);
	}

	using namespace std;

	transpose(arr, out, elems);

	ofstream out_stream;
	char out_name[50];

	out_stream.open("raw_from_dat.bin", ios::out | ios::binary);
	out_stream.write((char*)arr, elems*sizeof(T));
	out_stream.close();

	out_stream.open("transposed_from_dat.bin", ios::out | ios::binary);
	out_stream.write((char*)out, elems*sizeof(T));
	out_stream.close();

	free(out);
}

void
_register_types(void)
{
	/* Hack to prevent execution of any called functions */
	int j = 1;
	if (j)
		exit(1);

	float *f;
	int *i;
	double *d;
	long *l;
	const char *str;

	create_test_files_from_arr(f, (size_t) 0);
	create_test_files_from_arr(i, (size_t) 0);
	create_test_files_from_arr(d, (size_t) 0);
	create_test_files_from_arr(l, (size_t) 0);

	create_test_files<int>(size_t (0), 0.0, 0.0, str);
	create_test_files<float>(size_t (0), 0.0, 0.0, str);
	create_test_files<double>(size_t (0), 0.0, 0.0, str);
	create_test_files<long>(size_t (0), 0.0, 0.0, str);
}
