#include<stdio.h>
#include<string.h>
#define STRCPY(a,b) strcpy(a##_p,#b)
int main(void)
{
	char var1_p[20];
	char var2_p[30];
	strcpy(var1_p,"aaaa");
	strcpy(var2_p,"bbbb");
	STRCPY(var1,var2);
	STRCPY(var2,var1);
	printf("var1=%s\n",var1_p);
	printf("var2=%s\n",var2_p);
	return 0;
 } 
