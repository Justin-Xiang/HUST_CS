#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX 10
#define size 1024
#define shmsize 10240
#define SHMKEY 10
#define LENKEY 11
#define SEMKEY 20
int semid;
int shmid;
int lenid;
char *buf;
int *len;
void P(int semid, int index);
void V(int semid, int index);

int main()
{
    printf("put run\n");
    shmid = shmget(SHMKEY, size, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        printf("共享内存获取失败！\n");
        exit(1);
    }
    buf = shmat(shmid, 0, 0);
    lenid = shmget(LENKEY, 4, IPC_CREAT | 0666);
    if (lenid == -1)
    {
        printf("长度共享内存获取失败！\n");
        exit(1);
    }
    len = shmat(lenid, 0, 0);

    semid = semget(SEMKEY, 2, IPC_CREAT | 0666);
    if (semid == -1)
    {
        printf("信号灯集获取失败！\n");
        exit(1);
    }

    FILE *pfile = fopen("hello_copy", "w");
    if (pfile == NULL)
        printf("打开写入文件失败\n");
    int k = 0;
    while (1)
    {
        P(semid, 1);
        if (*(buf + size * ((k + 1) % MAX) + 0) == 'E' && *(buf + size * ((k + 1) % MAX) + 1) == 'O' && *(buf + size * ((k + 1) % MAX) + 2) == 'F')
        {
            printf("run:k=%d\n", k);
            printf("run:len=%d\n", *len);
            fwrite((buf + size * (k % MAX)), 1, *len, pfile);
            V(semid, 0);
            break;
        }
        printf("run:k=%d\n", k);
        fwrite((buf + size * (k % MAX)), 1, size, pfile);
        k++;
        V(semid, 0);
    }
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