#ifndef stack_h
#define stack_h

enum StkError
{
    STK_OK,
    STK_CAPACITY_NULL,
    STK_SIZE_BIGGER_CAP,
    STK_CAP_UNDER_ZERO,
    STK_SIZE_UNDER_ZERO,
    STK_CAP_SIZE_NOT_NULL,
    STK_IS_NULL
};

typedef double stack_elem;
typedef struct Stack{
    stack_elem *data;
    int size;
    int capacity;
    int error;

    FILE *file;
}Stack;

#define epsilon 1e-9
static const stack_elem STACK_POIZON = 6666;
const double CANARY = 0xB0B;

int StackInit(Stack *stk, int capacity, FILE *file);
int StackPush(Stack *stk, double value);
int ReallocationStack(Stack *stk);
double StackPop(Stack *stk);
void StackDump(Stack *stk, const char *function, int line, const char *commentariy);
void StackDtor(Stack *stk);
int StackVerify(Stack *stk);
int CheckPush(Stack *stk);


#ifdef StkDEBUG

#define STACK_DUMP(stk, commentariy) \
    StackDump(stk,  __FUNCTION__, __LINE__, commentariy)

#else

#define STACK_DUMP ((void)0)

#endif


#endif