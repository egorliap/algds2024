#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
int test__min_time(int** table,int n,int m, int ans) {
    if(ans == min_time(table,n,m)){
        
        return 0;
    }else{
        printf("\n\n%d\n\n",min_time(table,n,m));
        return 1;
    }
}