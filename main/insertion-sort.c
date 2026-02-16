#include <assert.h>
#include "insertion-sort.h"


static void swap(uint8_t* a, uint8_t* b)
{
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}


void sort_companies(Application* app)
{
    for(int i = 1; i < app->size; i++)
    {
        uint8_t k = 0;
        uint8_t* indexes = app->indexes;
        uint8_t index = indexes[ i ];
        uint8_t flag = 0;
        Company* companies = app->companies;
        char letter1 = companies[ index - 1 ].name[ k ];
        char letter2 = companies[ index  ].name[ k ];
        while(letter1 == letter2)
        {
            assert(letter1 != '\0' || letter1 != '\0');
            letter1 = companies[ index - 1 ].name[ k ];
            letter2 = companies[ index  ].name[ k ];
            k++;
        }
        k = 0;
        if(letter1 != '\0' && letter2 == '\0')
        {
            swap(&indexes[i - 1], &indexes[ i ] );
            flag = 1;
        }
        
        if(letter1 < letter2) 
        {
            if(!flag) { swap( &indexes[ i - 1 ], &indexes[ i ] ); }

            for(int j = i - 1; j > 0; j-- )
            {
                index = indexes[ j ];
                letter1 = companies[ index ].name[ k ];
                letter2 = companies[ index - 1 ].name[ k ];
                if(letter1 < letter2)
                {
                    swap(&indexes[ j ], &indexes[ j - 1 ]);
                }
            }
            flag = 0;
        }
    }
}