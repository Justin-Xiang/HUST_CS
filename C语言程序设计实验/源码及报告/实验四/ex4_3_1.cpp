#include<stdio.h>
#include<math.h>
void Goldbach(int x)
{
	int a,b,m,n,i,flag1=1,flag2=1;
	for(a=2;a<=(x/2);a++)
	{
		m=a;
		n=sqrt(m);
		for(i=2;i<=n;i++)
		{
			if(m%i==0)
			{
				flag1=0;
				break;
			}
		}
		b=x-m;
		n=sqrt(b);
		for(i=2;i<=n;i++)
		{
			if(b%i==0)
			{
				flag2=0;
				break;
			}
		}
		if(flag1&&flag2)
		{
			printf("%d=%d+%d\n",x,a,b);
		}
		flag1=1;
		flag2=1;
	}
}
int main(void)
{
	int x;
	printf("请输入一个大于等于4的偶数\n"); 
	scanf("%d",&x);
	Goldbach(x);
	return 0; 
}
