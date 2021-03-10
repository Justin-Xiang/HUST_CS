#include<stdio.h>
int main(void)
{unsigned short x,m,n;
printf("Input x,m,n:");
scanf("%hx %hu %hu",&x,&m,&n);
if(!(m<=15 && m>=0 && n>=1 && n<=(16-m)))//检查m和n的范围
    {
    printf("Error!");
    }
else if(n==16)//n=16时单独处理，取出整个x
    {
    printf("%#hx",x);
    }
else
    {
    x &= ~(~0<<n)<<m;//取出x从第m位开始向左的n位
    x <<= (15-m-n+1);//向左端靠齐
    printf("%#hx",x);
    }
}
