#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "status.h"
#include "hash-table.h"

static int str_to_number(const char* str)
{
    int ret = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        ret += str[i];
    }
    return ret;
}

STATUS_T hashTable_init(Companies* hashTable)
{
    if(hashTable == NULL) { return POINTER_IS_NULL; }
    for(int i = 0; i < COMPANIES_MAX; i++)
    {
        hashTable->buckets[i].empty = true;
    }
    return NONE;
}

STATUS_T hashTable_insert(Companies* hashTable, Company company)
{
    bool success = false;
    uint16_t key = str_to_number(company.company_name);
    int index = key % COMPANIES_MAX;
    int counter = 0;
    while(counter < COMPANIES_MAX)
    {
        if(hashTable->buckets[index].key == key && !( hashTable->buckets[index].empty ) )
        {
            return DUPLICATE;
        }
        if(hashTable->buckets[ index ].empty)
        {
            hashTable->buckets[ index ].company = company;
            hashTable->buckets[ index ].key = key;
            hashTable->buckets[ index ].empty = false;
            return SUCCESS;
        }
        else
        {
            index++;
            index %= COMPANIES_MAX;
        }
        counter++;
    }
    return OUT_OF_SPACE;
}

void hashTable_findAndPrint( Companies* hashTable, const char* name )
{
    printf("find and print:\n");
    int index = str_to_number(name) % COMPANIES_MAX;
    int counter = 0;
    while(counter < 100)
    {
        index %= 100;
        char name2[20] = {0};
        strcpy(name2, hashTable->buckets[index].company.company_name);
        if(hashTable->buckets[index].company.company_name == name && !(hashTable->buckets[index].empty) )
        {
            uint32_t key = str_to_number(hashTable->buckets[index].company.company_name);
            printf("Index: %d, Key: %lu, Name: %s\n", index, key, name );
            return;
        }
        index++;
        counter++;
    }
}

void hashTable_printAll(Companies* hashTable)
{
    printf("print all:\n");
    for(int i = 0; i < COMPANIES_MAX; i++)
    {
        uint16_t key = str_to_number(hashTable->buckets[i].company.company_name);
        if( !(hashTable->buckets[i].empty) )
        {
            printf("Index: %d, Key: %d, Name: %s\nAD1: %s\nAD2: %s\n\n", i, key, hashTable->buckets[i].company.company_name, 
                hashTable->buckets[i].company.ad_data[0].ad_text, hashTable->buckets[i].company.ad_data[1].ad_text);
        }
    }
}
