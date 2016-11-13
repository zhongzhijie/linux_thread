
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

    /* �����߳� */
    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    if (0 != res)
    {
        perror("Thread create failed!");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for thread to finish...\r\n");

    /* �߳�ͬ������ǰ�̵߳ȴ�a_thread���� */
    res = pthread_join(a_thread, &thread_result);

    printf("Thread joined, it returned %s\r\n", (char *)thread_result);
    printf("Message is now %s\r\n", message);

    exit(EXIT_FAILURE); 
}

/* ���̵߳Ļص����� */
void *thread_function(void *arg)  
{  
    printf("thread_function is running. Argument is %s\r\n", (char *)arg);  
    sleep(3);

    /* �޸�ȫ�ֱ���������Ҳ���Կ����߳�֮�乲��ȫ�ֱ��� */
    strcpy(message, "Bye!");

    /* �߳���ֹ������ĳ�������ָ�룬�����Ǿֲ����� */
    pthread_exit("Thank you for your CPU time!");  
} 

