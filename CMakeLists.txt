cmake_minimum_required(VERSION 3.17)
project(SO C)

set(CMAKE_C_STANDARD 99)
enable_language(ASM)

add_executable(SO se4/tests/simpletest.c se4/uthread/uthread.c se4/uthread/semaphore.c se4/uthread/event.c se4/uthread/ctxswitch.s)
include_directories(SO se4/include)
include_directories(SO se4/uthread)