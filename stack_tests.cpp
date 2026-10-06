#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"

int CheckPush(Stack *stk)
{
    StackPush(stk, 1);
    StackPush(stk, 2);
    StackPush(stk, 3);
    StackPush(stk, 4);
    StackPush(stk, 6666.6767);
    StackPush(stk, 6666);

    return 0;
}