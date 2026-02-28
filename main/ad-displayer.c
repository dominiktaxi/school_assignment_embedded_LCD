#include "ad-displayer.h"
#include <string.h>
#include <inttypes.h>
// TODO: scrollingText is a catastrophe! FIX IT! UNREADABLE, TERRIBLE !
static bool isLongerThan(const char* thisChar, size_t thatNumber, size_t n)
{
    return strnlen(thisChar, n) > thatNumber;
}

static void scrollingText(AdDisplayer* adDisplayer, Company* company)
{
    if(isLongerThan(company->company_name, LCD_CHAR_SIZE, COMPANY_STR_NAME_SIZE_MAX) && !adDisplayer->flag2)
    {
        for(uint8_t i = LCD_CHAR_SIZE - 1; i >= 0; i--)
        {
            if(company->company_name[ i ] == ' ')
            {
                uint8_t index = 0;
                for(uint8_t j = i; company->company_name[j] != '\0'; j++)
                {
                    adDisplayer->nameBuffer[index++] = company->company_name[j];
                }
                break;
            }
        }
        adDisplayer->flag2 = true;
    }

    if(adDisplayer->currentTime >= adDisplayer->tempTime)
    {
        printf("Index: %u ,IT PRINTS %s\n", adDisplayer->index, adDisplayer->adBuffer);
        if(adDisplayer->ad[ adDisplayer->index ] == '\0' || adDisplayer->flag == true)
        {
            adDisplayer->adBuffer[ LCD_CHAR_SIZE - 1 ] = ' ';
            if(adDisplayer->flag == false)  { adDisplayer->index = 0; adDisplayer->flag = true; }
            if(adDisplayer->index++ > 15)   { adDisplayer->index = 0; adDisplayer->flag = false; }

        }
        else if( adDisplayer->flag == false )
        {
            adDisplayer->adBuffer[ LCD_CHAR_SIZE - 1 ] = adDisplayer->ad[ adDisplayer->index ];
            lcd_print(&adDisplayer->screen, adDisplayer->adBuffer, 1, 0);
            adDisplayer->index++;
        }
        //printf("temptime: %"PRId64"\ncurrentTime: %"PRId64"\n", adDisplayer->tempTime, adDisplayer->currentTime);
        for(int i = 0; i < LCD_CHAR_SIZE - 1; i++)
        {
            adDisplayer->adBuffer[i] = adDisplayer->adBuffer[i + 1];
        }

        if(!adDisplayer->flag2)
        {
            lcd_print(&adDisplayer->screen, company->company_name, 0, 0);
        }
        else
        {

        }
        adDisplayer->tempTime = adDisplayer->currentTime + 200;
    }
}
static void blinkingText(const char* text)
{

}
static void staticText(const char* text)
{

}

void adDisplayer_init(AdDisplayer* adDisplayer)
{
    lcd_init(&adDisplayer->screen, SDA, SCL);
    adDisplayer->currentTime = 0;
    adDisplayer->startTime = 0;
    adDisplayer->tempTime = 0;
    adDisplayer->index = 0;
    adDisplayer->flag = false;
    adDisplayer->flag2 = false;
    for(int i = 1; i < sizeof(adDisplayer->ad) / sizeof(adDisplayer->ad[0]) - 1; i++)
    {
        adDisplayer->ad[i] = '\0';
    }
    for(int i = 0; i < LCD_CHAR_SIZE; i++)
    {
        adDisplayer->adBuffer[ i ] = ' ';
        adDisplayer->nameBuffer[ i ] = '\0';
    }
    adDisplayer->adBuffer[LCD_CHAR_SIZE] = '\0';
    adDisplayer->nameBuffer[ LCD_CHAR_SIZE ] = '\0';
    
}

void adDisplayer_print(AdDisplayer* adDisplayer, Company* company)
{
    //scrollingText(adDisplayer, "hello");
    DISPLAY_PATTERN pattern = company->display_pattern;
    AD_TYPE adType = company->ad_data[ company->indexOfadToPrint ].type;
    const char* name = company->company_name;
    const char* text = company->ad_data[company->indexOfadToPrint].ad_text;
    switch(adType)
    {
        case SCROLLING:
        {
            if(adDisplayer->currentTime >= adDisplayer->tempTime)
            {
                printf("COMPANY NAME: %s, SCROLLING, AD: %s\n", name, text);
            }
            organizeBuffers(adDisplayer, company);
            scrollingText(adDisplayer, company);
            break;
        }
        case BLINKING:
        {
            if(adDisplayer->currentTime > adDisplayer->tempTime)
            {
                printf("COMPANY NAME: %s, BLINKING, AD: %s\n", name, text);
                adDisplayer->tempTime = adDisplayer->currentTime + 1000;
            }
            break;
        }
        case STATIC:
        {
            if(adDisplayer->currentTime > adDisplayer->tempTime)
            {
                printf("COMPANY NAME: %s, STATIC, AD: %s\n", name, text);
                adDisplayer->tempTime = adDisplayer->currentTime + 1000;
            }
            break;
        }
        case NONE:
        {

            break;
        }

    }
    
}

void adDisplayer_clearBuffer(AdDisplayer* adDisplayer)
{
    memset(adDisplayer->adBuffer, ' ', sizeof(adDisplayer->adBuffer));
    adDisplayer->adBuffer[sizeof(adDisplayer->adBuffer) - 1] = '\0';
}