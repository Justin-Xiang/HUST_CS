#include<stdio.h>
void select(long int);
int main(void)
{
	long int a;
	printf("Input a long integer:\n");
	scanf("%ld",&a);
	select(a);
	return 0;
}

void select(long int a)
{
	char low,high;
	unsigned char *p=(unsigned char*)&a;
	p=p+3;
	int i;
	for(i=0;i<4;i++)
	{
		low=(*p)&0x0f;
		high=(*p>>4)&0x0f;
		printf("%x %x\n",high,low);
		p--;
	}
}
