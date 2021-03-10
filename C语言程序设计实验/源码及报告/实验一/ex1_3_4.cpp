#include<stdio.h>
#define n 10                /*行数*/
int main(void)
{
	int i,j,k,c,m;
	for(i=0;i<n;i++)
	{
		for(m=0;m<=n-i;m++)
		{
			printf("  ");           /*打印空格*/
		}
		for(j=0;j<=i;j++)
		{
			if(j==0)
			c=1;
			else
			c=c*(i+1-j)/j;               /*根据公式打印相应的数字*/
			printf("%4d",c);
		}
		printf("\n");
	}
	return 0;
 }

