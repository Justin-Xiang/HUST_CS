#include <stdio.h>
#define IN 1
#define OUT 0
int main()
{
    char c;
    int char_num,word_num,line_num,state;
    char_num=word_num=line_num=0;
    state=OUT;
    printf("����������(��Ctrl+Z��β)��\n"); 
    while((c=getchar())!=EOF)
	{
        
        char_num++;
        if(c=='\n')
		{       
            line_num++;
        }
        if(c=='\n' || c=='\t' || c==' ')
		{
            
                state=OUT;
        }
		else if(state==OUT)
		{
        
            state=IN;
            word_num++;
        }
        }
 
 
    printf("����=%d\n����=%d\n�ַ���=%d\n",line_num,word_num,char_num);
    return 0;
}

