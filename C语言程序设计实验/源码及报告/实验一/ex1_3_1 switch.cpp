#include<stdio.h>
int main(void)
{
	int x;
	printf("Please enter your salary:\n");   /*输入工资*/ 
	scanf("%d",&x);                        
	printf("Your tax is:");
	switch((x/1000))          /*根据工资数额大小做出判断*/
	{
		case 0: printf("0");break;
		case 1: printf("%.2f",x*0.05);break;
		case 2: printf("%.2f",x*0.1);break;
		case 3: printf("%.2f",x*0.15);break;
		case 4: printf("%.2f",x*0.2);break;
		default: printf("%.2f",x*0.25);break;
	}
	return 0;
}
