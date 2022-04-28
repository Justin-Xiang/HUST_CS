#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAX 10
#define size 1024
#define shmsize 10240

//键值
#define SHMKEY 10
#define LENKEY 11
#define SEMKEY 20


pid_t p1, p2;
int semid;
int shmid;
int lenid;

int main()
{   
    //共享内存创建
    shmid = shmget(SHMKEY, shmsize, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        printf("共享内存创建失败！\n");
        exit(1);
    }
    //长度内存创建
    lenid = shmget(LENKEY, 4, IPC_CREAT | 0666);
    if (lenid == -1)
    {
        printf("长度共享内存创建失败！\n");
        exit(1);
    }

    //信号灯集创建
    semid = semget(SEMKEY, 2, IPC_CREAT | 0666);
    if (semid == -1)
    {
        printf("信号灯集创建失败！\n");
        exit(1);
    }

    union semun empty, full;
    empty.val = MAX;
    full.val = 0;
    if (semctl(semid, 0, SETVAL, empty) == -1)
    {
        printf("信号灯0初始化失败！\n");
        exit(1);
    }
    if (semctl(semid, 1, SETVAL, full) == -1)
    {
        printf("信号灯1初始化失败！\n");
        exit(1);
    }

    if ((p1 = fork()) == 0)
    {
        printf("get created\n");
        execv("./get", NULL);
    }
    else
    {
        if ((p2 = fork()) == 0)
        {
            printf("put created\n");
            execv("./put", NULL);
        }
        else
        {
            wait(NULL);
            wait(NULL);
            //清楚信号灯
            //删除共享内存
            semctl(semid, 0, IPC_RMID, NULL);
            shmctl(shmid, IPC_RMID, 0);
            shmctl(lenid, IPC_RMID, 0);
            exit(0);
        }
    }
}
