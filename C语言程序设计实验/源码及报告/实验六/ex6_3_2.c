#include<stdio.h>
#include<string.h>
int RemoveSame(int a,int n);
int main(void)
{
	int n,i;
	printf("�����������е�Ԫ�ظ�����\n");
	scanf("%d",&n);
	printf("�밴����������Ԫ��\n");
	int a[n];
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	RemoveSame(a,n);
	for(i=0;i<n;i++)
	{
		printf("%d",a[i]);
	}
	
}

int RemoveSame(int a,int n)
{
	int *p,*q;
	for(p=a;p<a+n;p++)
	{
		for(q=p+1;q<a+n;q++)
		{
			if(p==q)
			{
				n--;
			}
		}
	}
	printf("%d",n);
}
