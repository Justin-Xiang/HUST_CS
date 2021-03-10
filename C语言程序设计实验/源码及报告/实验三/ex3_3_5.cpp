#include<stdio.h>
#include<math.h>
int main(void)
{
	int n,a,b,c,d;
	for(n=1000;n<10000;n++)
	{
		d=n%10;
		c=(n/10)%10;
		b=(n/100)%10;
		a=(n/1000)%10;
		if((sqrt(n)==int(sqrt(n)))&&(a==b)&&(c==d)&&(a!=c))
		{
			printf("%d",n);
		}
	}
	return 0;
}
