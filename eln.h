#ifndef ELN_LIB
#define ELN_LIB

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define ELN_MAX_LEN 400000

typedef unsigned char digit;

typedef struct elNum
{
    digit *number;
    unsigned long long length;
    unsigned char sign;
    unsigned long long size;
} elNum;
/// @brief  Sum of two elNum numbers
/// @param elNum_n1 first number
/// @param elNum_n2 second number
/// @param elNum_result result
/// @return returns 1 if sucsess
int plus_el(elNum *elNum_n1, elNum *elNum_n2, elNum *elNum_result);

/// @brief Initialization with const char *
/// @param string_number number represented by string
/// @return Returns a pointer to struct with number
elNum *init_el(const char *string_number);

/// @brief Sets zeros to the type elNum
/// @param elNum_n Pointer
/// @param n Char (from '0' to '9' reccomended)
void set_zeros_el(elNum *elNum_n);

/// @brief Prints elNum number
/// @param elNum_n elNum number
void print_el(elNum *elNum_n);

int num_str_el(elNum *elNum_n, char *str, int SIZE);

/// @brief Sets given int to elNum number
/// @param elNum_n elNum number
/// @param number Number that will be handaled (positive numbers reccomended)
/// @return Operation status
int set_cnum_el(elNum *elNum_n, long long int number);

/// @brief Sets elNum_n1 to elNum_n2
/// @param elNum_n1
/// @param elNum_n2
/// @return Operation status
int set_elNum_el(elNum *elNum_n1, elNum *elNum_n2);

/// @brief Comparison of two numbers
/// @return Returns 1 if n1 > n2, 0 if n1 == n2, -1 if n1 < n2
int cmp_el(elNum *elNum_n1, elNum *elNum_n2);

int cmpi_el(elNum *elNum_n, int num);

/// @brief init_el with no arguments
/// @return ptr to the struct (memory is allocated only in this function)
elNum *i_el();

int free_el(elNum *n1);

int freen_el(int ammount, ...);

/// @brief The most recomended function for init_el
/// @param num
/// @return you know it
elNum *init_int_el(int num);

int mltp10_el(elNum *, unsigned long long power_of_10);

int mult_el(elNum *elNum_n1, elNum *elNum_n2, elNum *elNum_result);

int minus_el(elNum *elNum_n1, elNum *elNum_n2, elNum *elNum_result);

int devide_el(elNum *elNum_n1, elNum *elNum_n2, elNum *elNum_result);

int _lib_second_part(elNum *elNum_n, unsigned long long second_part_length);

int devide_pow_10(elNum *elNum_n, unsigned long long power_of_10);

int _beta_effective_mult(elNum *elNum_n1, elNum *elNum_n2, elNum *elNum_result);

elNum *init_elNum(elNum *elNum_n);

int _beta_lib_firstpart_10(elNum *elNum_n, unsigned long long power_of_10, elNum *elNum_result);

static int _swap_el(void *ptr1, void *ptr2, size_t num);

elNum *i_size_el(size_t n);
#endif