#include<stdio.h>
#include<math.h>
#define s(a,b,c) ((a)+(b)+(c))/2
#define area(s,a,b,c) sqrt((s)*((s)-(a))*((s)-(b))*((s)-(c)))
int main(void)
{
	double a,b,c,area;
	printf("请输入三角形三边长\n");
	scanf("%lf%lf%lf",&a,&b,&c);
	printf("三角形面积为%lf",area(s(a,b,c),a,b,c));
	return 0;
}
