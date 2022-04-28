#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <pthread.h>

int a;
int semid;

void P(int semid, int index);
void V(int semid, int index);
void *pthread1();
void *pthread2();
void *pthread3();

    int main(void)
{
    semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666);
    if (semid == -1)
    {
        printf("信号灯集创建失败!\n");
        exit(1);
    }
    union semun sem[3];
    sem[0].val = 1;
    sem[1].val = 0;
    sem[2].val = 0;
    if (semctl(semid, 0, SETVAL, sem[0]) == -1)
    {
        printf("信号灯0初始化失败!\n");
        exit(1);
    }
    if (semctl(semid, 1, SETVAL, sem[1]) == -1)
    {
        printf("信号灯1初始化失败!\n");
        exit(1);
    }
    if (semctl(semid, 2, SETVAL, sem[2]) == -1)
    {
        printf("信号灯2初始化失败!\n");
        exit(1);
    }

    pthread_t p1, p2, p3;
    if (pthread_create(&p1, NULL, pthread1, NULL))
    {
        printf("线程1创建失败!\n");
        exit(1);
    }
    if (pthread_create(&p2, NULL, pthread2, NULL))
    {
        printf("线程2创建失败!\n");
        exit(1);
    }
    if (pthread_create(&p3, NULL, pthread3, NULL))
    {
        printf("线程3创建失败!\n");
        exit(1);
    }
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    semctl(semid, 0, IPC_RMID, NULL);
    exit(0);
}


void P(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}

void V(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}

void *pthread1(){
    a = 0;
    for(int i = 1;i <= 100; i++){
        P(semid, 0);
        a = a + i;
        V(semid, 1);
    }
}

void *pthread2(){
    for(int i = 1; i <=100; i++){
        P(semid, 1);
        if(a%2 == 0){
            printf("打印线程1: a = %d\n", a);
        }
        V(semid, 2);
    }
}

void *pthread3(){
    for(int i = 1; i <= 100; i++){
        P(semid, 2);
        if(a%2 != 0){
            printf("打印线程2: a = %d\n", a);
        }
        V(semid, 0);
    }
}

