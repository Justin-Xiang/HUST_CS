#include<stdio.h>
#include<math.h>
int main(void)
{
	int n,a,b,c,d;
	for(n=1000;n<10000;n++)                /*��Χȷ��*/
	{
		d=n%10;                            /*��λ��*/
		c=(n/10)%10;                        /*ʮλ*/ 
		b=(n/100)%10;                        /*��λ*/
		a=(n/1000)%10;                      /*ǧλ*/
		if((sqrt(n)==int(sqrt(n)))&&(a==b)&&(c==d)&&(a!=c))
		{                                     /*ͨ������ɸѡ*/
			printf("%d",n);
		}
	}
	return 0;
}

