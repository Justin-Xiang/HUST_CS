#include<stdio.h>
#include<math.h>
int main(void)
{
	int a[100];
	int i,max,min,x,n;
	printf("Please enter the days: \n");
	scanf("%d",&n);
	printf("Please enter the value:");
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	max=fabs(a[1]-a[0]);
	for(i=0;i<n-1;i++)
	{
		if(fabs((a[i+1]-a[i]))>max)
		{
			max=fabs(a[i+1]-a[i]);
		}
	
}
	
	printf("The Difference value is %d",max);
	return 0;
	
 } 
