#include<stdio.h>
int main(void)
{
	int x,n,i,j,m,s,a[10],flag;
	printf("������������x��\n");
	scanf("%d",&x);
	for(n=1234;n<98765;n++)
	{
		flag=0;
		m=n;                      //��ֹ������ 
		for(i=4;i>=0;i--)
		{
			a[i]=m%10;           //���������� 
			m=m/10;
		}
		if(n%x!=0)
		{
			continue;
		}
		else                     //������������� 
		{
			s=n/x;
			for(i=9;i>=5;i--)
			{
				a[i]=s%10;
				s=s/10;
			}
		}
	 
	for(i=0;i<=8;i++)             //�鿴�Ƿ����ظ������� 
	{
		for(j=i+1;j<=9;j++)
		{
			if(a[i]==a[j])
			{
				flag=1;
			}
			
		}
		
	 }
	if(flag==0)                       //���ظ��������� 
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
