/*
 * NOTES:
 * 信号量用来同步
 * 
 * - 二进制信号量：只要01两种取值
 * - 计数信号量：可以由有更大范围的取值
 * 
 * 四个信号量函数：
 * sem_init：初始化信号量。
 * sem_post：给信号量值+1
 * sem_wait：给信号量值-1。如果sem值是0，wait会阻塞，直到sem大于0
 * sem_destory：清理信号量
 * 
 * 也可以用互斥量来进行同步，非常繁琐
 * 与信号量类似，互斥量也有四个函数
 * pthread_mutex_inint
 * pthread_mutex_lock
 * pthread_mutex_unlock
 * pthread_mutex_destory
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function(void *arg);
sem_t bin_sem;

#define WORK_SIZE 1024
char work_area[WORK_SIZE];

int main()
{
    int res;
    pthread_t a_thread;
    void *thread_result;

    res = sem_init(&bin_sem, 0, 0);
    if (res != 0) {
        perror("sem_init failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if (res != 0) {
        perror("pthread_create failed");
        exit(EXIT_FAILURE);
    }

    printf("Input some text. Enter 'end' to finish\n");
    while (strncmp("end", work_area, 3) != 0) {
        fgets(work_area, WORK_SIZE, stdin);
        sem_post(&bin_sem);
    }

    printf("\nWaiting for thread to finish...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("pthread_join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined\n");
    sem_destroy(&bin_sem);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
    sem_wait(&bin_sem);
    while (strncmp("end", work_area, 3) != 0) {
        printf("You input %d characters\n", (int)strlen(work_area) - 1);
        sem_wait(&bin_sem);
    }
    pthread_exit(NULL);
}

// leo@ubuntu:~/c_test$ ./a.out 
// Input some text. Enter 'end' to finish
// asd
// You input 3 characters

// You input 0 characters
// end

// Waiting for thread to finish...
// Thread joined