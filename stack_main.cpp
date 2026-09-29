#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"

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

