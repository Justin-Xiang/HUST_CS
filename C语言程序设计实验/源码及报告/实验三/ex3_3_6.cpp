#include<stdio.h>
#include<math.h>

double pass=0,count=0;//pass����������count4�غ��ܿ���

void f(double Ta,double Tb,int n){
	if(n==4){
		if(fabs(Ta-Tb)<1000) 
		{
		    pass++;}
		count++;
		return;
	}
	double a,b;
	a=Ta-Ta*0.25;b=Tb+Ta*0.25;//a��
	f(a,b,n+1);
	a=Ta+Tb*0.25;b=Tb-Tb*0.25;//aʤ
	f(a,b,n+1);
}

int main(void)
{
	f(1000,2000,0);
	printf("%f",(pass/count)*100);
}
