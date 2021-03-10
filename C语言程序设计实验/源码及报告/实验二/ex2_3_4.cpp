#include<stdio.h>
int main(void)
{
	char a[100];
	int n,i,count=0;
	printf("Please enter the days:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%c ",&a[i]);
	}
	printf("Please enter the exact number:\n");
	for(i=1;i<n-1;i++)
	{
		if(a[i]<a[i-1]&&a[i]<a[i+1])
		{
			count++;
		}
		if(a[i]>a[i-1]&&a[i]>a[i+1])
		{
			count++;
		}
	}
	printf("%d",count);
	return 0;
}
