#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"


int StackInit(Stack *stk, int capacity, FILE *file)
{
    assert(stk);
    stk->capacity = capacity;
    stk->size = 0;
    stk->file = file;
    stk->data = (double *)calloc(capacity, sizeof(double));
    
    StackVerify(stk);
    for(int i = 0; i < stk->capacity; i++)
    {
        stk->data[i] = STACK_POIZON;
    }
    STACK_DUMP;
    return 0;
}

int StackPush(Stack *stk, double value)
{
    assert(stk);
    if(value == STACK_POIZON)
    {
        fprintf(stk->file, "this value is pozoined, use another one\n");
        return 1;
    }
    if(stk->size >= stk->capacity)
    {
        ReallocationStack(stk);
    }
    stk -> data[stk -> size++] = value;
    StackVerify(stk);
    
    STACK_DUMP;

    return 0;
}

double StackPop(Stack *stk)
{
    assert(stk);
    if (stk->size == 0)
    {
        printf("can't pop from empty stack\n");
        return 0;
    }
    stk -> size--;
    double x = stk -> data[stk -> size]; 
    printf("x = %.4lf \n", x);

    stk->data[stk->size] = STACK_POIZON;


    StackVerify(stk);
    STACK_DUMP;

    return x;
}

void StackDump(Stack *stk, const char *function, int line)
{
    assert(stk);
    FILE *file = stk->file;
   


    fprintf(file, "__________STACKDUMP___________\n");
    fprintf(file, "result of %s on line %d\n", function, line);
    fprintf(file, "capacity = %d \n", stk->capacity);
    fprintf(file, "size = %d\n", stk ->size);
    fprintf(file, "data = %p\n", stk->data);

    for(int i = 0; i < stk->capacity; i++)
    {
        if(stk->data[i] == STACK_POIZON)
        {
            fprintf(file, "POIZON\n");
        }
        else
        {
            fprintf(file, "%d element =  %.4lf \n", i, stk->data[i]);
        }
        
    }

}


int ReallocationStack(Stack *stk)
{
    assert(stk);
   

    double *new_capacity = (double *)realloc(stk->data, 2 * stk->capacity * sizeof(double));

    if( new_capacity == NULL)
    {
        StackDtor(stk);
    }
        
    stk->data = new_capacity; 
    stk->capacity = 2 * stk->capacity;

    for(int i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = STACK_POIZON;
    }

    StackVerify(stk);

    return 0;
}

void StackDtor(Stack *stk)
{
    assert(stk);
    free(stk->data);
    
    stk->data = 0;
    stk->capacity = 0;
    stk->size = 0;

   STACK_DUMP;

}


int StackVerify(Stack *stk) //cpp с тестами
{
    if (stk == NULL)
    {
        printf("stack is null\n");
        return 1;
    }

    if(stk->data == NULL && (stk->size != 0 || stk->capacity != 0)) 
    {
        printf("stack is null, but cap or size in not\n");
        return 1; 
    }

    if(stk->data != NULL && stk->capacity == 0)
    {
        printf("stack is not null, but cap or size is\n");
        return 1;  
    }

    if(stk->size > stk->capacity)
    {
        printf("size is bigger than cap\n");
        return 1;
    }

    if(stk->capacity < 0)
    {
        printf("cap smaller than 0\n");
        return 1;
    }

    if(stk->size < 0)
    {
        printf("size smaller than 0\n");
        return 1;
    }


    return 0;
}