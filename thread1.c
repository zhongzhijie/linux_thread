
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *thread_function(void *arg);

char message[] = "hello world!";

int main(void)
{
    int res;
    pthread_t a_thread;
    void *thread_result;

    /* 创建线程 */
    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (0 != res)
    {
        perror("Thread create failed!");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for thread to finish...\r\n");

    /* 线程同步，当前线程等待a_thread结束 */
    res = pthread_join(a_thread, &thread_result);

    printf("Thread joined, it returned %s\r\n", (char *)thread_result);
    printf("Message is now %s\r\n", message);

    exit(EXIT_FAILURE); 
}

/* 新线程的回调函数 */
void *thread_function(void *arg)  
{  
    printf("thread_function is running. Argument is %s\r\n", (char *)arg);  
    sleep(3);

    /* 修改全局变量，这里也可以看出线程之间共享全局变量 */
    strcpy(message, "Bye!");

    /* 线程终止，返回某个对象的指针，不能是局部变量 */
    pthread_exit("Thank you for your CPU time!");  
} 

