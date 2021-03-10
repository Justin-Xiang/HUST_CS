#include<stdio.h>
int main(void)
{
	int n,i,k,b;
	b=0;
	char a[11];
	printf("Please input a num:\n");
	for(i=0;i<=10;i++)
	scanf("%c",&a[i]);
	for(i=0;i<=10;i++)
	{
		if(a[i]<'0'||a[i]>'9')
		{
		    b++;
		}
	}
	if((a[0]=='1')&&((a[1]=='3')||(a[1]=='4')||(a[1]=='5')||(a[1]=='7')||(a[1]=='8'))&&(b=0))
	{
	
	printf("The number is:\n");
	for(i=0;i<=10;i++){
	
	printf("%c",a[i]);}
	printf("\n");
	printf("The number is right");
	}
	else
	{
		printf("The number is wrong");
	 } 
	
	
	return 0;
	
}
