#include <stdint.h>

#include "uthread.h"
#include "usynch.h"
#include "waitblock.h"
//#include "list.h"

//static inline list_entry_t * find_priority_entry(int32_t priority, list_entry_t * waiters) {
//    list_entry_t * curr;
//    curr = get_list_first(waiters);
//    if(is_list_empty(waiters))
//        return curr;
//
//    int32_t curr_priority = container_of(curr, waitblock_t, entry)->priority;
//    if(curr_priority < priority)
//        return curr->prev;
//
//    while (curr_priority >= priority && curr != waiters) {
//        curr = curr->next;
//        curr_priority = container_of(curr, waitblock_t, entry)->priority;
//    }
//    return curr->prev;
//}

void cb_init(cyclic_barrier_t * barrier, uint32_t parties) {
	barrier->parties = parties;
	init_list_head(&barrier->waiters);
}

uint32_t cb_await(cyclic_barrier_t * barrier) {
	uint32_t length = list_length(&barrier->waiters);

    if(length < barrier->parties - 1){
        waitblock_t wblock;
        init_waitblock(&wblock);
        insert_list_last(&barrier->waiters, &wblock.entry);
//        list_entry_t * entry = find_priority_entry(wblock.priority, &barrier->waiters);
//        insert_list_after(entry, &wblock.entry);
        ut_deactivate();
        return length;
    }

    while (!is_list_empty(&(barrier->waiters))) {
        list_entry_t *curr = remove_list_first(&(barrier->waiters));
        waitblock_t *pwblock = container_of(curr, waitblock_t, entry);
        ut_activate(pwblock->thread);
    }
    ut_yield();
    return length;
}
