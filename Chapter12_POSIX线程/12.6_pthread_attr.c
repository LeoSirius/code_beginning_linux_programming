/*
 * NOTES:
 * 这个程序类似12.3，不过我们不让线程join，而是设置detach属性，让它自己结束
 *
 * 线程属性相关的函数：
 * pthread_attr_init()
 * pthread_attr_destroy()
 * pthread_attr_getxxx
 * pthread_attr_setxxx
 * 
 * 在任何一个时间点上，线程是可结合的（joinable），或者是分离的（detached）。
 * 一个可结合的线程能够被其他线程收回其资源和杀死；在被其他线程回收之前，它的存储器资源（如栈）是不释放的。
 * 相反，一个分离的线程是不能被其他线程回收或杀死的，它的存储器资源在它终止时由系统自动释放。
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);

char message[] = "Hello World";
int thread_finished = 0;

int main()
{
    int res;
    pthread_t a_thread;
    pthread_attr_t thread_attr;

    res = pthread_attr_init(&thread_attr);
    if (res != 0) {
        perror("pthread_attr_init failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    if (res != 0) {
        perror("pthread_attr_setdetachstate failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, &thread_attr, thread_function, (void *)message);
    if (res != 0) {
        perror("pthread_create failed");
        exit(EXIT_FAILURE);
    }

    pthread_attr_destroy(&thread_attr);
    while (!thread_finished) {
        printf("Waiting for thread to say it's finished...\n");
        sleep(1);
    }

    printf("Other thread finished, bye\n");
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
    printf("thread_function is running. Argument was %s\n", (char *)arg);
    sleep(4);
    printf("Second thread setting finished flag, and exiting now\n");
    thread_finished = 1;
    pthread_exit(NULL);
}

// leo@ubuntu:~/c_test$ ./a.out 
// Waiting for thread to say it's finished...
// thread_function is running. Argument was Hello World
// Waiting for thread to say it's finished...
// Waiting for thread to say it's finished...
// Waiting for thread to say it's finished...
// Second thread setting finished flag, and exiting now
// Other thread finished, bye