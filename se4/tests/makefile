
dynamic: simpletest.c event_test.c state_test.c priority_test.c cyclic_barrier_test.c
	gcc -o simpletest -Wall -g -I ../include simpletest.c ../uthread/libuthread.so
	gcc -o event_test -Wall -g -I ../include event_test.c ../uthread/libuthread.so
	gcc -o state_test -Wall -g -I ../include state_test.c ../uthread/libuthread.so
	gcc -o priority_test -Wall -g -I ../include priority_test.c ../uthread/libuthread.so
	gcc -o cyclic_barrier_test -Wall -g -I ../include cyclic_barrier_test.c ../uthread/libuthread.so
	
	
static : simpletest.c event_test.c
	gcc -o simpletest -Wall -g -I ../include simpletest.c ../uthread/libuthread.a
	gcc -o event_test -Wall -g -I ../include event_test.c ../uthread/libuthread.a
	
clean:
	rm -rf simpletest event_test state_test priority_test cyclic_barrier_test
