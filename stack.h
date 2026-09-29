#ifndef stack_h
#define stack_h

typedef struct Stack{
    double *data;
    int size;
    int capacity;
}Stack;

typedef enum {
    STACK_IS_OK = 0,
    STACK_IS_NULL,
    SIZE_IS_NOT_NULL,
    CAPACITY_IS_NOT_NULL,
    SIZE_IS_NULL,
    CAPACITY_IS_NULL,
    SIZE_BIGGER_CAPACITY,
    SIZE_UNDERFLOW,
    CAPACITY_UNDERFLOW
} StackError;

int StackInit(Stack *stk, int capacity);
int StackPush(Stack *stk, double value);
int ReallocationStack(Stack *stk);
double StackPop(Stack *stk);
double StackDump(Stack *stk);
void StackDtor(Stack *stk);

#endif