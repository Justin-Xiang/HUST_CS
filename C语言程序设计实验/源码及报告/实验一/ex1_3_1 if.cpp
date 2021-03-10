#include<stdio.h>
int main(void)
{
	int x;
	printf("Please enter your salary:\n");   /*输入工资*/ 
	scanf("%d",&x);                        
	printf("Your tax is:");                 
	if(x/1000==0) printf("0");               /*根据工资数额大小做出判断*/  
	else if(x/1000==1) printf("%.2f",x*0.05);  
	else if(x/1000==2) printf("%.2f",x*0.1);
	else if(x/1000==3) printf("%.2f",x*0.15);
	else if(x/1000==4) printf("%.2f",x*0.2);
	else if(x/1000>4) printf("%.2f",x*0.25);
	return 0;
}


