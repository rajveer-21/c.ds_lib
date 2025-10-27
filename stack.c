#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GROW_STACK_CAPACITY(capacity)(capacity < 8 ? 8 : capacity * 2)
#define GROW_STACK_ELEMENTS(type, stack, old_size, new_size) (reallocate(stack, old_size * sizeof(type), new_size * sizeof(type)))
#define FREE_STACK_ELEMENTS(type, stack, old_size) (reallocate(stack, old_size * sizeof(type), 0))
typedef struct
{
    int capacity;
    int occupied;
    char** stuff;
}STACK;
void* reallocate(void* stack, size_t old_size, size_t new_size)
{
    if(new_size == 0)
    {
        free(stack);
        return NULL;
    }
    void* new_stack = realloc(stack, new_size);
    if(new_stack == NULL)
    exit(1);
    return new_stack;
}
void initializeSTACK(STACK* stack)
{
    stack->occupied = 0;
    stack->capacity = 0;
    stack->stuff = NULL;
}
void destroySTACK(STACK* stack)
{
    for (int i = 0; i < stack->occupied; i++)
    free(stack->stuff[i]);
    FREE_STACK_ELEMENTS(char*, stack->stuff, stack->capacity);
    initializeSTACK(stack);
}
void stackOp1(STACK* stack, char* data)
{
    if(stack->occupied + 1 > stack->capacity)
    {
        int oldCapacity = stack->capacity;
        stack->capacity = GROW_STACK_CAPACITY(oldCapacity);
        stack->stuff = GROW_STACK_ELEMENTS(char*, stack->stuff, oldCapacity, stack->capacity);
    }
    stack->stuff[stack->occupied] = data;
    stack->occupied = stack->occupied + 1;
}
void stackOp2(STACK* stack)
{
    if(stack->occupied == 0)
    {
        printf("Invalid Pop Operation, stack is empty.\n");
        return;
    }
    stack->occupied = stack->occupied - 1;
    char* top_element = stack->stuff[stack->occupied];
    printf("Removed element : %s\n", stack->stuff[stack->occupied]);
    free(top_element);
}
void stackOp3(STACK* stack)
{
    if(stack->occupied == 0)
    {
        printf("Invalid Peek Operation, stack is empty\n.");
        return;
    }
    printf("Topmost element : %s\n", stack->stuff[stack->occupied - 1]);
    return;
}
int main()
{
    STACK stack;
    initializeSTACK(&stack);
    stackOp2(&stack);
    stackOp1(&stack, strdup("NIGGA"));
    stackOp1(&stack, strdup("NIGLET"));
    stackOp1(&stack, strdup("NIGGER"));
    stackOp3(&stack);
    stackOp2(&stack);
    stackOp3(&stack);
    stackOp2(&stack);
    stackOp3(&stack);
    stackOp2(&stack);
    destroySTACK(&stack);
    return 0;
}
