#ifndef stack_h
#define stack_h

typedef struct Stack{
    double *data;
    int size;
    int capacity;

    FILE *file;
}Stack;

static const int STACK_POIZON = 6666;

int StackInit(Stack *stk, int capacity, FILE *file);
int StackPush(Stack *stk, double value);
int ReallocationStack(Stack *stk);
double StackPop(Stack *stk);
void StackDump(Stack *stk, const char *function, int line);
#ifdef StkDEBUG

#define STACK_DUMP \
    StackDump((stk),  __FILE__, __LINE__)

#else

#define STACK_DUMP ((void)0)

#endif
void StackDtor(Stack *stk);
int StackVerify(Stack *stk);

#endif