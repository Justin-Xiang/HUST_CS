#include<stdio.h>
int main(void)
{
	int a[100];                  /*��������洢����*/
	int i,max,min,x,n;
	printf("Please enter the days: \n");  /*��������*/
	scanf("%d",&n);
	printf("Please enter the value:\n");   /*�������̼۸�*/
	for(i=0;i<n;i++)
	{
		scanf("%d ",&a[i]);
	}
	max=0;
	min=a[0];
	for(i=0;i<n;i++)                          /*��ʼ�Ƚ�*/
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
	
	printf("The Difference value is %d",x);    /*���*/
	return 0;
	
 }

