//导入头文件
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define max 10 //最多10条

pid_t p1, p2;
int pipefd[2]; //创建管道 0用于读 1用于写

void parent_sigint(int sig_no);
void child1(int sig_no);
void child2(int sig_no);

int main()
{
    char s[50];   //存储信息
    pipe(pipefd); //在该进程中创建无名管道

    signal(SIGINT, parent_sigint); //中断信号处理函数
    int count = 0;                 //计数器
    if ((p1 = fork()) == 0)        //创建子进程1
    {
        signal(SIGINT, SIG_IGN);                  //忽略子进程1的中断信号
        signal(SIGUSR1, child1);                  //子进程1的信号处理函数
        close(pipefd[1]);                         //关闭写端
        while (read(pipefd[0], s, sizeof(s)) > 0) //读取管道
        {
            printf("%s\n", s); //打印信息
            count++;           //计数器加1
        }
        printf("子进程1读取了%d条信息\n", count); //打印计数器
        close(pipefd[0]);                         //关闭读端
        exit(0);                                  //退出子进程1
    }
    else
    {
        if ((p2 = fork()) == 0) //创建子进程2
        {
            signal(SIGINT, SIG_IGN);                  //忽略子进程2的中断信号
            signal(SIGUSR2, child2);                  //子进程2的信号处理函数
            close(pipefd[1]);                         //关闭写端
            while (read(pipefd[0], s, sizeof(s)) > 0) //读取管道
            {
                printf("%s\n", s); //打印信息
                count++;           //计数器加1
            }
            printf("子进程2读取了%d条信息\n", count); //打印计数器
            close(pipefd[0]);                         //关闭读端
            exit(0);                                  //退出子进程2
        }
        else
        {
            //父进程
            int p_count = 1;
            close(pipefd[0]);      //关闭读端
            while (p_count <= max) //循环读取信息
            {
                sprintf(s, "I send you %d times.", p_count);
                write(pipefd[1], s, sizeof(s)); //写入管道
                p_count++;                      //计数器加1
                sleep(1);                       //睡眠1秒
            }
            close(pipefd[1]); //关闭写端
            wait(NULL);       //等待子进程1
            wait(NULL);       //等待子进程2
            printf("Parent Process is killed\n");
            exit(0); //退出父进程
        }
    }
}

void parent_sigint(int sig_no)
{
    kill(p1, SIGUSR1);
    kill(p2, SIGUSR2);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
    printf("Parent Process is Killed!\n");
    exit(1);
}

void child1(int sig_no)
{
    close(pipefd[0]);
    printf("Child Process 1 is killed by Parent\n");
    exit(1);
}

void child2(int sig_no)
{
    close(pipefd[0]);
    printf("Child Process 2 is killed by Parent\n");
    exit(1);
}
