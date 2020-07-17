/*
 * NOTES:
 * 一次创建多个线程，并让每个线程sleep随机时间
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 6

void *thread_function(void *arg);

int main()
{
    int res;
    pthread_t a_thread[NUM_THREADS];
    void *thread_result;
    int lots_of_thread;

    for (lots_of_thread = 0; lots_of_thread < NUM_THREADS; lots_of_thread++) {
        res = pthread_create(&(a_thread[lots_of_thread]), NULL, thread_function, (void *)&lots_of_thread);
        if (res != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }

    printf("Waiting for threads to finish...\n");
    for (lots_of_thread = NUM_THREADS - 1; 0 <= lots_of_thread; lots_of_thread--) {
        res = pthread_join(a_thread[lots_of_thread], &thread_result);
        if (res == 0)
            printf("Picked up a thread\n");
        else
            perror("pthread_join failed");
    }
    printf("All done\n");
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
    int my_number = *(int *)arg;
    int rand_num;

    printf("thread_function is running. Argument was %d\n", my_number);
    rand_num = 1 + (int)(9.0 * rand() / (RAND_MAX + 1.0));
    sleep(rand_num);
    printf("Bye from %d\n", my_number);
    pthread_exit(NULL);
}

// leo@ubuntu:~/c_test$ ./a.out 
// thread_function is running. Argument was 0
// thread_function is running. Argument was 1
// thread_function is running. Argument was 2
// thread_function is running. Argument was 3
// thread_function is running. Argument was 4
// Bye from 1
// thread_function is running. Argument was 5
// Waiting for threads to finish...
// Bye from 5
// Picked up a thread
// Bye from 0
// Bye from 2
// Bye from 3
// Bye from 4
// Picked up a thread
// Picked up a thread
// Picked up a thread
// Picked up a thread
// Picked up a thread
// All done