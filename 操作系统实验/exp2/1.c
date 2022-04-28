#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <pthread.h>



int all;
int num = 0;
int semid;

void P(int semid, int index);
void V(int semid, int index);
void *pthread1(void *id);

int main(void)
{
    int n = 0;
    printf("飞机票总数: ");
    scanf("%d", &all);
    printf("创建售票线程个数");
    scanf("%d", &n);
    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666); //创建信号灯
    if (semid == -1)
    {
        printf("信号灯集创建失败!\n");
        exit(1);
    }

    union semun sem;
    sem.val = 1; //初始值
    if (semctl(semid, 0, SETVAL, sem) == -1)
    {
        printf("信号灯0初始化失败!\n");
        exit(1);
    }


    pthread_t pthread[n];
    for (int i = 0; i < n; i++)
    {
        if (pthread_create(&pthread[i], NULL, pthread1, (void *)i))
        {
            printf("线程%d创建失败!\n", i);
            exit(1);
        }
    }


    for (int j = 0; j < n; j++)
    { //等待线程结束
        if (pthread_join(pthread[j], NULL))
        {
            printf("线程%d结束失败!\n", j);
            exit(1);
        }
    }

    semctl(semid, 0, IPC_RMID, NULL); //删除信号灯集
    exit(0);
}



void P(int semid, int index){
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}

void V(int semid, int index){
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}

void *pthread1(void* id){
    long pthread = (long) id;
    int count = 0;
    while(1){
        P(semid, 0);
        
        if(num < all){
            num += 1;
            printf("线程%ld已售票数: %d\n", pthread, num);
            count++;
            
        }
        else{
            printf("线程%ld总售票数: %d\n", pthread,count);
            V(semid, 0);
            pthread_exit(NULL); //结束线程
        }
        V(semid, 0);
        }
}

