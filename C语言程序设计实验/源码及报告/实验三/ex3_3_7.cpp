#include<stdio.h>
#include<math.h>
int IsPrime(int n)
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
	printf("ÇëÊäÈëm\n");
	scanf("%d",&m);
	for(i=3;i<m;i++)
	{
		if(IsPrime(i)&&IsPrime(i+2))
		{
			printf("(%d,%d) ",i,i+2);
			count++;
			if(count%5==0)
			{
				printf("\n");
			}
		}
	}
	printf("\ncount=%d",count);
	return 0;
}
