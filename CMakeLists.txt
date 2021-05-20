cmake_minimum_required(VERSION 3.17)
project(SO C)

set(CMAKE_C_STANDARD 99)
enable_language(ASM)

add_executable(SimpleTest se4/tests/simpletest.c se4/uthread/uthread.c se4/uthread/semaphore.c se4/uthread/event.c se4/uthread/ctxswitch.s)
include_directories(SimpleTest se4/include)
include_directories(SimpleTest se4/uthread)

add_executable(EventTest se4/tests/event_test.c se4/uthread/uthread.c se4/uthread/semaphore.c se4/uthread/event.c se4/uthread/ctxswitch.s)
include_directories(EventTest se4/include)
include_directories(EventTest se4/uthread)

add_executable(StateTest se4/tests/state_test.c se4/uthread/uthread.c se4/uthread/semaphore.c se4/uthread/event.c se4/uthread/ctxswitch.s)
include_directories(EventTest se4/include)
include_directories(EventTest se4/uthread)

add_executable(PriorityTest se4/tests/priority_test.c se4/uthread/uthread.c se4/uthread/semaphore.c se4/uthread/event.c se4/uthread/ctxswitch.s)
include_directories(EventTest se4/include)
include_directories(EventTest se4/uthread)

add_executable(CyclicBarrierTest se4/tests/cyclic_barrier_test.c se4/uthread/uthread.c se4/uthread/cyclic_barrier.c se4/uthread/ctxswitch.s)
include_directories(EventTest se4/include)
include_directories(EventTest se4/uthread)