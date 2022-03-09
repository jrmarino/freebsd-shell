#ifndef QSORT_S_HEADER
#define QSORT_S_HEADER

#include <stddef.h>
#include <limits.h>
#include <inttypes.h>
#include <stdio.h>

int git_qsort_s(void *base, size_t nmemb, size_t size,
		int (*compar)(const void *, const void *, void *), void *ctx);

#define bitsizeof(x)  (CHAR_BIT * sizeof(x))

#define maximum_unsigned_value_of_type(a) \
    (UINTMAX_MAX >> (bitsizeof(uintmax_t) - bitsizeof(a)))

#define unsigned_mult_overflows(a, b) \
    ((a) && (b) > maximum_unsigned_value_of_type(a) / (a))

static inline size_t st_mult(size_t a, size_t b)
{
	if (unsigned_mult_overflows(a, b)) {
		printf("size_t overflow: %"PRIuMAX" * %"PRIuMAX,
		    (uintmax_t)a, (uintmax_t)b);
		exit(1);
	}
	return a * b;
}

#endif
