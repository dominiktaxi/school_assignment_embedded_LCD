#include "ad-displayer.h"
#include <string.h>
#include <inttypes.h>

static void splitArray(char* array, uint8_t size)
{
    for(int i = LCD_CHAR_SIZE - 1; i < size; i += LCD_CHAR_SIZE)
    {
        for(int j = i; j >= 0; j--)
        {
            if(array[j] == ' ') 
            { 
                array[j] = '\0'; 
                i = j;
                break; 
            }
        }
        array[i] = '\0'; 
    }
    array[size] = '\0';
    array[size + 1] = '\0';


   
}

static void printInParts(AdDisplayer* adDisplayer, char* buffer, uint8_t column, uint8_t* splitIndex)
{
    lcd_print(&adDisplayer->screen, "                ", column, 0);
    lcd_print(&adDisplayer->screen, buffer + *splitIndex, column, 0);

    for(int i = *splitIndex; i < AD_STR_SIZE_MAX; i++)
    {
        if( buffer[i] == '\0' )
        {
            if(buffer[i + 1] == '\0')
            {
                *splitIndex = 0;
                break;
            }
            *splitIndex = i + 1;
            break;
        }
    }

}

static void scrollingText(AdDisplayer* adDisplayer, Company* company)
{
    const char* ad = company->ad_data[ company->indexOfadToPrint ].ad_text;
   
    if(*(adDisplayer->currentTime) >= adDisplayer->tempTime)
    {
        
        if(ad[ adDisplayer->index ] == '\0' || adDisplayer->flag == true)
        {
            adDisplayer->adBuffer[ LCD_CHAR_SIZE - 1 ] = ' '; //insert spaces at the end
            if(adDisplayer->flag == false)  { adDisplayer->index = 0; adDisplayer->flag = true; }
            if(adDisplayer->index++ > 15)   { adDisplayer->index = 0; adDisplayer->flag = false; }
        }
        else if( adDisplayer->flag == false )
        {
            adDisplayer->adBuffer[ LCD_CHAR_SIZE - 1 ] = ad[ adDisplayer->index ];
            lcd_print(&adDisplayer->screen, adDisplayer->adBuffer, 1, 0);
            adDisplayer->index++;
        }
        for(int i = 0; i < LCD_CHAR_SIZE - 1; i++)
        {
            adDisplayer->adBuffer[i] = adDisplayer->adBuffer[i + 1];
        }
        adDisplayer->tempTime = *adDisplayer->currentTime + 300;
    }
}
static void blinkingText(AdDisplayer* adDisplayer, Company* company)
{
    

    if(*(adDisplayer->currentTime) >= adDisplayer->tempTime3)
    {
        if(!adDisplayer->on)
        {
            printInParts(adDisplayer, adDisplayer->adBuffer, 1, &company->adSplitIndex);
            adDisplayer->on = true;
        }
        else
        {
            lcd_print(&adDisplayer->screen, "                ", 1, 0);
            adDisplayer->on = false;
        }
        adDisplayer->tempTime3 = *adDisplayer->currentTime + 1000;
    }
}
static void staticText(AdDisplayer* adDisplayer, Company* company)
{
    if(*(adDisplayer->currentTime) >= adDisplayer->tempTime3)
    {
        printInParts(adDisplayer, adDisplayer->adBuffer, 1, &company->adSplitIndex);
        adDisplayer->tempTime3 = *adDisplayer->currentTime + 1000;
    }
}

void adDisplayer_init(AdDisplayer* adDisplayer, int64_t* currentTime)
{
    lcd_init(&adDisplayer->screen, SDA, SCL);
    adDisplayer->currentTime = currentTime;
    adDisplayer->tempTime = 0;
    adDisplayer->tempTime2 = 0;
    adDisplayer->index = 0;
    adDisplayer->splitIndex = 0;
    adDisplayer->flag = false;
    adDisplayer->on = false;
    // for(int i = 1; i < sizeof(adDisplayer->ad) / sizeof(adDisplayer->ad[0]) - 1; i++)
    // {
    //     adDisplayer->ad[i] = '\0';
    // }
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
    AD_TYPE adType = company->ad_data[ company->indexOfadToPrint ].type;

    if(*adDisplayer->currentTime >= adDisplayer->tempTime2)
    {
        printInParts(adDisplayer, adDisplayer->nameBuffer, 0, &company->nameSplitIndex);
        adDisplayer->tempTime2 = *adDisplayer->currentTime + 2000;
    }
    switch(adType)
    {
        case SCROLLING:
        {   
            scrollingText(adDisplayer, company);
            break;
        }
        case BLINKING:
        {
            if(*(adDisplayer->currentTime) > adDisplayer->tempTime)
            {
                blinkingText(adDisplayer, company);
                adDisplayer->tempTime = *adDisplayer->currentTime + 1000;
            }
            break;
        }
        case STATIC:
        {
            if(*(adDisplayer->currentTime) > adDisplayer->tempTime)
            {
                staticText(adDisplayer, company);
                adDisplayer->tempTime = *adDisplayer->currentTime + 1000;
            }
            break;
        }
        case NONE:
        {
            break;
        }
    }
}

void adDisplayer_reset(AdDisplayer* adDisplayer, Company* company)
{
    memset(adDisplayer->adBuffer, ' ', sizeof(adDisplayer->adBuffer));
    adDisplayer->adBuffer[sizeof(adDisplayer->adBuffer) - 1] = '\0';
    adDisplayer->tempTime3 = 0;
    adDisplayer->tempTime2 = 0;
    adDisplayer->tempTime = 0;
    AD_TYPE adType = company->ad_data[company->indexOfadToPrint].type;
    const char* ad = company->ad_data[company->indexOfadToPrint].ad_text;
    const char* company_name = company->company_name;
    switch (adType)
    {
        case SCROLLING: 
        {
             if(strnlen(company_name, COMPANY_STR_NAME_SIZE_MAX) > LCD_CHAR_SIZE)
            {
                strcpy(adDisplayer->nameBuffer, company_name);
                splitArray(adDisplayer->nameBuffer, (uint8_t)strlen(company_name) );
                adDisplayer->adBuffer[LCD_CHAR_SIZE] = '\0';
            }
            break;
        }

        case BLINKING:
        case STATIC:
        
        {
            if(strnlen(company_name, COMPANY_STR_NAME_SIZE_MAX) > LCD_CHAR_SIZE)
            {
                strcpy(adDisplayer->nameBuffer, company_name);
                splitArray(adDisplayer->nameBuffer, (uint8_t)strlen(company_name) );
                adDisplayer->adBuffer[LCD_CHAR_SIZE] = '\0';
            }
            if(strnlen(ad, AD_STR_SIZE_MAX) > LCD_CHAR_SIZE)
            {
                strcpy(adDisplayer->adBuffer, ad);
                splitArray(adDisplayer->adBuffer, (uint8_t)strlen(ad));
                adDisplayer->adBuffer[strlen(ad)] = '\0';
            }
            break;
        }
        case NONE: { break; }
    }
    lcd_clear(&adDisplayer->screen);
}