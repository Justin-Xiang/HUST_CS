#include<stdio.h>
int main(void)
{
	char ch;
	ch=getchar();
	if(ch>='A'&&ch<='Z')
	{
		ch=ch+32;
		printf("%c",ch);
	}
	else
	{
		printf("%c",ch);
	}
	return 0;
 } 
