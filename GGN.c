#include "GGN.h"
GGN *GGN_i()
{
    GGN *GGN_num = malloc(sizeof(GGN));
    if (GGN_num == NULL)
    {
        abort();
    }
    GGN_num->length = 0;
    GGN_set_char_to_all(GGN_num, 0);
    return GGN_num;
}
int GGN_sum(GGN *n1, GGN *n2, GGN *result)
{
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
    for (int index = 0; index < GGN_num->length; index++)
        GGN_num->number[index] = string_number[GGN_num->length - 1 - index] - '0';
    return GGN_num;
};
void GGN_set_char_to_all(GGN *GGN_n, unsigned char n)
{
    memset(GGN_n, n, GGN_MAX_NUM_LEN);
}
void GGN_print(GGN *GGN_n)
{
    for (int index = 0; index < GGN_n->length; index++)
    {
        printf("%d", GGN_n->number[GGN_n->length - 1 - index]);
    }
    printf("\n");
}

int GGN_set_int(GGN *GGN_n, int number)
{
    GGN_set_char_to_all(GGN_n, 0);

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
    GGN_set_char_to_all(GGN_n2, 0);
    GGN_n2->length = GGN_n1->length;
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
    free(numInt);
    return GGN_n1_compare_with_n2(GGN_n, numInt);
}
int GGN_n_add_int(GGN *GGN_n, int num, GGN *result)
{
    return 1;
}
int GGN_mult(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result)
{
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
    return 1;
}
int GGN_mult_pow_10(GGN *GGN_n, int power_of_10)
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