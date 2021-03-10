#include<stdio.h>
int main(void)
{
	int x,n,i,j,m,s,a[10],flag;
	printf("请输入正整数x：\n");
	scanf("%d",&x);
	for(n=1234;n<98765;n++)
	{
		flag=0;
		m=n;                      //防止被更改 
		for(i=4;i>=0;i--)
		{
			a[i]=m%10;           //存入数组中 
			m=m/10;
		}
		if(n%x!=0)
		{
			continue;
		}
		else                     //整除则继续存入 
		{
			s=n/x;
			for(i=9;i>=5;i--)
			{
				a[i]=s%10;
				s=s/10;
			}
		}
	 
	for(i=0;i<=8;i++)             //查看是否有重复的数字 
	{
		for(j=i+1;j<=9;j++)
		{
			if(a[i]==a[j])
			{
				flag=1;
			}
			
		}
		
	 }
	if(flag==0)                       //无重复则可以输出 
	{
		for(i=0;i<=4;i++)
		{
			printf("%d",a[i]);
		}
		printf("/");
		for(i=5;i<=9;i++)
		{
			printf("%d",a[i]);
		}
		printf("=%d\n",x);
		
	 }
}
	return 0; 
}
