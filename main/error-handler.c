#include <stdio.h>
#include "error-handler.h"

void errorHandler_printErrors(STATUS_T* status, uint8_t size)
{
    for(uint8_t i = 0; i < size; i++)
    {
        switch(status[i])
        {
            case FAILED:
            {
                printf("FAILED\n");
                break;
            }
            case SUCCESS:
            {
                printf("SUCCESS\n");
                break;
            }
            case STRING_TOO_LONG:
            {
                printf("STRING TOO LONG\n");
                break;
            }
            case POINTER_IS_NULL:
            {
                printf("POINTER IS NULL\n");
                break;
            }
            case OUT_OF_SPACE:
            {
                printf("OUT OF SPACE\n");
                break;
            }
            case DUPLICATE:
            {
                printf("DUPLICATE\n");
                break;
            }
            case AD_CAPACITY_REACHED:
            {
                printf("ADD CAPACITY REACHED\n");
                break;
            }
            case COMPANY_NOT_FOUND:
            {
                printf("COMPANY NOT FOUND\n");
                break;
            }
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

