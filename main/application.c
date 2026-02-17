#include "application.h"
#include "utils.h"
#include "insertion-sort.h"
void application_init(Application* app)
{
    app->capacity = (uint8_t)(sizeof(app->companies) / sizeof(app->companies[0]));
    app->size = 0;
    for(int i = 0; i < MAX_COMPANIES; i++)
    {
        app->indexes[ i ] = i;
    }
}

int add_company(Application* app, const char* name)
{
    for(int i = 0; i < app->size; i++)
    {
        if(app->companies[ app->indexes[ i ] ].name == name)
        {
            return 0;
        }
    }
    app->companies[ app->indexes[ app->size ] ].name = name;
    app->size++;
    return 1;
}

int remove_company(Application* app, const char* name)
{
    for(int i = 0; i < app->size; i++)
    {
        if(app->companies[ app->indexes[ i ] ].name == name)
        {
            swap(&app->indexes[ i ], &app->indexes[ app->size - 1 ]);
            app->size--;
            return 1;
        }
    }
    return 0;
}

int add_payment(Application* app, const char* name, uint32_t payment)
{
    for(int i = 0; i < app->size; i++)
    {
        if(app->companies[ app->indexes[i] ].name == name)
        {
            app->companies[ app->indexes[i] ].paid_amount += payment;
            return 1;
        }
    }
    return 0;
}

void sort(Application* app)
{
    sort_companies(app);
}

void list_companies(const Application* app)
{
    for(int i = 0; i < app->size; i++)
    {
        printf("%s  -> ", app->companies[ app->indexes[ i ] ].name);
        printf("%s  -> \n", app->companies[ i ].name);
    }
}

void list_indexes(const Application* app)
{
    for(int i = 0; i < app->size; i++)
    {
        printf("index: %d  value: %u\n", i, app->indexes[i]);
    }
}

