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

STATUS_T hashTable_init(HashTable*);
STATUS_T hashTable_insert(HashTable*, Company);
bool hashTable_delete(HashTable*, const char*);
void hashTable_findAndPrint(HashTable*, const char*);
void hashTable_printAll(HashTable*);

#endif