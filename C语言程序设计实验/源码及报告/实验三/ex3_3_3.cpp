#include<stdio.h> 
int main(void)
{ 
	char c;
	int total = 0;  //用于标记连续空格的个数,大于1个的标记为1,否则标记为0
	printf ("Please input a char:\n");
	do
	{
		c = getchar();
		if (c == ' ')
		{
			if (!total)  //如果当前标记为0
			{
				printf ("%c", c);  //输出一个空格
				total = 1;  //将标记置为1
			}
			else
				continue;  //如果出现连续的空格则跳过
		}
		else
		{
			printf ("%c", c);  //其他字符原样输出
			total = 0;  //重新标记空格
		}
	}while (c != '\n');
	
	return 0;
}
