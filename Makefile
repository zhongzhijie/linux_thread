all:thread1 thread2 thread3 thread4 thread5

thread1: thread1.c
	gcc -D_REENTRANT thread1.c -o thread1 -lpthread

thread2: thread2.c
	gcc -D_REENTRANT thread2.c -o thread2 -lpthread

thread3: thread3.c
	gcc -D_REENTRANT thread3.c -o thread3 -lpthread

thread4: thread4.c
	gcc -D_REENTRANT thread4.c -o thread4 -lpthread

thread5: thread5.c
	gcc -D_REENTRANT thread5.c -o thread5 -lpthread

clean: 
	rm -f thread1 *.o thread2 thread3 thread4 thread5