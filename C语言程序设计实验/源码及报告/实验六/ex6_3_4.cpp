#include<stdio.h>
void spin(int *b,int n,int m);
int main()
{
    int i,j,a[20][20],m,n;
    int *b=&a[0][0];
    printf("输入行数和列数\n");
    scanf("%d%d",&n,&m);
    printf("依次输入\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&a[i][j]);
    spin(b,n,m);
    return 0;
}
void spin(int *b,int n,int m)
{
    int i,j,p;
    for(j=m-1;j>=0;j--){
        for(i=0;i<n;i++){
            p=*(b+i*20+j);
            printf("%d ",p);
        }
        printf("\n");
    }
}
