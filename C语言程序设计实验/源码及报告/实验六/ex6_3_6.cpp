#include<stdio.h>
#include<string.h>
void down_sort(int *,int );
void up_sort(int *,int);
int main(int argc,char *argv[])
{
	int n,i;
	void(*p)(int *,int);
	printf("请输入整数的个数\n");
	scanf("%d",&n);
	int a[n];
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	if(argc>1&&!strcmp(argv[1],"-d"))
	    p=down_sort;
	else
	    p=up_sort;
	p(a,n);
	printf("排序后:\n");
	for(i=0;i<n;i++)
	{
		printf("%d ",a[i]);
	}
	return 0;
}

void down_sort(int *a,int m)
{
	int i,j,k;
    for(i=0;i<m-1;i++)
    {
        for(j=i;j<m;j++)
        {
            if(*(a+i)<*(a+j))
            {
                k=*(a+i);
                *(a+i)=*(a+j);
                *(a+j)=k;
            }
        }
    }
}

void up_sort(int *a,int m)
{
	int i,j,t;
	for(i=0;i<m-1;i++)
	{
		for(j=0;j<m-1-i;j++)
		{
			if(*(a+j)>*(a+j+1))
			{
				t=*(a+j);
				*(a+j)=*(a+j+1);
				*(a+j+1)=t;
			}
		}
	}
}
