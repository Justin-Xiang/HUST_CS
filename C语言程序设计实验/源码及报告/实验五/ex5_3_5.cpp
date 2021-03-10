#include<stdio.h>
void strnins(char t[],char s[],int n);
int main(void)
{
	char t[15]="C programmar";
	char s[30]="language learner";
	strnins(t,s,5);
	puts(t);
	return 0;
}

void strnins(char t[],char s[],int n)
{
	int i=0,j=0,a;
	while(s[i++]);
	while(t[j++]);
	for(a=j;a>=n;a--)
	{
		t[a+i-1]=t[a];
	}
	j=0;
	while(j<i-1)
	{
		t[j+n]=s[j];
		j++;
	}
}
