#ifndef AD_DISPLAYER_H
#define AD_DISPLAYER_H
#define LCD_CHAR_SIZE 16
#include <stdbool.h>
#include "companies.h"
#include "lcd-screen.h"
typedef uint32_t(*RandomNumberGenerator)(void);
typedef int64_t(*GetTime)(void);
typedef enum
{
    ORGANIZE_BUFFER,
    CLEAR_SCREEN,
}TODO;

typedef struct AdDisplayer
{
    LcdScreen screen;
    int64_t* currentTime;
    int64_t tempTime;
    int64_t tempTime2;
    int64_t tempTime3;
    uint8_t index;
    uint8_t splitIndex;
    bool flag;
    bool on;
    //char ad[AD_STR_SIZE_MAX];
    char adBuffer[AD_STR_SIZE_MAX + 2]; //+2 for \0\0
    char nameBuffer[COMPANY_STR_NAME_SIZE_MAX + 2]; //+2 for \0\0
}AdDisplayer;
void adDisplayer_init(AdDisplayer*, int64_t*);
void adDisplayer_print(AdDisplayer*, Company* );
void adDisplayer_reset(AdDisplayer*, Company*);
#endif