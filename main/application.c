#include "application.h"
#include "utils.h"
#include "insertion-sort.h"
void application_init(Application* app)
{
    return;
}

int add_company(Application* app)
{
    insert_company(&app->manager, "Dahl Sverige AB", "Buy pipes", NULL, BLINKING, NONE, 16000);
}