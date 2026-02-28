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
    int64_t startTime;
    int64_t currentTime;
    int64_t tempTime;
    uint8_t index;
    bool flag;
    bool flag2;
    char ad[AD_STR_SIZE_MAX];
    char adBuffer[LCD_CHAR_SIZE + 1]; //+1 for null terminator
    char nameBuffer[LCD_CHAR_SIZE + 1]; //+1 for null terminator
}AdDisplayer;
void adDisplayer_init(AdDisplayer*);
void adDisplayer_print(AdDisplayer*, Company* );
void adDisplayer_clearBuffer(AdDisplayer*);
#endif