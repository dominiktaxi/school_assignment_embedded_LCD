#ifndef HASH_TABLE_H

#define HASH_TABLE_H
#include <stdbool.h>
#include "companies.h"
#include "status.h"
typedef struct Bucket
{
    Company company;
    uint16_t key;
    bool empty;
}Bucket;


typedef struct HashTable
{
    Bucket buckets[100];
}HashTable;

STATUS_T hash_table_init(HashTable*);
STATUS_T insert(HashTable*, Company);
void find_and_print(HashTable*, const char*);
void print_all(HashTable*);

#endif