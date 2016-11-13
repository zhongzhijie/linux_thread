
#include "pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *thread_function(void *arg);

int flag = 1;

int main(void)
{
    int res;
    int count = 1;
    pthread_t a_thread;
    void *thread_result;

    /* �����߳� */
    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if (0 != res)
    {
        perror("Thread create failed!");
        exit(EXIT_FAILURE);
    }

    while (count++ <= 20)  
    {  
        if (flag == 1)  
        {  
            printf ("1\r\n");  
            flag = 2;  
        }  
        else  
        {  
            sleep(1);  
        }  
    }
    
    printf("Waiting for thread to finish...\r\n");

    /* �߳�ͬ������ǰ�̵߳ȴ�a_thread���� */
    res = pthread_join(a_thread, &thread_result);

    printf("Thread joined, it returned %s\r\n", (char *)thread_result);

    exit(EXIT_FAILURE); 
}

/* ���̵߳Ļص����� */
void *thread_function(void *arg)  
{  
    int count = 1;  
  
    while (count++ <= 20)  
    {  
        if (flag == 2)  
        {  
            printf("2\r\n");  
            flag = 1;  
        }  
        else  
        {  
            sleep(1);  
        }  
    } 

    /* �߳���ֹ������ĳ�������ָ�룬�����Ǿֲ����� */
    pthread_exit("Thank you for your CPU time!");  
} 

