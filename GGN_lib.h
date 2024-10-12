#ifndef GGN_LIB
#define GGN_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <stdarg.h>
// will be used later
#define GGN_MAX_NUM_LEN 35000
typedef struct GGN
{
    unsigned char number[GGN_MAX_NUM_LEN];
    unsigned long long length;
    unsigned char sign;
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

/// @brief Sets zeros to the type GGN
/// @param GGN_n Pointer
/// @param n Char (from '0' to '9' reccomended)
void GGN_setZero(GGN *GGN_n);

/// @brief Prints GGN number
/// @param GGN_n GGN number
void GGN_print(GGN *GGN_n);

int GGN_num_str(GGN *GGN_n, char *str, int SIZE);

/// @brief Sets given int to GGN number
/// @param GGN_n GGN number
/// @param number Number that will be handaled (positive numbers reccomended)
/// @return Operation status
int GGN_set_int(GGN *GGN_n, int number);

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
/// @return ptr to the struct (memory is allocated only in this function)
GGN *GGN_i();

int GGN_free(GGN *n1);

int GGN_free_all(int ammount, ...);

/// @brief The most recomended function for init
/// @param num
/// @return you know it
GGN *GGN_init_int(int num);

int GGN_mult_pow_10(GGN *, unsigned long long power_of_10);

int GGN_mult(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result);

int GGN_minus(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result);

int GGN_devide(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result);

int _lib_GGN_second_part(GGN *GGN_n, unsigned long long second_part_length);
int GGN_devide_pow_10(GGN *GGN_n, unsigned long long power_of_10);
int _beta_GGN_effective_mult(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result);
GGN *GGN_init_GGN(GGN *GGN_n);
#endif
