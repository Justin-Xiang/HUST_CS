#include<stdio.h>
#include<math.h>
#define s(a,b,c) ((a)+(b)+(c))/2
#define area(s,a,b,c) sqrt((s)*((s)-(a))*((s)-(b))*((s)-(c)))
int main(void)
{
	double a,b,c,area;
	printf("���������������߳�\n");
	scanf("%lf%lf%lf",&a,&b,&c);
	printf("���������Ϊ%lf",area(s(a,b,c),a,b,c));
	return 0;
}
