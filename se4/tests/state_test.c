#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "uthread.h"
#include "usynch.h"

void waiter(void * arg) {
    event_t * done = (event_t *)arg;
    event_wait(done);
}

void notifier(void * arg) {
    event_t * done  = (event_t *)arg;
    event_set(done);
}

void func1(void * arg){
    event_t * done = (event_t *)arg;
    uthread_t * thread;
    char * state;

    //Check the state of the currently running thread
    thread = ut_self();
    state = ut_state(thread);
    printf("Current Thread State: %s\n", state);
    assert(strcmp(state, "Running") == 0);

    //Check the state of the first thread in queue
    //This is the notifier thread waiting to run
    thread = ut_first();
    state = ut_state(thread);
    printf("First Thread In Queue State: %s\n", state);
    assert(strcmp(state, "Ready") == 0);

    //Check the state of the thread waiting for the event
    thread = get_wblock_thread(done);
    state = ut_state(thread);
    printf("Block Waiting Thread State: %s\n", state);
    assert(strcmp(state, "Blocked") == 0);

    //Yield so the notifier can run and unblock the thread
    ut_yield();

    //Check the state of the first thread in queue
    //This is the thread that was blocked
    thread = ut_first();
    state = ut_state(thread);
    printf("Unblocked Thread State: %s\n", state);
    assert(strcmp(state, "Ready") == 0);
}

void test1(){
    printf("\n :: Test 1 - BEGIN :: \n\n");

    event_t done;
    event_init(&done);


    ut_create(waiter, &done, 1);
    ut_create(func1, &done, 1);
    ut_create(notifier, &done, 1);
    ut_run();

    printf("\n :: Test 1 - END :: \n\n");
}

int main() {
    ut_init();

    test1();

    ut_end();
    return 0;
}