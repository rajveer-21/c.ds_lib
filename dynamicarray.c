#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define GROW_ARRAY_CAPACITY(capacity)((capacity < 8)? 8 : capacity * 2)
#define GROW_ARRAY_ELEMENTS(type, array, old_size, new_size)(reallocate(array, old_size * sizeof(type), new_size * sizeof(type)))
#define FREE_ARRAY_ELEMENTS(type, array, old_size)(reallocate(array, old_size * sizeof(type), 0))
typedef struct
{
    int occupied;
    int capacity;
    char** stuff;
}ARRAY;
void* reallocate(void* array, size_t old_size, size_t new_size);
void initializeDynamicArray(ARRAY* array);
void writeToDynamicArray(ARRAY* array, char* instruction);
void freeUpDynamicArray(ARRAY* array);

void* reallocate(void* array, size_t old_size, size_t new_size)
{
    if(new_size == 0)
    {
        free(array);
        return NULL;
    }
    void* new_array = realloc(array, new_size);
    if(new_array == NULL)
    exit(1);
    return new_array;
}

void initializeDynamicArray(ARRAY* array)
{
    array->occupied = 0;
    array->capacity = 0;
    array->stuff = NULL;
}

void writeToDynamicArray(ARRAY* array, char* instruction)
{
    if(array->occupied + 1 > array->capacity)
    {
        int oldCapacity = array->capacity;
        array->capacity = GROW_ARRAY_CAPACITY(oldCapacity);
        array->stuff = GROW_ARRAY_ELEMENTS(char*, array->stuff, oldCapacity, array->capacity);
    }
    array->stuff[array->occupied] = instruction;
    array->occupied = array->occupied + 1;
}

void freeUpDynamicArray(ARRAY* array)
{
    FREE_ARRAY_ELEMENTS(char*, array->stuff, array->occupied);
    initializeDynamicArray(array);
    return;
}

int main()
{
    ARRAY array;
    initializeDynamicArray(&array);
    writeToDynamicArray(&array, "OPCODE_1");
    writeToDynamicArray(&array, "OPCODE_2");
    writeToDynamicArray(&array, "OPCODE_3");
    for(int i = 0; i < array.occupied; i++)
    {
        printf("%s\n", array.stuff[i]);
    }
    freeUpDynamicArray(&array);
}
