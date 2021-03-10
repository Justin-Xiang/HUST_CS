#include<stdio.h>
#include<math.h>
int IsPrime(int n)             //函数定义
{
	int j;
	for(j=2;j<=sqrt(n);j++)
	{
		if(n%j==0)
		{
			return 0;
		}
	}
	return 1;
}

int main(void)
{
	int i,count=0,m;
	printf("请输入m\n");
	scanf("%d",&m);
	for(i=3;i<m;i++)
	{
		if(IsPrime(i)&&IsPrime(i+2))     //判断是否为孪生素数
		{
			printf("(%d,%d) ",i,i+2);
			count++;
			if(count%5==0)                 //每5个换行一次
			{
				printf("\n");
			}
		}
	}
	return 0;
}

