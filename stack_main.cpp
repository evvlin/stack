#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char *argv[]) 
{
    if (argc != 2)
    {
        printf( "ups ty eblan\n");
        return 1;
    } 

    printf("1");
    FILE *file = fopen(argv[1], "w");
    
    if (file == NULL)
    {
        printf("poshel nahui");
        return 1;
    }

    fprintf(file, "eto dermo rabotaet naher!\n");

    Stack my_stack;

    if (StackInit(&my_stack, 5, file) != 0)
    {
        fclose(file);
        return 1;
    }
    printf("2");
    CheckPush(&my_stack);
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
    printf("7");

    StackDump(&my_stack, __FUNCTION__, __LINE__, "main");
    StackDtor(&my_stack);
    printf("8");
    fclose(file);
    return 0;
}

