#include <stdio.h>
#include <stdlib.h>

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

void hash_table_init(HashTable* table)
{
    for(int i = 0; i < 100; i++)
    {
        table->buckets[i].empty = true;
    }
}

bool insert(HashTable* table, Company company)
{
    bool success = false;
    uint16_t key = str_to_number(company.company_name);
    int index = key % 100;
    int counter = 0;
    while(counter < 100)
    {
        if(table->buckets[index].key == key && !( table->buckets[index].empty ) )
        {
            return false;
        }
        if(table->buckets[ index ].empty)
        {
            table->buckets[ index ].company = company;
            table->buckets[ index ].key = key;
            table->buckets[ index ].empty = false;
            return true;
        }
        else
        {
            index++;
            index %= 100;
        }
        counter++;
    }
    return false;
}

bool delete(HashTable* table, const char* name)
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
        if(!table->buckets[index].empty)
        {
            insert(table, table->buckets[index].key, table->buckets[index].company);
            table->buckets[index].empty = true;
        }
        else
        {
            break;
        }
    }
    return success;
}

void find_and_print(HashTable* table, int key)
{
    printf("find and print:\n");
    int index = key % 100;
    int counter = 0;
    while(counter < 100)
    {
        index %= 100;
        int data = table->buckets[index].data;
        if(table->buckets[index].key == key && !(table->buckets[index].empty) )
        {
            key = table->buckets[index].key;
            printf("Index: %d, Key: %d, Data: %d\n", index, key, data );
            return;
        }
        index++;
        counter++;
    }
}

void print_all(HashTable* table)
{
    printf("print all:\n");
    for(int i = 0; i < 100; i++)
    {
        int key = table->buckets[i].key;
        int data = table->buckets[i].data;
        if( !(table->buckets[i].empty) )
        {
            printf("Index: %d, Key: %d, Data: %d\n", i, key, data);
        }
    }
}
