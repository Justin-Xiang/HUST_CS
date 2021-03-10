//
// Created by JustinXiang on 2021/2/27.
//

#include "define.h"

int j, k ,z, final, add, num1, num2, r, l; //r为行 l为列


/*读取棋盘文件*/
void Readqipan(char * filename)
{
    FILE * fp;
    fp = fopen(filename,"r");
    if(fp == NULL)
    {
        printf("文件打开失败!\n");
    }
    else
    {
        int integer; //用于接受数字
        i = 0;
        while(fscanf(fp,"%d",&integer) != EOF)
        {
            qipan[i].num = integer;
            if(integer !=-1 ) qipan[i].flag = 1;
            else qipan[i].flag = 0;
            i++;
        }
    }
    fclose(fp);
    printf("读取成功！\n");
}



/*随机生成数独*/
void RandGener(char * filename)
{
    FILE * fp;
    fp = fopen(filename,"r");
    if(fp == NULL)
    {
        printf("文件打开失败");
    }
    else{
        int integer;
        srand((unsigned)time(NULL));
        int x =11+rand()%11;
        int j;
        i = 0;
        while(fscanf(fp,"%d",&integer) != EOF)
        {
            qipan[i].num = integer;
            qipan[i].flag = 1;
            i++;
        }

        for(j = 0 ;j<x;j++)
        {
            int r = rand()%6;
            int c = rand()%6;
            qipan[r*6+c].num = -1;
            qipan[r*6+c].flag = 0;

        }
    }
    fclose(fp);
    printf("生成成功!\n");
}


/*输出当前棋盘*/
void Showqipan(struct Qipan qipan[])
{
    for(i=0;i<36;i++)
    {
        if(qipan[i].num == -1) printf("_ ");
        else printf("%d ",qipan[i].num);
        if((i+1)%6 == 0) putchar('\n');
    }
}

/*初始化棋盘*/
void Resetqipan(struct Qipan qipan[])
{
    for(i=0;i<36;i++)
    {
        if(qipan[i].flag != 1) qipan[i].num = -1;
    }
}


/*数独交互*/
void PlaySuDoKu(struct Qipan qipan[])
{
    printf("当前棋盘:\n");
    Showqipan(qipan);
    printf("请分别输入 行 列 1或0 来填补空缺:\n");
    printf("重新开始则连续输入三个0.\n结束填写则输入连续输入三个7 7 7\n");
    int answer[3] = {-1};
    while(scanf("%d",&answer[0]) != EOF)
    {
        for(i = 1; i < 3; i++)
        {
            scanf("%d",&answer[i]);
        }
        if(answer[0]==0 && answer[1]==0 && answer[2] == 0)
        {
            Resetqipan(qipan);
            printf("重新开始!\n");
        }
        else if(answer[0]==7 && answer[1]==7 && answer[2] == 7)
        {

            printf("结束!\n");
            return;
        }
        else
        {
            temp = (answer[0]-1)*6 + answer[1];
            if(qipan[temp-1].flag == 1){
                printf("该位置为初始位置，不可修改！\n");
            }
            else
            {
                qipan[temp-1].num = answer[2];
            }
        }
        putchar('\n');
        Showqipan(qipan);
        printf("\n继续输入!\n");
    }
}


/*检查棋盘是否填满*/
status Checkqipan(struct Qipan qipan[])
{
    for(i=0;i<36;i++)
    {
        if(qipan[i].num == -1) return ERROR;
    }
    return OK;
}


/*转化为CNF文件*/
void SetCNFfile(struct Qipan qipan[])
{
    printf("输入要转化为CNF文件的文件名:\n");
    scanf("%s",filename_setcnf);
    FILE * fp;
    fp = fopen(filename_setcnf,"w");
    if(fp == NULL)
    {
        printf("文件打开失败!\n");
        exit(1);
    }
    int f_sum = 0;  //公式数计数器
    for(i = 0; i <36;i++)
    {
        if(qipan[i].num!= -1) f_sum++;
    }
    fprintf(fp,"p cnf 606 %d\n",f_sum+2286);

    /*---------------------------------------*/
    //根据棋盘信息
    /*---------------------------------------*/

    for(i = 0; i<36;i++)
    {
        if(qipan[i].num == 1)
        {
            fprintf(fp,"%d 0\n",i+1);
        }
        else if(qipan[i].num == 0)
        {
            fprintf(fp,"%d 0\n",-(i+1));
        }
        continue;
    }

    /*---------------------------------------*/
    //约束1：行列中无连续的0或1
    /*---------------------------------------*/

    //处理6行
    for(r = 1;r<=6;r++)
    {
        for(l = 1;l<=4;l++)
        {
            for(i=0;i<3;i++)
            {
                temp = (r-1)*6 + l +i;
                fprintf(fp,"%d ",temp);
                if(i==2){
                    fprintf(fp,"0\n");
                }
            }
            for(i = 0;i<3;i++)
            {
                temp = (r-1)*6 + l + i;
                fprintf(fp,"%d ",-temp);
                if(i==2)
                {
                    fprintf(fp,"0\n");
                }
            }
        }
    }


    //处理6列
    for(l = 1; l<=6;l++)
    {
        for(r = 1;r<=4;r++)
        {
            for(i=0;i<3;i++)
            {
                temp = (r+i-1)*6 + l;
                fprintf(fp,"%d ",temp);
                if(i==2)
                    fprintf(fp,"0\n");
            }
            for(i=0;i<3;i++)
            {
                temp = (r+i-1) *6 +l;
                fprintf(fp,"%d ",-temp);
                if(i==2)
                    fprintf(fp,"0\n");
            }
        }
    }
    /*---------------------------------------*/
    //约束2：行，列中0，1个数相同
    /*---------------------------------------*/
    int order[16][5] = {{3,4,5,6},{2,4,5,6},{2,3,5,6},{2,3,4,6},{2,3,4,5}
            ,{1,4,5,6},{1,3,5,6},{1,3,4,6},{1,3,4,5}
            ,{1,2,5,6},{1,2,4,6},{1,2,4,5}
            ,{1,2,3,6},{1,2,3,5}
            ,{1,2,3,4}};
    //处理6行
    for (r = 1; r <= 6; r++){
        for (k = 0; k < 15; k++){
            for(j = 0; j < 4; j++){
                temp = (r - 1)*6 + order[k][j];
                fprintf(fp, "%d ", temp);
                if (j == 3) fprintf(fp, "0\n");
            }
        }
    }
    for (r = 1; r <= 6; r++){
        for (k = 0; k < 15; k++){
            for(j = 0; j < 4; j++){
                temp = (r - 1)*6 + order[k][j];
                fprintf(fp, "%d ", -temp);
                if (j == 3) fprintf(fp, "0\n");
            }
        }
    }
    //处理6列
    for (l = 1; l <= 6; l++){
        for (k = 0; k < 15; k++){
            for(j = 0; j < 4; j++){
                temp = (order[k][j] - 1)*6 + l;
                fprintf(fp, "%d ", temp);
                if (j == 3) fprintf(fp, "0\n");
            }
        }
    }
    for (l = 1; l <= 6; l++){
        for (k = 0; k < 15; k++){
            for(j = 0; j < 4; j++){
                temp = (order[k][j] - 1)*6 + l;
                fprintf(fp, "%d ", -temp);
                if (j == 3) fprintf(fp, "0\n");
            }
        }
    }
    /*---------------------------------------*/
    //约束3：没有相同的行或列
    /*---------------------------------------*/
    add = 36;
    for(i=1;i<=6;i++)
    {
        for(j = i+1;j<=6;j++)
        {
            final = add +19;
            for(k=1;k<=6;k++)
            {
                num1 = (i-1)*6 + k;
                num2 = (j-1)*6 + k;
                fprintf(fp,"%d -%d 0\n%d -%d 0\n-%d -%d %d 0\n", num1,add+1,num2,add+1,num1,num2,add+1);
                fprintf(fp,"-%d -%d 0\n-%d -%d 0\n%d %d %d 0\n", num1,add+2,num2,add+2,num1,num2,add+2);
                fprintf(fp,"-%d %d 0\n-%d %d 0\n%d %d -%d 0\n", add+1,add+3,add+2,add+3,add+1,add+2,add+3);
                add+=3;
            }
            for(z = 1;z<=6;z++)
            {
                fprintf(fp,"%d %d 0\n",final-3*(z-1)-1,final);
            }
            fprintf(fp,"-%d -%d -%d -%d -%d -%d -%d 0\n",final-16,final-13,final-10,final-7,final-4,final-1,final);
            add = final;
        }
    }
    //处理6列
    for (i = 1; i <= 6; i++){
        for (j = i + 1; j <= 6; j++){
            final = add + 19;
            for (k = 1; k<= 6; k++){
                num1 = (k - 1)*6 + i;
                num2 = (k - 1)*6 + j;
                fprintf(fp,"%d -%d 0\n%d -%d 0\n-%d -%d %d 0\n", num1,add+1,num2,add+1,num1,num2,add+1);
                fprintf(fp,"-%d -%d 0\n-%d -%d 0\n%d %d %d 0\n", num1,add+2,num2,add+2,num1,num2,add+2);
                fprintf(fp,"-%d %d 0\n-%d %d 0\n%d %d -%d 0\n", add+1,add+3,add+2,add+3,add+1,add+2,add+3);
                add+=3;
            }
            for (z = 1; z <= 6; z++){
                fprintf(fp,"%d %d 0\n", final - 3*(z - 1) - 1,final);
            }
            fprintf(fp,"-%d -%d -%d -%d -%d -%d -%d 0\n",final-16,final-13,final-10,final-7,final-4,final-1,final);
            add = final;
        }
    }
    fclose(fp);
    printf("文字数：606	公式数：%d\n", f_sum + 2286);
}
