#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"


int StackInit(Stack *stk, int capacity, FILE *file)
{
    stk->capacity = capacity;
    stk->size = 1;
    stk->file = file;
    stk->data = (double *)calloc(capacity + 2, sizeof(double));
    
    StackVerify(stk);
    stk->data[0] = CANARY;
    for(int i = 1; i <= (stk->capacity + 1); i++)
    {
        stk->data[i] = STACK_POIZON;
    }
    stk->data[stk->capacity + 1] = CANARY;
    STACK_DUMP(stk, "idi hahui");
    return 0;
}

int DoubleCompare(double a, double b)
{
    return (fabs(a - b) < epsilon);   
  
}
int StackPush(Stack *stk, double value)
{
    StackVerify(stk); 
    if(DoubleCompare(value, STACK_POIZON))
    {
        fprintf(stk->file, "this value is pozoined, use another one\n");
        return 1;
    }
    if(stk->size >= stk->capacity + 1)
    {
        ReallocationStack(stk);
    }

    stk -> data[stk -> size++] = value;
    
    STACK_DUMP(stk, "sosite");

    return 0;
}

double StackPop(Stack *stk)
{
    StackVerify(stk);
    if (stk->size == 1)
    {
        printf("can't pop from empty stack\n");
        return 0;
    }
    stk -> size--;
    double x = stk -> data[stk -> size]; 
    printf("x = %.4lf \n", x);

    stk->data[stk->size] = STACK_POIZON;

    STACK_DUMP(stk, "ebanoe sostoianie of ebanogo steka vova eblan poprosil nahuiato napisat 67");

    return x;
}

void StackDump(Stack *stk, const char *function, int line, const char *commentariy)
{
   
    FILE *file = stk->file;
   
    fprintf(file, "__________STACKDUMP___________\n");
    if(stk->error == 0)
    {
        fprintf(file, "NO ERROR\n");
    }
    else
    {
        switch(stk->error){
            case STK_CAPACITY_NULL: fprintf(file, "STK_CAPACITY_NULL\n"); break;
            case  STK_SIZE_BIGGER_CAP: fprintf(file, "STK_SIZE_BIGGER_CAP\n"); break;
            case  STK_CAP_UNDER_ZERO: fprintf(file, "STK_CAP_UNDER_ZERO\n"); break;
            case  STK_SIZE_UNDER_ZERO: fprintf(file, "STK_SIZE_UNDER_ZERO\n"); break;
            case  STK_CAP_SIZE_NOT_NULL: fprintf(file, "STK_CAP_SIZE_NOT_NULL\n"); break;
            case  STK_IS_NULL: fprintf(file, "STK_IS_NULL\n"); break;
            default: fprintf(file, "undefined\n"); break;

        }
        fprintf(file, "%d\n", stk->error);
    }
    
    fprintf(file, "result of %s on line %d\n", function, line);
    fprintf(file, "capacity = %d \n", stk->capacity);
    fprintf(file, "size = %d\n", stk ->size);
    fprintf(file, "data = %p\n", stk->data);
    fprintf(file, "%s\n", commentariy);
    

    for(int i = 1; i < stk->capacity + 1; i++)
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
    StackVerify(stk);
   
    double *new_capacity = (double *)realloc(stk->data, (2 * stk->capacity + 2) * sizeof(double));

    if(new_capacity == NULL)
    {
        StackDtor(stk);
    }
    
    stk->data = new_capacity; 
    stk->data[stk->capacity + 1] = STACK_POIZON;
    stk->capacity = 2 * stk->capacity;
    stk->data[stk->capacity + 1] = CANARY;

    for(int i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = STACK_POIZON;
    }
    return 0;
}

void StackDtor(Stack *stk)
{
    STACK_DUMP(stk,"");
    StackVerify(stk);
    free(stk->data);
    
    stk->data = 0;
    stk->capacity = 0;
    stk->size = 0;
}

int StackVerify(Stack *stk) 
{
    if (stk == NULL)
    {
        stk->error = STK_IS_NULL;
        return 1;
    }

    if(stk->data == NULL && (stk->size != 1 || stk->capacity != 0)) 
    {
        stk->error = STK_CAP_SIZE_NOT_NULL;
        return 1; 
    }

    if(stk->data != NULL && stk->capacity == 0)
    {
        stk->error = STK_CAPACITY_NULL;
        return 1;  
    }

    if(stk->size > stk->capacity + 1)
    {
        stk->error = STK_SIZE_BIGGER_CAP;
        return 1;
    }

    if(stk->capacity < 0)
    {
        stk->error = STK_CAP_UNDER_ZERO;
        return 1;
    }

    if(stk->size < 1)
    {
        stk->error = STK_SIZE_UNDER_ZERO;
        return 1;
    }

    stk->error = STK_OK;
    return 0;
}