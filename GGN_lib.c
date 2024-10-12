#include "GGN_lib.h"
GGN *GGN_i()
{
    GGN *GGN_num = malloc(sizeof(GGN));
    if (GGN_num == NULL)
    {
        exit(1);
    }
    GGN_num->length = 0;
    GGN_setZero(GGN_num);
    GGN_num->sign = 0;
    return GGN_num;
}
GGN *GGN_init_GGN(GGN *GGN_n)
{
    GGN *GGN_num = GGN_i();
    GGN_set_GGN(GGN_n, GGN_num);
    return GGN_num;
}
int GGN_free(GGN *n1)
{
    free(n1);
    if (n1)
        return 0;
    return 1;
}
int GGN_free_all(int ammount, ...)
{
    va_list pointers_all;
    va_start(pointers_all, ammount);
    for (; ammount > 0; ammount--)
        free(va_arg(pointers_all, GGN *));
    return 1;
}
int GGN_sum(GGN *n1, GGN *n2, GGN *result)
{
    if (n1->sign && !n2->sign)
    {
        n1->sign = 0;
        GGN_minus(n2, n1, result);
        if (n1 != result)
            n1->sign = 1;
        return 1;
    }
    if (n2->sign && !n1->sign)
    {
        n2->sign = 0;
        GGN_minus(n1, n2, result);
        if (n2 != result)
            n2->sign = 1;
        return 1;
    }
    if (n1->sign && n2->sign)
        result->sign = 1;
    if (!(n1 && n2 && result))
        return 0;
    int toBeAdded = 0;
    int nextreg = 0;
    for (unsigned long int index = 0; (index <= n1->length || index <= n2->length) && index < GGN_MAX_NUM_LEN; index++)
    {

        toBeAdded = n1->number[index] + n2->number[index] + nextreg;
        nextreg = 0;
        if (toBeAdded > 9)
        {
            nextreg = 1;
            toBeAdded -= 10;
        }
        result->number[index] = toBeAdded;
        if ((result->number[index] > 0) && (result->length < index + 1))
            result->length = index + 1;
    }
    return 1;
}

GGN *GGN_init(const char *string_number)
{
    GGN *GGN_num = GGN_i();
    GGN_num->length = strlen(string_number);
    for (int index = 0; (index < GGN_num->length) && (string_number[GGN_num->length - 1 - index] != '-'); index++)
        GGN_num->number[index] = string_number[GGN_num->length - 1 - index] - '0';
    if (string_number[0] == '-')
    {
        GGN_num->length--;
        GGN_num->sign = 1;
    }
    return GGN_num;
};
void GGN_setZero(GGN *GGN_n)
{
    memset(GGN_n->number, 0, GGN_MAX_NUM_LEN);
}
void GGN_print(GGN *GGN_n)
{
    if (GGN_n->sign)
    {
        printf("-");
    }
    for (int index = 0; index < GGN_n->length; index++)
    {
        printf("%d", GGN_n->number[GGN_n->length - 1 - index]);
    }
}
int GGN_num_str(GGN *GGN_n, char *str, int SIZE)
{
    memset(str, 0, SIZE);
    int add = 0;
    if (GGN_n->sign)
    {
        str[0] = '-';
        add = 1;
    }
    for (int index = 0; (index < GGN_n->length) && (index + add < SIZE); index++)
    {
        str[add + index] = GGN_n->number[GGN_n->length - 1 - index] + '0';
    }
    return add + GGN_n->length;
}

int GGN_set_int(GGN *GGN_n, int number)
{

    if (number < 0)
    {
        number *= -1;
        GGN_n->sign = 1;
    }
    else

        GGN_n->sign = 0;

    GGN_setZero(GGN_n);

    GGN_n->length = number ? log10(number) + 1 : 1;
    for (int index = 0; index < GGN_n->length; index++)
    {
        GGN_n->number[index] = number % 10;
        number /= 10;
    }
    return 1;
}
int GGN_set_GGN(GGN *GGN_n1, GGN *GGN_n2)
{
    GGN_setZero(GGN_n2);
    GGN_n2->length = GGN_n1->length;
    GGN_n2->sign = GGN_n1->sign;
    for (int index = 0; index < GGN_n2->length; index++)
        GGN_n2->number[index] = GGN_n1->number[index];
    return 1;
}
int GGN_n1_compare_with_n2(GGN *GGN_n1, GGN *GGN_n2)
{
    if (GGN_n1->length > GGN_n2->length)
        return 1;
    else if (GGN_n1->length < GGN_n2->length)
        return -1;
    unsigned long index = GGN_n1->length - 1;
    while (index + 1)
    {
        if (GGN_n1->number[index] > GGN_n2->number[index])
            return 1;
        else if (GGN_n1->number[index] < GGN_n2->number[index])
            return -1;
        index--;
    }
    return 0;
}

int GGN_n_compare_with_int(GGN *GGN_n, int num)
{
    GGN *numInt = GGN_init("0");
    GGN_set_int(numInt, num);
    int result = GGN_n1_compare_with_n2(GGN_n, numInt);
    free(numInt);
    return result;
}
int GGN_n_add_int(GGN *GGN_n, int num, GGN *result)
{
    return 1;
}
int GGN_mult(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result)
{
    if ((GGN_n1->length == 0) || (GGN_n2->length == 0))
    {
        GGN_setZero(GGN_result);
        GGN_result->length = 0;
        GGN_result->sign = 0;
        return 1;
    }
    GGN *GGN_result_oper = GGN_init_int(0);
    GGN *GGN_final = GGN_init_int(0);
    for (int index = 0; index < GGN_n2->length; index++)
    {
        GGN_set_int(GGN_result_oper, 0);
        int toBeAdded = 0;
        for (int num = 0; (num <= GGN_n1->length) && (num < GGN_MAX_NUM_LEN); num++)
        {
            toBeAdded = GGN_result_oper->number[num] + GGN_n1->number[num] * GGN_n2->number[index];
            GGN_result_oper->number[num] = toBeAdded % 10;
            GGN_result_oper->number[num + 1] = toBeAdded / 10;
            if (GGN_result_oper->number[num] > 0)
            {
                GGN_result_oper->length = num + 1;
            }
        }
        GGN_mult_pow_10(GGN_result_oper, index);
        GGN_sum(GGN_final, GGN_result_oper, GGN_final);
    }
    GGN_set_GGN(GGN_final, GGN_result);
    free(GGN_final);
    free(GGN_result_oper);
    if (GGN_n1->sign != GGN_n2->sign)
        GGN_result->sign = 1;
    return 1;
}
int GGN_mult_pow_10(GGN *GGN_n, unsigned long long power_of_10)
{
    if (!(GGN_n->length + power_of_10 < GGN_MAX_NUM_LEN))
        return 0;
    for (int index = GGN_n->length - 1; index >= 0; index--)
        GGN_n->number[index + power_of_10] = GGN_n->number[index];
    for (int index = 0; index < power_of_10; index++)
        GGN_n->number[index] = 0;
    GGN_n->length += power_of_10;
    return 1;
}

GGN *GGN_init_int(int num)
{
    GGN *GGN_num = GGN_i();
    GGN_set_int(GGN_num, num);
    return GGN_num;
}
int GGN_minus(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result)
{
    if (GGN_n1->sign != GGN_n2->sign)
    {
        char sign = GGN_n1->sign;
        GGN_n1->sign = GGN_n2->sign = 0;
        GGN_sum(GGN_n1, GGN_n2, GGN_result);
        GGN_n1->sign = sign;
        GGN_n2->sign = !sign;
        GGN_result->sign = sign;
        return 1;
    }
    GGN *o1 = GGN_n1, *o2 = GGN_n2;
    switch (GGN_n1_compare_with_n2(o1, o2))
    {
    case 1:
        break;
    case 0:
        GGN_set_int(GGN_result, 0);
        return 1;
        break;
    case -1:
        o1 = GGN_n2;
        o2 = GGN_n1;
        GGN_result->sign = GGN_n2->sign ? 0 : 1;
        break;
    }
    int next = 0;
    int result = 0;
    int length_n1 = GGN_n1->length;
    for (int index = 0; (index < length_n1 || index < GGN_n2->length) && index < GGN_MAX_NUM_LEN; index++)
    {
        result = o1->number[index] - o2->number[index] + next;
        next = 0;
        if (result < 0)
        {
            next = -1;
            result += 10;
        }
        GGN_result->number[index] = result;
        if (result)
            GGN_result->length = index + 1;
    }
    return 1;
}

int GGN_devide(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result)
{
    if (GGN_n1_compare_with_n2(GGN_n2, GGN_n1) == 1)
    {
        GGN_set_int(GGN_result, 0);
        return 1;
    }
    if (!GGN_n1_compare_with_n2(GGN_n2, GGN_n1))
    {
        GGN_set_int(GGN_result, 1);
        return 1;
    }
    GGN *result = GGN_init_int(0);

    GGN *minused = GGN_init_int(0);

    GGN *current_multiplier = GGN_init_int(0);

    GGN *curernt_devisor = GGN_i();
    GGN_set_GGN(GGN_n2, curernt_devisor);

    GGN *toBeDevised = GGN_i();
    GGN_set_GGN(GGN_n1, toBeDevised);

    while (GGN_n1_compare_with_n2(toBeDevised, GGN_n2) == 1)
    {
        if (toBeDevised->length > GGN_n2->length + 1)
        {
            GGN_set_int(current_multiplier, 1);
            GGN_mult_pow_10(current_multiplier, toBeDevised->length - GGN_n2->length - 1);
            GGN_sum(current_multiplier, result, result);
            GGN_mult(current_multiplier, GGN_n2, curernt_devisor);
            GGN_minus(toBeDevised, curernt_devisor, toBeDevised);
        }
        else
        {
            for (int counter = 9; counter > 0; counter--)
            {
                GGN_set_int(current_multiplier, counter);
                GGN_mult(current_multiplier, GGN_n2, curernt_devisor);
                int compare = GGN_n1_compare_with_n2(toBeDevised, curernt_devisor);
                if (compare == 1 || compare == 0)
                {
                    GGN_sum(current_multiplier, result, result);
                    GGN_minus(toBeDevised, curernt_devisor, toBeDevised);
                    break;
                }
            }
        }
    }
    GGN_set_GGN(result, GGN_result);
    if (GGN_n1->sign != GGN_n2->sign)
    {
        GGN_result->sign = 1;
    }
    GGN_free_all(5, result, minused, current_multiplier, curernt_devisor, toBeDevised);
    return 1;
}
int GGN_devide_pow_10(GGN *GGN_n, unsigned long long power_of_10)
{
    if (!power_of_10)
        return 1;
    if (GGN_n->length < power_of_10)
        power_of_10 = GGN_n->length;

    for (int index = power_of_10; index < GGN_n->length; index++)
        GGN_n->number[index - power_of_10] = GGN_n->number[index];
    for (int index = GGN_n->length - power_of_10; index < GGN_n->length; index++)
        GGN_n->number[index] = 0;

    GGN_n->length -= power_of_10;
    return 1;
}
int _lib_GGN_second_part(GGN *GGN_n, unsigned long long second)
{
    unsigned long long second_input = second;
    while (second < GGN_n->length)
        GGN_n->number[second++] = 0;
    GGN_n->length = second_input > GGN_n->length ? GGN_n->length : second_input;
    return 1;
}
// Karatsuba multiplication
int _beta_GGN_effective_mult(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result)
{
    if ((GGN_n1->length <= 2) || (GGN_n2->length <= 2))
    {
        GGN_mult(GGN_n1, GGN_n2, GGN_result);
        return 1;
    }

    GGN *n1_cp = GGN_init_GGN(GGN_n1);
    GGN *n2_cp = GGN_init_GGN(GGN_n2);

    int second_length;
    if (n1_cp->length > n2_cp->length)
        second_length = n1_cp->length - n1_cp->length / 2;
    else
        second_length = n2_cp->length - n2_cp->length / 2;

    GGN *mult_1 = GGN_init_GGN(n1_cp);
    GGN *mult_2 = GGN_init_GGN(n2_cp);

    GGN_devide_pow_10(n1_cp, second_length);
    _lib_GGN_second_part(mult_1, second_length);
    GGN_devide_pow_10(n2_cp, second_length);
    _lib_GGN_second_part(mult_2, second_length);

    GGN *ab = GGN_i();
    _beta_GGN_effective_mult(n1_cp, n2_cp, ab);
    GGN *a0b0 = GGN_i();
    _beta_GGN_effective_mult(mult_1, mult_2, a0b0);

    GGN_sum(n1_cp, mult_1, mult_1);
    GGN_sum(n2_cp, mult_2, mult_2);

    _beta_GGN_effective_mult(mult_1, mult_2, mult_1);

    GGN_minus(mult_1, ab, mult_1);
    GGN_minus(mult_1, a0b0, mult_1);

    GGN_mult_pow_10(ab, second_length * 2);
    GGN_mult_pow_10(mult_1, second_length);

    GGN_set_GGN(ab, GGN_result);
    GGN_sum(a0b0, GGN_result, GGN_result);
    GGN_sum(mult_1, GGN_result, GGN_result);

    GGN_free_all(6, mult_1, mult_2, n1_cp, n2_cp, ab, a0b0);
    return 1;
}
