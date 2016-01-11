all: test_wait_queue.o wake_up_process.o
	cc -o test_wait_queue test_wait_queue.o
	cc -o wake_up_process wake_up_process.o

clean:
	rm *.o

test_wait_queue.o: test_wait_queue.c
	cc -c test_wait_queue.c

wake_up_process.o: wake_up_process.c
	cc -c wake_up_process.c
