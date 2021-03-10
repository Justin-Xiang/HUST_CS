#include<stdio.h>
int main()
{
	int n, m, i, j;
	printf("请输入行数列数\n");
	scanf("%d %d",&n, &m);
	
	int a[n][m], b[n][m];
	
    printf("请从左到右，从上到下，依次输入颜色编号\n");
	for(i=0; i<n; i++)
	for(j=0; j<m; j++)
	scanf("%d", &a[i][j]);
	
	for(i=0; i<n; i++)
	for(j=0; j<m; j++)
	b[i][j] = 0;
	
	for(i=0; i<n; i++)
	for(j=0; j<m; j++)
	if((a[i][j]==a[i][j+1]&&a[i][j]==a[i][j+2])||(a[i][j]==a[i][j+1]&&a[i][j]==a[i][j-1])||(a[i][j]==a[i][j-1]&&a[i][j]==a[i][j-2]))
	b[i][j] = 1;
	
	
	for(j=0; j<m; j++)
	for(i=0; i<n; i++)
	if((a[i][j]==a[i+1][j]&&a[i][j]==a[i+2][j])||(a[i+1][j]==a[i][j]&&a[i][j]==a[i-1][j])||(a[i][j]==a[i-1][j]&&a[i][j]==a[i-2][j]))
	b[i][j] = 1;
	
	for(j=0; j<m; j++)
	for(i=0; i<n; i++)
	if(b[i][j])
	a[i][j] = 0;
	
	printf("消除后的棋盘为\n"); 
	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
		printf("%d ",a[i][j]);
		printf("\n");
	}
	
	return 0;
}

