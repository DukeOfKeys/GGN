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
/// @brief  Sum of two GGN numbers
/// @param GGN_n1 first number
/// @param GGN_n2 second number
/// @param GGN_result result
/// @return returns 1 if sucsess
int GGN_sum(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result);
/// @brief Initialization with const char *
/// @param string_number number represented by string
/// @return Returns a pointer to struct with number
GGN *GGN_init(const char *string_number);
/// @brief Sets one char to all places in the GGN number
/// @param GGN_n Pointer
/// @param n Char (from '0' to '9' reccomended)
void GGN_set_char_to_all(GGN *GGN_n, unsigned char n);
/// @brief Prints GGN number
/// @param GGN_n GGN number
void GGN_print(GGN *GGN_n);
/// @brief Sets given int to GGN number
/// @param GGN_n GGN number
/// @param number Number that will be handaled (positive numbers reccomended)
/// @return Operation status
int GGN_set_int(GGN *GGN_n, int number);
/// @brief Multiplication
/// @param GGN_n1
/// @param GGN_n2
/// @param GGN_result
/// @return Operation status
int GGN_multiply(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result);
/// @brief Sets GGN_n1 to GGN_n2
/// @param GGN_n1
/// @param GGN_n2
/// @return Operation status
int GGN_set_GGN(GGN *GGN_n1, GGN *GGN_n2);
/// @brief Comparison of two numbers
/// @return Returns 1 if n1 > n2, 0 if n1 == n2, -1 if n1 < n2
int GGN_n1_compare_with_n2(GGN *GGN_n1, GGN *GGN_n2);
int GGN_n_compare_with_int(GGN *GGN_n, int num);
int GGN_n_add_int(GGN *GGN_n, int num, GGN *result);
/// @brief init with no arguments
/// @return
GGN *GGN_i();
GGN *GGN_init_int(int num);
int GGN_mult_pow_10(GGN *, int power_of_10);
int GGN_fast_mult(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result);
#endif