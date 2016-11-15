all:thread1 thread2 thread3 thread4 thread5 thread6 thread7 thread8

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

thread6: thread6.c
	gcc -D_REENTRANT thread6.c -o thread6 -lpthread

thread7: thread7.c
	gcc -D_REENTRANT thread7.c -o thread7 -lpthread

thread8: thread8.c
	gcc -D_REENTRANT thread8.c -o thread8 -lpthread
clean: 
	rm -f thread1 *.o thread2 thread3 thread4 thread5 thread6 thread7 thread8