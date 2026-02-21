#include <stdio.h>
#include "error-handler.h"

void errorHandler_printErrors(STATUS_T status)
{
    switch(status)
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
    }   
}