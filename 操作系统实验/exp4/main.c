#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>

void getmode(struct stat buf)
{ //-l参数时按照相应格式打印
    if (S_ISLNK(buf.st_mode))
        printf("l");
    else if (S_ISREG(buf.st_mode))
        printf("-");
    else if (S_ISDIR(buf.st_mode))
        printf("d");
    else if (S_ISCHR(buf.st_mode))
        printf("c");
    else if (S_ISBLK(buf.st_mode))
        printf("b");
    else if (S_ISFIFO(buf.st_mode))
        printf("f");
    else if (S_ISSOCK(buf.st_mode))
        printf("s");
    //获取打印文件所有者权限
    if (buf.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");

    if (buf.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");

    if (buf.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");

    //所有组权限
    if (buf.st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");

    if (buf.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");

    if (buf.st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");

    //其他人权限
    if (buf.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");

    if (buf.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");

    if (buf.st_mode & S_IXOTH)
        printf("x ");
    else
        printf("- ");

    return;
}

void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if ((dp = opendir(dir)) == NULL)
    {
        printf("目录打开失败！\n");
        return;
    }
    if (chdir(dir) == -1)
    {
        printf("改变目录失败！\n");
        return;
    }
    while ((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode))
        { //判断是否为目录
            if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
                continue; //只结束本次循环，而不是跳出循环

            for (int i = 0; i < depth; i++)
            {
                printf(" ");
            }
            getmode(statbuf);
            //根据uid和gid获取文件所有者的用户名和组名
            struct passwd *psd;                //从该结构体接收文件所有者用户名
            struct group *grp;                 //获取组名
            psd = getpwuid(statbuf.st_uid);    //文件所有者
            grp = getgrgid(statbuf.st_gid);    //文件所有者对应组
            printf("%-ld ", statbuf.st_nlink); //链接数
            printf("%-4s ", psd->pw_name);     //文件所有者
            printf("%-4s ", grp->gr_name);     //文件所有者对应组

            printf("%-4ld ", statbuf.st_size);                      //文件大小
            printf("%-4s ", strtok(ctime(&statbuf.st_mtim), "\n")); // ctime返回时间字符串，strtok将字符串分割
            printf("%-4s\n", entry->d_name);
            printdir(entry->d_name, depth + 4);
        }
        else
        {
            for (int i = 0; i < depth; i++)
            {
                printf(" ");
            }
            getmode(statbuf);
            //根据uid和gid获取文件所有者的用户名和组名
            struct passwd *psd;                 //从该结构体接收文件所有者用户名
            struct group *grp;                  //获取组名
            psd = getpwuid(statbuf.st_uid);     //文件所有者
            grp = getgrgid(statbuf.st_gid);     //文件所有者对应组
            printf("%-4ld ", statbuf.st_nlink); //链接数
            printf("%-4s ", psd->pw_name);      //文件所有者
            printf("%-4s ", grp->gr_name);      //文件所有者对应组

            printf("%-4ld ", statbuf.st_size);                      //文件大小
            printf("%-4s ", strtok(ctime(&statbuf.st_mtim), "\n")); // ctime返回时间字符串，strtok将字符串分割
            printf("%-4s\n", entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
    return;
}

int main()
{
    char name[100];
    printf("输入目录：");
    scanf("%s", name);
    printdir(name, 1);
    return 0;
}