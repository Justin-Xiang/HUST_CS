#include <stdio.h>
int mark[256];
int n;
void DFS(int sum, int k, int prio) {
	
	if(sum > n) 
	{
		return;
	} 
	else if(sum == n) 
	{
		int i;
		printf("=");
		for( i = 0; i < k-1; i++) 
		{
			printf("%d+",mark[i]);
		}
		printf("%d\n",mark[i]);
	} 
	else
	{
		for(int j = prio; j > 0; j--) 
		{
			mark[k] = j;
			sum += j;
			DFS(sum,k+1,j);
			sum -= j;  
		}
	}
}
int main(void) 
{
	printf("请输入你要划分的整数（1~10）\n");
	scanf("%d", &n);
	DFS(0, 0, n);
	return 0;
}
