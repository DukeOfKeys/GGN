#include "eln.h"
elNum *i_el()
{
    elNum *num = calloc(1, sizeof(elNum));
    if (!num)
        exit(EXIT_FAILURE);

    num->size = ELN_MAX_LEN;
    num->number = (digit *)calloc(1, num->size);
    if (!num->number)
        exit(EXIT_FAILURE);
    return num;
}
elNum *i_size_el(size_t n)
{
    elNum *num = calloc(1, sizeof(elNum));
    if (!num)
        exit(EXIT_FAILURE);

    num->size = n;
    num->number = (digit *)calloc(1, num->size);
    if (!num->number)
        exit(EXIT_FAILURE);
    return num;
}
elNum *init_el(const char *str)
{
    elNum *num = i_el();
    num->length = strlen(str);
    for (int index = 0; (index < num->length) && (str[num->length - 1 - index] != '-'); index++)
        num->number[index] = str[num->length - 1 - index] - '0';
    if (str[0] == '-')
    {
        num->length--;
        num->sign = 1;
    }
    return num;
};

elNum *init_int_el(int num)
{
    elNum *el_ptr = i_el();
    set_cnum_el(el_ptr, num);
    return el_ptr;
}
elNum *init_elNum(elNum *n)
{
    elNum *num = i_el();
    set_elNum_el(n, num);
    return num;
}
int free_el(elNum *n)
{
    free(n->number);
    free(n);
    if (n)
        return 0;
    return 1;
}
int freen_el(int n, ...)
{
    va_list pointers_all;
    va_start(pointers_all, n);
    for (; n > 0; n--)
        free_el(va_arg(pointers_all, elNum *));
    return 1;
}
int plus_el(elNum *n1, elNum *n2, elNum *result)
{

    if (n1->sign != n2->sign)
    {
        char sn1 = n1->sign, sn2 = n2->sign, snr;
        n1->sign = n2->sign = 0;
        minus_el(n1->sign ? n2 : n1, n1->sign ? n1 : n2, result);
        snr = result->sign;
        n1->sign = sn1;
        n2->sign = sn2;
        result->sign = snr;
        return 1;
    }

    result->sign = n1->sign;
    if (n1->length < n2->length)
        _swap_el(&n1, &n2, sizeof(elNum *));
    unsigned long long index;
    digit nextreg = 0;
    for (index = 0; index < n2->length; index++)
    {
        nextreg = n1->number[index] + n2->number[index] + nextreg;
        result->number[index] = nextreg % 10;
        nextreg = nextreg / 10;
    }

    while (index < n1->length && nextreg > 0)
    {
        result->number[index] = n1->number[index] + nextreg;
        nextreg = 0;
        if (result->number[index] > 9)
        {
            nextreg = 1;
            result->number[index] -= 10;
        }
        index++;
    }
    if ((index == n1->length) && nextreg)
    {
        result->number[index] = 1;
        result->length = index + 1;
        return 1;
    }
    if (n1->length > index)
        memcpy(result->number + index, n1->number + index, n1->length - index);

    result->length = n1->length > index ? n1->length : index;
    return 1;
}

void set_zeros_el(elNum *n)
{
    memset(n->number, 0, n->size);
}
void print_el(elNum *n)
{
    if (n->sign)
        printf("-");
    int index = 0;
    do
    {
        printf("%d", n->number[n->length - 1 - index]);
        index++;
    } while (index < n->length);
    printf("\n");
}
int num_str_el(elNum *n, char *str, int SIZE)
{
    memset(str, 0, SIZE);
    int add = 0;
    if (n->sign)
    {
        str[0] = '-';
        add = 1;
    }
    for (int index = 0; (index < n->length) && (index + add < SIZE); index++)
    {
        str[add + index] = n->number[n->length - 1 - index] + '0';
    }
    return add + n->length;
}

int set_cnum_el(elNum *n, long long int number)
{
    if (number < 0)
    {
        number *= -1;
        n->sign = 1;
    }
    else
        n->sign = 0;

    set_zeros_el(n);

    int index = 0;
    for (; number > 0; index++)
    {
        n->number[index] = number % 10;
        number /= 10;
    }
    n->length = index > 0 ? index : 1;
    return 1;
}
int set_elNum_el(elNum *n1, elNum *n2)
{
    set_zeros_el(n2);
    n2->length = n1->length;
    n2->sign = n1->sign;
    memcpy(n2->number, n1->number, n1->length);
    return 1;
}
int cmp_el(elNum *n1, elNum *n2)
{
    if (n1->length > n2->length)
        return 1;
    else if (n1->length < n2->length)
        return -1;
    unsigned long index = n1->length - 1;
    while (index + 1)
    {
        if (n1->number[index] > n2->number[index])
            return 1;
        else if (n1->number[index] < n2->number[index])
            return -1;
        index--;
    }
    return 0;
}

int cmpi_el(elNum *n, int num)
{
    elNum *numInt = init_el("0");
    set_cnum_el(numInt, num);
    int result = cmp_el(n, numInt);
    free_el(numInt);
    return result;
}
int mult_el(elNum *n1, elNum *n2, elNum *result)
{
    if ((n1->number[0] == 0 && n1->length <= 1) || (n2->number[0] == 0 && n2->length <= 1))
    {
        set_zeros_el(result);
        result->length = 1;
        result->sign = 0;
    }

    if (n1->length < n2->length)
        _swap_el(&n1, &n2, sizeof(elNum *));

    elNum *final = i_size_el(n1->length + n2->length);
    for (int index = 0; index < n2->length; index++)
    {
        int current_num = n2->number[index];
        if (current_num == 0)
            continue;
        digit r_cur = 0;
        int g_index;

        for (g_index = 0; g_index < n1->length; g_index++)
        {
            r_cur = final->number[g_index + index] + r_cur + n1->number[g_index] * current_num;
            final->number[g_index + index] = r_cur % 10;
            r_cur = r_cur / 10;
        }
        while (g_index + index < n1->length && r_cur)
        {
            r_cur = r_cur + n1->number[g_index + index];
            final->number[g_index + index] = r_cur % 10;
            r_cur = r_cur / 10;
            g_index++;
        }
        final->number[g_index + index] = r_cur;
        final->length = final->number[g_index + index] ? g_index + 1 + index : g_index + index;
    }
    set_elNum_el(final, result);
    free_el(final);
    if (n1->sign != n2->sign)
        result->sign = 1;
    return 1;
}
int mltp10_el(elNum *n, unsigned long long power_of_10)
{
    if (!(n->length + power_of_10 < ELN_MAX_LEN))
        return 0;
    memmove(n->number + power_of_10, n->number, n->length);
    memset(n->number, 0, power_of_10);
    n->length += power_of_10;
    return 1;
}

int minus_el(elNum *n1, elNum *n2, elNum *result)
{
    if (n1->sign != n2->sign)
    {
        char sign = n1->sign;
        n1->sign = n2->sign = 0;
        plus_el(n1, n2, result);
        n1->sign = sign;
        n2->sign = !sign;
        result->sign = sign;
        return 1;
    }
    switch (cmp_el(n1, n2))
    {
    case 1:
        break;
    case 0:
        set_cnum_el(result, 0);
        return 1;
    case -1:
        _swap_el(&n1, &n2, sizeof(elNum *));
        result->sign = n2->sign ? 0 : 1;
        break;
    }
    digit next = 0;
    digit op_r = 0;
    int length_n1 = n1->length;
    for (int index = 0; (index < length_n1 || index < n2->length) && index < ELN_MAX_LEN; index++)
    {
        op_r = n1->number[index] - n2->number[index] + next;
        next = 0;
        if (op_r < 0)
        {
            next = -1;
            op_r += 10;
        }
        result->number[index] = op_r;
        if (op_r)
            result->length = index + 1;
    }
    return 1;
}

int devide_el(elNum *n1, elNum *n2, elNum *result)
{
    if (cmp_el(n2, n1) == 1)
    {
        set_cnum_el(result, 0);
        return 1;
    }
    if (!cmp_el(n2, n1))
    {
        set_cnum_el(result, 1);
        return 1;
    }
    elNum *f_n = init_int_el(0);

    elNum *minused = init_int_el(0);

    elNum *current_multiplier = init_int_el(0);

    elNum *curernt_devisor = i_el();
    set_elNum_el(n2, curernt_devisor);

    elNum *toBeDevised = i_el();
    set_elNum_el(n1, toBeDevised);

    while (cmp_el(toBeDevised, n2) == 1)
    {
        if (toBeDevised->length > n2->length + 1)
        {
            set_cnum_el(current_multiplier, 1);
            mltp10_el(current_multiplier, toBeDevised->length - n2->length - 1);
            plus_el(current_multiplier, f_n, result);
            mult_el(current_multiplier, n2, curernt_devisor);
            minus_el(toBeDevised, curernt_devisor, toBeDevised);
        }
        else
        {
            for (int counter = 9; counter > 0; counter--)
            {
                set_cnum_el(current_multiplier, counter);
                mult_el(current_multiplier, n2, curernt_devisor);
                int compare = cmp_el(toBeDevised, curernt_devisor);
                if (compare == 1 || compare == 0)
                {
                    plus_el(current_multiplier, f_n, result);
                    minus_el(toBeDevised, curernt_devisor, toBeDevised);
                    break;
                }
            }
        }
    }
    set_elNum_el(f_n, result);
    if (n1->sign != n2->sign)
    {
        result->sign = 1;
    }
    freen_el(5, f_n, minused, current_multiplier, curernt_devisor, toBeDevised);
    return 1;
}
int devide_pow_10(elNum *n, unsigned long long power_of_10)
{
    if (!power_of_10)
        return 1;
    if (n->length < power_of_10)
    {
        n->length = 0;
        set_zeros_el(n);
        return 1;
    }
    for (int index = power_of_10; index < n->length; index++)
        n->number[index - power_of_10] = n->number[index];
    for (int index = n->length - power_of_10; index < n->length; index++)
        n->number[index] = 0;

    n->length -= power_of_10;
    return 1;
}
int _beta_lib_firstpart_10(elNum *n, unsigned long long power_of_10, elNum *result)
{
    result->sign = n->sign;
    if (n->length < power_of_10)
    {
        result->length = 0;
        result->number = n->number + n->length;
        return 1;
    }
    result->length = n->length - power_of_10;
    result->number = n->number + power_of_10;
    return 1;
}
int _beta_lib_second_part(elNum *n, unsigned long long second, elNum *result)
{
    result->sign = n->sign;
    result->number = n->number;
    if (n->length < second)
        result->length = n->length;
    else
        result->length = second;
    int index = result->length - 1;
    while (index + 1)
    {
        if (result->number[index])
            break;
        index--;
        result->length--;
    }
    return 1;
}
int _beta_effective_mult(elNum *n1, elNum *n2, elNum *result)
{

    char n1s = n1->sign;
    char n2s = n2->sign;
    n1->sign = n2->sign = 0;
    if ((n1->length <= 2) || (n2->length <= 2))
    {
        mult_el(n1, n2, result);
        return 1;
    }

    elNum first_part_n1, second_part_n1, first_part_n2, second_part_n2;
    int second_length = (n1->length > n2->length) ? n1->length - n1->length / 2 : n2->length - n2->length / 2;

    _beta_lib_firstpart_10(n1, second_length, &first_part_n1);

    _beta_lib_second_part(n1, second_length, &second_part_n1);

    _beta_lib_firstpart_10(n2, second_length, &first_part_n2);

    _beta_lib_second_part(n2, second_length, &second_part_n2);

    elNum *ab = i_size_el(first_part_n1.length + first_part_n2.length + second_length * 2);

    _beta_effective_mult(&first_part_n1, &first_part_n2, ab);

    elNum *a0b0 = i_size_el(second_part_n1.length + second_part_n2.length);
    _beta_effective_mult(&second_part_n1, &second_part_n2, a0b0);

    elNum *sum_n1 = i_size_el((second_part_n1.length + second_part_n2.length + 2) * 2 + second_length);
    elNum *sum_n2 = i_size_el(second_part_n2.length + 2);
    plus_el(&first_part_n1, &second_part_n1, sum_n1);
    plus_el(&first_part_n2, &second_part_n2, sum_n2);

    _beta_effective_mult(sum_n1, sum_n2, sum_n1);

    minus_el(sum_n1, ab, sum_n1);

    minus_el(sum_n1, a0b0, sum_n1);

    mltp10_el(ab, second_length * 2);
    mltp10_el(sum_n1, second_length);

    set_elNum_el(ab, result);
    plus_el(a0b0, result, result);
    plus_el(sum_n1, result, result);

    freen_el(4, ab, a0b0, sum_n2, sum_n1);
    n1->sign = n1s;
    n2->sign = n2s;
    result->sign = n1s || n2s ? (n1s && n2s ? 0 : 1) : 0;
    return 1;
}

static int _swap_el(void *ptr1, void *ptr2, size_t num)
{
    void *ptr_tmp = malloc(num);

    memcpy(ptr_tmp, ptr1, num);
    memcpy(ptr1, ptr2, num);
    memcpy(ptr2, ptr_tmp, num);
    free(ptr_tmp);
    return 1;
}