#include "application.h"
#include "utils.h"
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
            swap(&app->indexes[ i ], &app->indexes[ app->size ]);
            app->size--;
            return 1;
        }
    }
    return 0;
}

void add_payment(const Application* app, const char* name, uint32_t payment)
{

}