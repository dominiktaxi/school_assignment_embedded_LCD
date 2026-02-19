#include "application.h"
#include "utils.h"
void application_init(Application* app)
{
    return;
}

int add_company(Application* app, const char*)
{
    insert_company(&app->manager, "Dahl Sverige AB", "Buy pipes", NULL, BLINKING, NONE, 16000);
    return 1;
}