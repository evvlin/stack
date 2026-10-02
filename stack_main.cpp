#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char *argv[]) 
{
    if (argc != 2)
    {
        printf( "ups ty eblan\n", argv[0]);
        return 1;
    } 

    FILE *file = fopen(argv[1], "w");
    
    if (file == NULL)
    {
        printf("poshel nahui");
        return 1;
    }
    fprintf(file, "eto dermo rabotaet naher!\n");

    Stack my_stack = {0};

    StackInit(&my_stack, 5, file);
    if (StackInit(&my_stack, 5, file) != 0)
    {
        fclose(file);
        return 1;
    }

    StackPush(&my_stack, 1);
    StackPush(&my_stack, 2);
    StackPush(&my_stack, 3);
    StackPush(&my_stack, 4);
    StackPush(&my_stack, 6666);
    StackPush(&my_stack, 5);

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

    StackDump(&my_stack, __FILE__, __LINE__);
    StackDtor(&my_stack);

    fclose(file);
    return 0;
}

