#include<stdio.h>
int main(void)
{
	int n,i,x;
	printf("Please enter a num:\n");
	scanf("%d",&n);
	x=0;
	i=0;
	
	while(n)
	{
		i++;
		x+=n%10;
		n/=10;
	}
	printf("%dλ������λ����֮��Ϊ%d",i,x);
	return 0;
	
	
}
