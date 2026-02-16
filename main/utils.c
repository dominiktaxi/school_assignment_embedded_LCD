#include "utils.h"

void utils_toLower(const char** text)
{
    char a = 0;

    for(int i = 0; *text[i] != '\0'; i++)
    {
        a = *text[i];
    }
}

void swap(uint8_t* a, uint8_t* b)
{
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}
