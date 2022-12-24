#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define NPH 5
#define TICK struct timespec

int err = 0;
int eat();
int think();
void *philospher(void *which_thread);
void clean_terminate(int num);

sem_t frk_sem[NPH];
pthread_t philos[NPH];

int rand_sec()
{
    TICK time_stamp;
    clock_gettime(CLOCK_MONOTONIC, &time_stamp);
    srand(time_stamp.tv_nsec);
    int dormir = (rand() % NPH) + 1;
    return dormir;
}

int threadjoin()
{
    // philosphers leave
    for (int i = 0; i < NPH; i++)
    {
        err = pthread_join(philos[i], NULL);
        if (err)
            perror("pthread_join");
    }
    // destroy fork semphores
    for (int i = 0; i < NPH; i++)
    {
        err = sem_destroy(&frk_sem[i]);
        if (err)
            perror("sem_destroy fork");
    }
    return 0;
}

int threadcreate()
{
    // intialise semaphores
    for (int i = 0; i < NPH; i++)
    {
        err = sem_init(&frk_sem[i], 0, 1);
        if (err)
            perror("sem_init fork");
    }
    // create threads
    for (int i = 0; i < NPH; i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i;
        err = pthread_create(&philos[i], NULL, philospher, arg);
        if (err)
            perror("pthread_create");
    }
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, clean_terminate);
    threadcreate();
    threadjoin();
}

void *philospher(void *which_thread)
{
    int num = *((int *)which_thread);
    while (1)
    {
        printf("p%d thinking\n", num);
        think();
        printf("p%d paused\n", num);
        if (num != NPH - 1)
        {
            err = sem_wait(&frk_sem[num]);
            if (err)
                perror("sem_wait");
            err = sem_wait(&frk_sem[(num + 1) % NPH]);
            if (err)
                perror("sem_wait");
            printf("p%d eating\n", num);
            eat();
            printf("p%d done eating\n", num);
            sem_post(&frk_sem[num]);
            sem_post(&frk_sem[(num + 1) % NPH]);
        }
        else
        {
            err = sem_wait(&frk_sem[(num + 1) % NPH]);
            if (err)
                perror("sem_wait");
            err = sem_wait(&frk_sem[num]);
            if (err)
                perror("sem_wait");
            printf("p%d eating\n", num);
            eat();
            printf("p%d done eating\n", num);
            sem_post(&frk_sem[(num + 1) % NPH]);
            sem_post(&frk_sem[num]);
        }
    }
    return NULL;
}

int eat()
{
    int tonie = rand_sec();
    sleep(tonie);
    return 0;
}

int think()
{
    int totle = rand_sec();
    sleep(totle);
    return 0;
}

void clean_terminate(int num)
{
    printf("--------PHILOSPHERS LEFT :(--------\n");
    exit(0);
}