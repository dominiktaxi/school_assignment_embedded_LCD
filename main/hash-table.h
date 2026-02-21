#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include "companies.h"
#include "status.h"
#include "macros.h"
typedef struct Bucket
{
    Company company;
    uint16_t key;
    bool empty;
}Bucket;


typedef struct HashTable
{
    Bucket buckets[COMPANIES_MAX];
}HashTable;

STATUS_T hashTable_init(HashTable*);
STATUS_T hashTable_insert(HashTable*, Company);
STATUS_T hashTable_addAd(HashTable*, const char*, const char*, AD_TYPE);
bool hashTable_delete(HashTable*, const char*);
void hashTable_findAndPrint(HashTable*, const char*);
void hashTable_printAll(HashTable*);

#endif