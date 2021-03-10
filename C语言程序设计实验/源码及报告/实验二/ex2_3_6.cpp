#include<stdio.h>
int main(void)
{
	unsigned long IP;
	unsigned short first,second,third,fourth;
	printf("Please enter the IP in unsigned long int form:\n");
	scanf("%lu",&IP);
	first=(IP&0xFF000000)>>24;
	second=(IP&0xFF0000)>>16;
	third=(IP&0xFF00)>>8;
	fourth=IP&0xFF;
	printf("%hu.%hu.%hu.%hu",fourth,third,second,first);
	return 0;
}
