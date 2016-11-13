
#include <pthread.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <semaphore.h>  
  
#define SIZE 1024  
char buffer[SIZE];

void *thread_function(void *arg);  
pthread_mutex_t mutex;

int main()  
{  
    int res;  
    pthread_t a_thread;  
    void *thread_result;  

    /* 初始化信号量 */
    res = pthread_mutex_init(&mutex, NULL);  
    if (res != 0)  
    {  
        perror("Mutex init failed");  
        exit(EXIT_FAILURE);
    }  
  
    res = pthread_create(&a_thread, NULL, thread_function, NULL);  
    if (res != 0)  
    {  
        perror("Thread create failed");  
        exit(EXIT_FAILURE);  
    }  
  
    printf("Input some text. Enter 'end' to finish\r\n");  
  
    while (1)  
    {
        /* 操作前全局变量必须上锁 */
        pthread_mutex_lock(&mutex);  
        scanf("%s", buffer);
        /* 操作完解锁 */
        pthread_mutex_unlock(&mutex);  
        if (strncmp("end", buffer, 3) == 0)  
            break;  
        sleep(1);  
    }

  
    printf ("Waiting for thread to finish...\r\n");  
  
    res = pthread_join(a_thread, &thread_result);  
    if (res != 0)  
    {  
        perror("Thread join failed");  
        exit(EXIT_FAILURE);  
    }  
  
    printf ("Thread join\r\n");  

    /* 销毁信号量 */
    pthread_mutex_destroy(&mutex);  
  
    exit(EXIT_SUCCESS);  
}  
  
void *thread_function(void *arg)  
{  
    sleep(1);
    
    while (1)  
    {  
        /* 操作前全局变量必须上锁 */
        pthread_mutex_lock(&mutex);  
        printf("You input %d characters\r\n", strlen(buffer));
        /* 操作完解锁 */
        pthread_mutex_unlock(&mutex);  
        if (strncmp("end", buffer, 3) == 0)  
            break;  
        sleep(1);  
    }

    sleep(2);
    printf ("thread finished\r\n");
    pthread_exit(NULL);
}

