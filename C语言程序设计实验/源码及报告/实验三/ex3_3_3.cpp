#include<stdio.h> 
int main(void)
{ 
	char c;
	int total = 0;  //���ڱ�������ո�ĸ���,����1���ı��Ϊ1,������Ϊ0
	printf ("Please input a char:\n");
	do
	{
		c = getchar();
		if (c == ' ')
		{
			if (!total)  //�����ǰ���Ϊ0
			{
				printf ("%c", c);  //���һ���ո�
				total = 1;  //�������Ϊ1
			}
			else
				continue;  //������������Ŀո�������
		}
		else
		{
			printf ("%c", c);  //�����ַ�ԭ�����
			total = 0;  //���±�ǿո�
		}
	}while (c != '\n');
	
	return 0;
}
