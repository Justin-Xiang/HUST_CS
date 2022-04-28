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
    printf("get run\n");
    shmid = shmget(SHMKEY, shmsize, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        printf("共享内存获取失败！\n");
        exit(1);
    }

    //共享内存绑定
    //绑定之后 直接操作buf
    buf = shmat(shmid, 0, 0);
    lenid = shmget(LENKEY, 4, IPC_CREAT | 0666);
    if (lenid == -1)
    {
        printf("长度共享内存获取失败！\n");
        exit(1);
    }
    //同上
    len = shmat(lenid, 0, 0);

    semid = semget(SEMKEY, 2, IPC_CREAT | 0666);
    if (semid == -1)
    {
        printf("信号灯集获取失败！\n");
        exit(1);
    }

    FILE *pfile = fopen("hello", "rb");
    if (pfile == NULL)
        printf("打开读写文件失败\n");
    fseek(pfile, 0L, SEEK_END);
    // pfile返回当前位置
    int flen = ftell(pfile);
    printf("len=%d\n", flen);
    //重制文件指针
    fseek(pfile, 0L, SEEK_SET);
    printf("flen/size=%d\n", flen / size);

    if (flen % size == 0)
    {
        int i = 0;
        while (1)
        {
            P(semid, 0);
            printf("get:i=%d\n", i);
            // args:
            //内存块指针
            //每个元素大小 字节
            //元素个数
            //文件指针
            fread((buf + size * (i % MAX)), 1, size, pfile);
            i++;
            if (i == (flen / size))
            {
                *(buf + size * (i % MAX)) = 'E';
                *(buf + size * (i % MAX) + 1) = 'O';
                *(buf + size * (i % MAX) + 2) = 'F';
                V(semid, 1);
                break;
            }
            V(semid, 1);
        }
    }
    else
    {
        int i = 0;
        while (1)
        {
            P(semid, 0);
            if (i == (flen / size))
            {
                printf("get:i=%d\n", i);
                *len = fread((buf + size * (i % MAX)), 1, size, pfile);
                printf("get:len=%d\n", *len);
                i++;
                printf("get:i=%d\n", i);
                *(buf + size * (i % MAX)) = 'E';
                *(buf + size * (i % MAX) + 1) = 'O';
                *(buf + size * (i % MAX) + 2) = 'F';
                V(semid, 1);
                break;
            }
            else
            {
                printf("get:i=%d\n", i);
                fread((buf + size * (i % MAX)), 1, size, pfile);
                i++;
                V(semid, 1);
            }
        }
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