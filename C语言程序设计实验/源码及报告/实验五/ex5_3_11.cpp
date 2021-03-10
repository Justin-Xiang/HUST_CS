#include<stdio.h>
void visited(int (*pa)[12], int i, int j)
{
	int n, m;
	pa[i][j] = 1;
	if(i == 6 && j == 10){
		printf("find path: \n");
		for(n=0; n<8; n++){
			for(m=0; m<12; m++){
				if(pa[n][m] == 1)
					printf("* ");
				else if(pa[n][m] == 2)
					printf("2 ");
				else 
					printf("0 ");
			}
			printf("\n");	
		}
	}
 
	if(pa[i-1][j] == 0)
		visited(pa, i-1, j);
	if(pa[i+1][j] == 0)
		visited(pa, i+1, j);
	if(pa[i][j-1] == 0)
		visited(pa, i, j-1);
	if(pa[i][j+1] == 0)
		visited(pa, i, j+1);
 
	pa[i][j] = 0;
}
int main()
{
	int a[8][12] = {
		2,2,2,2,2,2,2,2,2,2,2,2,
		2,0,2,2,2,2,2,2,2,2,2,2,
		2,0,2,0,0,2,0,0,0,0,2,2,
		2,0,0,0,2,2,0,0,2,0,2,2,
		2,0,2,2,0,0,0,2,2,0,2,2,
		2,0,0,0,0,2,0,0,0,0,2,2,
		2,2,2,2,2,2,2,2,2,0,0,2,
		2,2,2,2,2,2,2,2,2,2,2,2, 
		};
 
	visited(a, 1, 1);
 
	return 0;
}

