#include <stdio.h>
#include "error-handler.h"

void errorHandler_printErrors(STATUS_T status, const char* type)
{
    switch(status)
    {
        case FAILED:
        {
            printf("%s FAILED\n", type);
            break;
        }
        case SUCCESS:
        {
            printf("%s SUCCESS\n", type);
            break;
        }
        case STRING_TOO_LONG:
        {
            printf("%s STRING TOO LONG\n", type);
            break;
        }
        case POINTER_IS_NULL:
        {
            printf("%s POINTER IS NULL\n", type);
            break;
        }
        case OUT_OF_SPACE:
        {
            printf("%s OUT OF SPACE\n", type);
            break;
        }
        case DUPLICATE:
        {
            printf("%s DUPLICATE\n", type);
            break;
        }
        case AD_CAPACITY_REACHED:
        {
            printf("%s AD CAPACITY REACHED\n", type);
            break;
        }
        case COMPANY_NOT_FOUND:
        {
            printf("%s, COMPANY NOT FOUND\n", type);
            break;
        }
    }
}

// typedef enum STATUS_T
// {
//     FAILED,
//     SUCCESS,
//     STRING_TOO_LONG,
//     POINTER_IS_NULL,
//     OUT_OF_SPACE,
//     DUPLICATE,
//     AD_CAPACITY_REACHED,
//     COMPANY_NOT_FOUND
// }STATUS_T;

