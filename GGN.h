#ifndef GGN_LIB
#define GGN_LIB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define GGN_MAX_NUM_LEN 1000
typedef struct GGN
{
    unsigned char number[GGN_MAX_NUM_LEN];
    unsigned long long length;
} GGN;
int GGN_sum(GGN *n1, GGN *n2, GGN *result);
GGN *GGN_init(const char *string_number);
void GGN_set_char_to_all(GGN *GGN_n, unsigned char n);
void GGN_print(GGN *GGN_n);
int GGN_set_int(GGN *GGN_n, int number);
#endif