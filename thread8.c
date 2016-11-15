#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h>

#define BUFFER_SIZE 5  
pthread_mutex_t g_mutex;  
pthread_cond_t g_cond;

typedef struct 
{  
    char buf[BUFFER_SIZE];  
    int count;  
} buffer_t;

buffer_t g_share = {"", 0};  
char g_ch = 'A';

void* producer( void *arg )  
{  
    printf("Producer starting.\n");  
    while(g_ch != 'Z') 
    {  
        pthread_mutex_lock(&g_mutex);  
        if(g_share.count < BUFFER_SIZE)
        {  
            g_share.buf[g_share.count++] = g_ch++;  
            printf("Prodcuer got char[%c]\n", g_ch - 1);  
            if( BUFFER_SIZE == g_share.count ) 
            {  
                printf("Producer signaling full.\n");  
                pthread_cond_signal(&g_cond);  
            }  
        }  
        pthread_mutex_unlock(&g_mutex);  
    }  
    printf("Producer exit.\n");  
    return NULL;  
}

void* consumer( void *arg )  
{  
    int i;
    
    printf("Consumer starting.\n");
    
    while(g_ch != 'Z')
    {  
        pthread_mutex_lock(&g_mutex);  
        printf("Consumer waiting\n");  
        pthread_cond_wait(&g_cond, &g_mutex);  
        printf("Consumer writing buffer\n");  
        for(i = 0; g_share.buf[i] && g_share.count; ++i) 
        {
            putchar(g_share.buf[i]);  
            --g_share.count;  
        }  
        putchar('\n');  
        pthread_mutex_unlock(&g_mutex);  
    }  
    
    printf("Consumer exit.\n");  
    return NULL;  
} 

int main(int argc, char *argv[])  
{  
    pthread_t ppth, cpth;
    
    pthread_mutex_init(&g_mutex, NULL);  
    pthread_cond_init(&g_cond, NULL);
    
    pthread_create(&cpth, NULL, consumer, NULL);  
    pthread_create(&ppth, NULL, producer, NULL);
    
    pthread_join(ppth, NULL);  
    pthread_join(cpth, NULL);
    
    pthread_mutex_destroy(&g_mutex);  
    pthread_cond_destroy(&g_cond);
    
    return 0;  
}
/************************************************************
�Ӵ����лᷢ�֣��ȴ����¼��������Ľӿڶ���Ҫ����һ��������������
��ʵ���������������Ҫ�ڵ�������֮ǰ����������֮�������
������ˣ��ڵ��ò������¼��������Ľӿ�֮ǰҲҪ����������֮�������
�������һ�����⣬�������ַ�ʽ�����ڡ������¼����͡��ȴ��¼����ǻ�Ϊ�ٽ����ġ�
Ҳ����˵��������¼�����û�з�������ô���߳�Ҫ�ȴ�������¼����ͻ���ֹ���¼����ķ�����
���ɴ�һ�㣬��������������ߡ��͡������ߡ��������ص��߶�ľ�š�
����ʵ�ʵ�����ǣ��������ߡ��ڻ���������ʱ���õ�������¼����ġ�֪ͨ����
Ȼ���ַ������ӡ������������������ֱ���������������ַ�������ӡ����֮�󣬡������ߡ��ſ�ʼ����������
Ϊʲô���������Ľ���أ����Ҫ˵��һ��pthread_cond_wait()�ӿڶԻ�������ʲô��
���ǣ�������pthread_cond_wait()���Ȼ������������Ȼ�����ȴ���
���ʱ�������ߡ����ܹ������ٽ�����Ȼ�������������ʱ���������ߡ������źš�
��pthead_cond_wait()��á�֪ͨ��֮������Ҫ�Ի�����������
�������Է�ֹ�������ߡ��������������Ż�����������
���⣬�������ߡ��ڻ���������������²��ܹ���������޶������Ǻ��б�Ҫ�ġ�
��Ϊ��pthread_cond_wait()���֪֮ͨ����û�жԻ���������֮ǰ��
�������ߡ������Ѿ����½����ٽ����ˣ������������ߡ��ֱ���ס�ˡ�
Ҳ������Ϊ�����������ֹ������ʣ������������뻥��������ʹ�á�
************************************************************/
