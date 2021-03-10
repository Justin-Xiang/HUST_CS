#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void mul(char *a,char *b,char *c)
{
	int i;
	int j;
	int ca;
	int cb;
	int *s;
	ca=strlen(a);
	cb=strlen(b);
	
	if(strcmp(a,"0")==0||strcmp(b,"0")==0)
	{
		strcpy(c,"0");
		return;
	}
	s=(int*)malloc(sizeof(int)*(ca+cb));
	
	for(i=0;i<ca+cb;i++)
	    s[i]=0;
	for(i=0;i<ca;i++)
	    for(j=0;j<cb;j++)
	        s[i+j+1]+=(a[i]-'0')*(b[i]-'0');
	
	for(i=ca+cb-1;i>=0;i--)
	    if(s[i]>=10)
	    {
	    	s[i-1]+=s[i]/10;
	    	s[i]%=10;
		}
	
	i=0;
	while(s[i]==0)
	    i++;
	for(j=0;i<ca+cb;j++,i++)
	{
		c[j]=s[i]+'0';
	}
	c[j]='\0';
	free(s);
}

int main(void)
{
	char str1[200];
	char str2[200];
	char str3[40000];
	
	printf("请输入第一个数：\n");
	gets(str1);
	printf("请输入第二个数：\n");
	gets(str2);
	
	mul(str1,str2,str3);
	
	int i;
	for(i=0;i<strlen(str3);i++)
	{
		printf("%c",str3[i]);
	}
	return 0;
}
