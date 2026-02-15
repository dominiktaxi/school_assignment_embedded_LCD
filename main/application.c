#include "application.h"

void application_init(Application* app)
{
    app->capacity = (uint8_t)(sizeof(app->companies) / sizeof(app->companies[0]));
    app->size = 0;
}

void add_company(Application* app, const char* name)
{
    app->companies[app->size].name = name;
    app->size++;
}

void add_payment(const Application* app, const char* name, uint32_t payment)
{

}