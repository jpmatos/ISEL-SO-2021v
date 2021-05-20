#include <stdio.h>
#include <stdint.h>

#include "uthread.h"

void func(void * arg){
    int32_t priority = *(int32_t *)arg;

    printf("Running thread with priority: %i\n", priority);
}

void test1(){
    printf("\n :: Test 1 - BEGIN :: \n\n");

    int32_t p1 = 1;
    int32_t p2 = 2;
    int32_t p3 = 3;

    ut_create(func, &p2, 2);
    ut_create(func, &p3, 3);
    ut_create(func, &p1, 1);
    ut_create(func, &p1, 1);
    ut_create(func, &p3, 3);
    ut_create(func, &p2, 2);
    ut_create(func, &p1, 1);
    ut_create(func, &p2, 2);
    ut_run();

    printf("\n :: Test 1 - END :: \n\n");
}

int main() {
    ut_init();

    test1();

    ut_end();
    return 0;
}