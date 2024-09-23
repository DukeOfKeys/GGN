#include "GGN.h"
int GGN_sum(GGN *n1, GGN *n2, GGN *result)
{
    GGN_set_char_to_all(result, 0);
    int toBeAdded = 0;
    int addIndx = 1;
    for (unsigned long int index = 0; (index <= n1->length || index <= n2->length) && index < GGN_MAX_NUM_LEN; index++)
    {
        toBeAdded = n1->number[index] + n2->number[index] - '0' * 2;
        if (toBeAdded + result->number[index] > 9)
        {
            addIndx = 1;
            while (addIndx + index < GGN_MAX_NUM_LEN)
            {
                if (result->number[addIndx + index] - '0' < 9)
                {
                    result->number[addIndx + index]++;
                    break;
                }
                addIndx++;
            }

            toBeAdded -= 10;
        }
        result->number[index] += toBeAdded + '0';
        if (result->number[index] - '0' > 0)
        {
            result->length = index + 1;
        }
    }
    return 1;
}
GGN *GGN_init(const char *string_number)
{
    GGN *GGN_num = malloc(sizeof(GGN));
    if (GGN_num == NULL)
    {
        abort();
    }
    GGN_num->length = strlen(string_number);
    GGN_set_char_to_all(GGN_num, '0');
    for (int index = 0; index < GGN_num->length; index++)
        GGN_num->number[index] = string_number[GGN_num->length - 1 - index];
    return GGN_num;
};
void GGN_set_char_to_all(GGN *GGN_n, unsigned char n)
{
    for (int index = 0; index < GGN_MAX_NUM_LEN; index++)
        GGN_n->number[index] = n;
}
void GGN_print(GGN *GGN_n)
{
    for (int index = 0; index < GGN_n->length; index++)
    {
        printf("%c", GGN_n->number[GGN_n->length - 1 - index]);
    }
    printf("\n");
}
int GGN_set_int(GGN *GGN_n, int number)
{
    GGN_set_char_to_all(GGN_n, '0');
    GGN_n->length = log10(number) + 1;
    for (int index = 0; index < GGN_n->length; index++)
    {
        GGN_n->number[index] = number % 10 + '0';
        number /= 10;
    }
    return 1;
}
int GGN_multiply(GGN *GGN_n1, GGN *GGN_n2, GGN *GGN_result)
{
}