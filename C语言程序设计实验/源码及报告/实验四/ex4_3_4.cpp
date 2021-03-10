#include<stdio.h>
#define CHANGE 1
int main(void)
{
	char c;
	printf("请输入一行英文字符，我会进行相应转换\n");
	while((c=getchar())!=EOF)
	{
	#if CHANGE == 1
	   if(c>='A'&&c<='Z')
	   putchar(c+32);
	   else if(c>='a'&&c<='z')
	   putchar(c-32);
	   else
	   putchar(c);
	#else
	   putchar(c);
	#endif
}
return 0;
}
