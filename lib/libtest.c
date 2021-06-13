#include <stdio.h>
#include "libtest.h"

int so_func_sum(int x, int y){
    int sum = x + y;
    printf("so_func_sum=%d",sum);

    return sum;
}