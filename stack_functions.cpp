#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"

int StackInit(Stack *stk, int capacity)
{
    assert(stk);
    stk ->capacity = capacity;

    stk -> data = (double *)calloc(capacity, sizeof(double));

    return 0;
}

int StackPush(Stack *stk, double value)
{
    assert(stk);
    if( stk->size >= stk->capacity)
    {
        ReallocationStack(stk);
    }
    stk -> data[stk -> size++] = value;
}

double StackPop(Stack *stk)
{
    assert(stk);
    stk -> size--;
    double x = stk -> data[stk -> size]; 
    printf("x = %.4lf \n", x);
    
    return x;
}

double StackDump(Stack *stk)
{
    assert(stk);
    printf("__________STACKDUMP___________\n");
    printf("capacity = %d \n", stk->capacity);
    printf("size = %d\n", stk ->size);

    printf("data = %p\n", stk->data);

    for(int i = 0; i < stk->capacity; i++)
    {
        printf("%d element =  %.4lf \n", i, stk->data[i]);
    }


}


int ReallocationStack(Stack *stk)
{
    assert(stk);
    StackDump(stk);

    double *ptr = (double *)realloc(stk->data, 2 * stk->capacity * sizeof(double));

    if( ptr == NULL)
    {
        StackDtor(stk);
    }
        

    free(stk->data);
    stk->data = ptr; 
    stk->capacity = 2 * stk->capacity;

    for(int i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = {0};
    }

    StackDump(stk);
    return 0;
}

void StackDtor(Stack *stk)
{
    assert(stk);
    free(stk->data);
    
    stk->data = 0;
    stk->capacity = 0;
    stk->size = 0;

    StackDump(stk);
}


StackError StackVerify(Stack *stk)
{
    if (stk == NULL)
    {
        return STACK_IS_NULL;
    }

    if(stk->data == NULL)
    {
        if(stk->size != 0)
        {
            return SIZE_IS_NOT_NULL;
        }
        if(stk->capacity != 0)
        {
            return CAPACITY_IS_NOT_NULL; 
        }
    }

    if(stk->data != NULL)
    {
       if(stk->size == 0)
        {
            return SIZE_IS_NULL;
        }
        if(stk->capacity == 0)
        {
            return CAPACITY_IS_NULL;  
        } 
    }

    if(stk->size > stk->capacity)
    {
        return SIZE_BIGGER_CAPACITY;
    }

    if(stk->capacity < 0)
    {
        return CAPACITY_UNDERFLOW;
    }

    if(stk->size < 0)
    {
        return SIZE_UNDERFLOW;
    }


}