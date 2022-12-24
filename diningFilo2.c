#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define TICK struct timespec

void *philospher_do(void *who);
void clean_terminate(int num);
int eat();

int main(int argc, char const *argv[])
{
    int philos[] = {0, 1, 2, 3, 4};
    int philo_frst = 0;
    int philo_scnd = philo_frst + 2;
    signal(SIGINT, clean_terminate);
    while (1)
    {
        pthread_t frst, scnd;
        int *a = malloc(sizeof(int));
        int *b = malloc(sizeof(int));
        *a = philo_frst;
        *b = philo_scnd;
        pthread_create(&frst, NULL, philospher_do, a);
        pthread_create(&scnd, NULL, philospher_do, b);
        pthread_join(frst, NULL);
        pthread_join(scnd, NULL);
        philo_frst = (philo_frst + 1) % 5;
        philo_scnd = (philo_scnd + 1) % 5;
    }
    return 0;
}

void *philospher_do(void *who)
{
    int num = *((int *)who);
    printf("p%d eating\n", num);
    eat();
    printf("p%d done eating\n", num);
    printf("p%d thinking\n", num);
    return NULL;
}

int rand_sec()
{
    TICK time_stamp;
    clock_gettime(CLOCK_MONOTONIC, &time_stamp);
    srand(time_stamp.tv_nsec);
    int dormir = (rand() % 1) + 1;
    return dormir;
}

int eat()
{
    int tonie = rand_sec();
    sleep(tonie);
    return 0;
}

void clean_terminate(int num)
{
    printf("--------PHILOSPHERS LEFT :(--------\n");
    exit(0);
}