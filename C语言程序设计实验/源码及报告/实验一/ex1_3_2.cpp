#include<stdio.h>
int main(void)
{
	int a[100];                  /*创建数组存储数据*/
	int i,max,min,x,n;
	printf("Please enter the days: \n");  /*输入天数*/
	scanf("%d",&n);
	printf("Please enter the value:\n");   /*输入收盘价格*/
	for(i=0;i<n;i++)
	{
		scanf("%d ",&a[i]);
	}
	max=0;
	min=a[0];
	for(i=0;i<n;i++)                          /*开始比较*/
	{
		if(a[i]>max)
		{
			max=a[i];
		}
		if(a[i]<min)
		{
			min=a[i];
			
		}
	}
	x=max-min;
	
	printf("The Difference value is %d",x);    /*输出*/
	return 0;
	
 }

