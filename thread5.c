#include <pthread.h>  
#include <stdio.h>  
#include <stdlib.h>  
  
#define NUM 8  
  
void *thread_function(void *arg);  
  
int main()  
{  
    int res;  
    pthread_t a_thread[NUM];  
    void *thread_result;  
    int index;  
  
    for (index = 0; index < NUM; ++index) {  
        res = pthread_create(&a_thread[index], NULL, thread_function, (void *)index);  
        if (res != 0)  
        {  
            perror("Thread create failed!");  
            exit(EXIT_FAILURE);  
        }  
        sleep(1);  
    }  
  
    printf("Waiting for threads to finished...\r\n");  
  
    for (index = NUM - 1; index >= 0; --index)  
    {  
        res = pthread_join(a_thread[index], &thread_result);  
        if (res == 0)  
        {  
            printf("Picked up a thread:%d\r\n", index + 1);  
        }  
        else  
        {  
            perror("pthread_join failed\r\n");  
        }  
    }  
  
    printf("All thread done\r\n");  
      
    exit(EXIT_SUCCESS);  
}  
  
void *thread_function(void *arg)  
{  
    int my_number = (int)arg;  
    int rand_num;  
  
    printf("thread_function is running. Argument was %d\r\n", my_number);  
    rand_num = 1 + (int)(9.0 * rand()/(RAND_MAX + 1.0));  
    sleep(rand_num);  
    printf("Bye from %d\r\n", my_number);  
    pthread_exit(NULL);  
}  
