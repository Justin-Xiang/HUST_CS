#include <stdio.h>
#define IN 1
#define OUT 0
int main()
{
    char c;
    int char_num,word_num,line_num,state;
    char_num=word_num=line_num=0;
    state=OUT;
    printf("请输入正文(以Ctrl+Z结尾)：\n"); 
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
 
 
    printf("行数=%d\n字数=%d\n字符数=%d\n",line_num,word_num,char_num);
    return 0;
}

