#include<stdio.h>
#define SIZE sizeof(int)
int main(void)
{
	int x;
	char a[SIZE*8+1];
	int i;
	scanf("%d",&x);
	for(i=0;i<SIZE*8+1;i++,x<<=1)
	{
		if(x&1<<(SIZE*8-1))
		   a[i]='1';
		else
		   a[i]='0';
	}
	a[SIZE*8]='\0';
	printf("%s",a);
	return 0;
 } 
