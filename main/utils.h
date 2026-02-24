#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>

void utils_toLower(const char**);
void swap(uint8_t*, uint8_t*);
uint32_t espRandom(void* data);
#endif