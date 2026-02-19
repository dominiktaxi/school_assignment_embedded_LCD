#ifndef HASH_TABLE_H

#define HASH_TABLE_H
#include <stdbool.h>
#include <companies.h>
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

hash_table_init(HashTable*);
bool insert(HashTable*, const char*, Company);


#endif