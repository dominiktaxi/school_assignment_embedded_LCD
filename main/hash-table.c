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

STATUS_T hashTable_init(HashTable* table)
{
    if(table == NULL) { return POINTER_IS_NULL; }
    for(int i = 0; i < 100; i++)
    {
        table->buckets[i].empty = true;
    }
    return NONE;
}

STATUS_T hashTable_insert(HashTable* table, Company company)
{
    bool success = false;
    uint16_t key = str_to_number(company.company_name);
    int index = key % 100;
    int counter = 0;
    while(counter < 100)
    {
        if(table->buckets[index].key == key && !( table->buckets[index].empty ) )
        {
            return DUPLICATE;
        }
        if(table->buckets[ index ].empty)
        {
            table->buckets[ index ].company = company;
            table->buckets[ index ].key = key;
            table->buckets[ index ].empty = false;
            return SUCCESS;
        }
        else
        {
            index++;
            index %= 100;
        }
        counter++;
    }
    return OUT_OF_SPACE;
}

bool hashTable_delete(HashTable* table, const char* name)
{
    bool success = false;
    uint32_t key = str_to_number(name);
    int index = key % 100;
    int counter = 0;
    while(counter < 100)
    {
        if(table->buckets[index].key == key)
        {
            table->buckets[index].empty = true;
            success = true;
            counter = 0;
        }
        else if(!success)
        {
            index++;
            index %= 100;
            counter++;
            continue;
        }
        index++;
        index %= 100;
        counter++;
        if( !table->buckets[ index ].empty )
        {
            hashTable_insert( table, table->buckets[ index ].company );
            table->buckets[ index ].empty = true;
        }
        else
        {
            break;
        }
    }
    return success;
}

void hashTable_findAndPrint( HashTable* table, const char* name )
{
    printf("find and print:\n");
    int index = str_to_number(name) % 100;
    int counter = 0;
    while(counter < 100)
    {
        index %= 100;
        char name2[20] = {0};
        strcpy(name2, table->buckets[index].company.company_name);
        if(table->buckets[index].company.company_name == name && !(table->buckets[index].empty) )
        {
            uint32_t key = str_to_number(table->buckets[index].company.company_name);
            printf("Index: %d, Key: %lu, Name: %s\n", index, key, name );
            return;
        }
        index++;
        counter++;
    }
}

void hashTable_printAll(HashTable* table)
{
    printf("print all:\n");
    for(int i = 0; i < 100; i++)
    {
        uint16_t key = str_to_number(table->buckets[i].company.company_name);
        if( !(table->buckets[i].empty) )
        {
            printf("Index: %d, Key: %d, Name: %s\n", i, key, table->buckets[i].company.company_name);
        }
    }
}
