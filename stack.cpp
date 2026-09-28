#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct Stack{
    double *data;
    int size;
    int capacity;
}Stack;

int StackInit(Stack *stk, int capacity);
int StackPush(Stack *stk, double value);
int ReallocationStack(Stack *stk);
double StackPop(Stack *stk);
double StackDump(Stack *stk);
void StackDtor(Stack *stk);

int main()
{
    Stack my_stack = {0};
    StackInit(&my_stack, 5);
    StackPush(&my_stack, 20);
    StackPush(&my_stack, 30);
    StackPush(&my_stack, 20);
    StackPush(&my_stack, 30);
    StackPush(&my_stack, 20);
    StackPush(&my_stack, 30);

    for(int i = 0; i < my_stack.capacity; i ++)
    {
        printf("%.4lf \n", my_stack.data[i]);
    }

    double x = StackPop(&my_stack);

    printf("x = %.4lf \n", x);

    for(int j = 0; j < my_stack.capacity; j ++)
    {
        printf("%.4lf \n", my_stack.data[j]);
    }

    StackDump(&my_stack);
    StackDtor(&my_stack);
    
    return 0;
}

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