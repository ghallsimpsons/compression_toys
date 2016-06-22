#include <stdlib.h>

#define test_type(T, elems, mean, stddev) (create_test_files<T>(elems, mean, stddev, #T))

template <typename T> void create_test_files_from_arr(T *arr, size_t elems);

template <typename T> void assign_bit(T *in_ptr, T *out_ptr,
                                      size_t elem_index_out, size_t sig_bit,
                                      size_t out_bit);

template <typename T> void transpose(T *data_in, T *data_out, size_t len);

template <typename T> void create_test_files(size_t elems, double mean,
                                             double stddev, const char *typestr);

template <typename T> void create_test_files_from_arr(T *arr, size_t elems);
