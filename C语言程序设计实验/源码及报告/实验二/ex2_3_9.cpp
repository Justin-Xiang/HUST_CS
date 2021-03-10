#include<stdio.h>
#include<string.h>
int main(void)
{
	int flag=1;
	unsigned long ip=0;
	char c;
	unsigned long a[4]={0};
	int k;
	int i=0;
	printf("Please enter the IP(End of CtrlZ):\n");
    while((c=getchar())!=EOF)
    {
    	if(c=='\n')
    	{
    		continue;
		}
		if(c>='0'&&c<='9')
		{
			a[i]=a[i]*10+c-'0';
		}
		else if(c=='.')
		{
			++i;
		}
		else
		{
			printf("NO");
			flag=0;
			break;
		}
		if(a[i]>255||i>3)
		{
			printf("NO");
			flag=0;
			break;
		}
	}
	if(flag)
	{
	printf("YES");
	
    for(k=0;k<4;++k)//将四段地址合并为一个长整数
    {
    a[k] <<= 8*(3-k);
    ip |=a[k];
    }
    printf("\nip is:%lu",ip);}
	
}
