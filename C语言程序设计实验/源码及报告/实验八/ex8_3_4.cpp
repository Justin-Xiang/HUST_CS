#include<stdio.h>
int main(void)
{
	FILE *fp; 
	int m,n,i,j,k,t;
	printf("����������������\n");
	scanf("%d%d",&m,&n);
	printf("���������:\n");
	fp=fopen("matrix.in","w");
	int a[m][n];
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	fprintf(fp,"ԭ����(%d��%d��):\n",m,n);
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			fprintf(fp,"%d",a[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	fp=fopen("matrix.out","w");
	fprintf(fp,"��ת90�Ⱥ�Ϊ(%d��%d��):\n",n,m);
	for(i=0,t=0;i<n;i++)
	{
		k=m-1;
		for(j=0;j<m;j++)
		{
			fprintf(fp,"%d ",a[k][t]);
			k=k-1;
		}
		fprintf(fp,"\n");
		t=t+1;
	}
}
