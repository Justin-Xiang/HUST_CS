#include<stdio.h>
#include<math.h>
int main(void)
{
	int n,a,b,c,d;
	for(n=1000;n<10000;n++)                /*范围确定*/
	{
		d=n%10;                            /*个位数*/
		c=(n/10)%10;                        /*十位*/ 
		b=(n/100)%10;                        /*百位*/
		a=(n/1000)%10;                      /*千位*/
		if((sqrt(n)==int(sqrt(n)))&&(a==b)&&(c==d)&&(a!=c))
		{                                     /*通过条件筛选*/
			printf("%d",n);
		}
	}
	return 0;
}

