#include<stdio.h>
int main(void)
{unsigned short x,m,n;
printf("Input x,m,n:");
scanf("%hx %hu %hu",&x,&m,&n);
if(!(m<=15 && m>=0 && n>=1 && n<=(16-m)))//���m��n�ķ�Χ
    {
    printf("Error!");
    }
else if(n==16)//n=16ʱ��������ȡ������x
    {
    printf("%#hx",x);
    }
else
    {
    x &= ~(~0<<n)<<m;//ȡ��x�ӵ�mλ��ʼ�����nλ
    x <<= (15-m-n+1);//����˿���
    printf("%#hx",x);
    }
}
