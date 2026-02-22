#ifndef AD_DISPLAYER_H
#define AD_DISPLAYER_H
#include "companies.h"
#include "lcd-screen.h"

typedef struct AdDisplayer
{
    LcdScreen screen;
}AdDisplayer;
void adDisplayer_init(AdDisplayer*);
void adDisplayer_print(AdDisplayer*, Company* );
#endif