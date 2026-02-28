#include "utils.h"
#include "esp_random.h"
#include "esp_timer.h"
#include "company-manager.h"

void utils_toLower(const char** text)
{
    char a = 0;

    for(int i = 0; *text[i] != '\0'; i++)
    {
        a = *text[i];
    }
}

void swap(uint8_t* a, uint8_t* b)
{
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}


uint32_t espRandom(void)
{
    return esp_random();
}

int64_t getEspTimeUs(void)
{
    return esp_timer_get_time();
}

int64_t getEspTimeSec(void)
{
    return (esp_timer_get_time() / 1000000);
}

int64_t getEspTimeMs(void)
{
    return (esp_timer_get_time() / 1000);
}