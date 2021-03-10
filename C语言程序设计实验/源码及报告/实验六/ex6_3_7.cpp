#include<stdio.h>
#include<string.h>

#define SIZE 51

int num;
int length;
char finally[SIZE];

int InputNum();
void InputChar();

int main(void){
	printf("Input the number of the element(s).\n");
	
	while(InputNum()==0){
		printf("Illegal input.Should be not less than 1.\n");
	}
	
	printf("Input the elements.\n");
	InputChar();
	printf("Here is the longest string:\n%s\n",finally);
	printf("The length of it is %d.\n",length);
	
	return 0;
}

void InputChar(){
	char buffer[SIZE*2];
	gets(buffer);
	int temp,ele;
	
	strcpy(finally,buffer);
	
	for(ele=1;ele<num;ele++){
		temp=strlen(buffer)+1;
		gets(buffer+temp);
		if(strlen(finally)<strlen(buffer+temp)) strcpy(finally,(buffer+temp));
		ele++;
		if(ele>=num) break;
		
		gets(buffer);
		if(strlen(finally)<strlen(buffer)) strcpy(finally,buffer);
	}
	
	length=strlen(finally);
}

int InputNum(){
	scanf("%d",&num);
	getchar();
	if(num<1) return 0;
	return 1;
}
