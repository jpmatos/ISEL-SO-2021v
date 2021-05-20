#include <stdio.h>
#include <stdint.h>

#include "uthread.h"
#include "usynch.h"

void func(void * arg){
    cyclic_barrier_t  * barrier = (cyclic_barrier_t *)arg;

    printf("Blocked With Priority %u\n", ut_priority(ut_self()));
    uint32_t res = cb_await(barrier);
    printf("Unblocked With Priority %u With Value %u\n", ut_priority(ut_self()), res);
}

void test1(){
    cyclic_barrier_t barrier;
    cb_init(&barrier, 5);

    ut_create(func, &barrier, 1);   //0
    ut_create(func, &barrier, 1);   //1
    ut_create(func, &barrier, 3);   //2
    ut_create(func, &barrier, 1);   //3
    ut_create(func, &barrier, 2);   //4
    ut_run();
}

int main() {
    ut_init();

    test1();

    ut_end();
    return 0;
}