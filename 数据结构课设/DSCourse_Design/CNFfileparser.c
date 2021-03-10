//
// Created by JustinXiang on 2021/2/26.
//

#include "define.h"

/*单个结点初始化函数*/

/*新建子句*/
struct Clause * createClause(){
    struct Clause * new_clause = malloc(sizeof(struct Clause));
    new_clause->head = NULL;
    new_clause->next = NULL;
    return new_clause;
}

/*新建文字*/
struct Literal * createLiteral()
{
    struct Literal * new_literal = malloc(sizeof(struct Literal));
    new_literal->next = NULL;
    new_literal->value = 0;
    return new_literal;
}

/*cnf文件读取*/
struct Clause * Readfile(char * filename){
    int length = strlen(filename);
    //printf("%d",length);
    if(filename[length-3]!='c' && filename[length-2]!='n' && filename[length-1]!='f')
    {
        printf("文件格式不正确\n");
        exit(1);
    }
    FILE * fp;
    fp = fopen(filename,"r");
    if(fp == NULL){
        printf("文件打开失败!\n");
        exit(1);
    }
    char s[100];
    char *c;
    struct Clause * root = NULL, * current_Clause = NULL, * pre_Clause = NULL;
    struct Literal * current_Literal = NULL, * pre_Literal = NULL;

    while(fgets(s, 100, fp)){//按行读取
        if(s[0] == 'c') continue;
        else if(s[0] == 'p'){
            sscanf(s, "p cnf %d %d", &word_number, &formula_number);//按格式读入文字数与公式数
            printf("文字数: %d	公式数: %d\n", word_number, formula_number);
            variable = (int *)calloc(word_number + 1, sizeof(int));
            for(i = 1; i <= word_number; i++) variable[i] = -1;//初始化标记数组，-1表示未被确定真值

        }
        else{
            //构建存储结构
            current_Clause = createClause();
            if(root == NULL) root = current_Clause;
            if(pre_Clause != NULL)  pre_Clause->next = current_Clause;
            c = strtok(s, (const char *) " ");//分割字符串
            while(c != NULL){
                current_Literal = createLiteral();
                temp = atoi(c);
                current_Literal->value = temp;
                if(temp != 0){
                    nums[abs(temp)-1] +=1;
                    if(current_Clause->head == NULL) current_Clause->head = current_Literal;
                    if(pre_Literal != NULL) pre_Literal->next = current_Literal;

                }
                pre_Literal = current_Literal;
                c = strtok(NULL, (const char *) " ");
            }
            pre_Clause = current_Clause;
        }
    }
    fclose(fp);
    return root;
}




/*遍历输出CNF文件格式*/
void Traversefile(struct Clause * root)
{
    struct Clause * T = root;
    while(T!=NULL){
        struct Literal * current_Literal = T->head;
        printf("公式: ");
        while(current_Literal != NULL)
        {
            printf("%d ",current_Literal->value);
            current_Literal = current_Literal->next;
        }
        if(T->next!=NULL) printf("\n");
        T = T->next;
    }
    printf("文件输出成功!\n");
}

/*文件保存成功*/
status Savefile(struct Clause * root)
{
    FILE * fp;
    char filename[20];
    struct Clause * T = root;
    printf("请输入文件名：\n");
    scanf("%s",filename);
    if((fp = fopen(filename,"wb"))==NULL){
        printf("文件打开失败！\n");
        return ERROR;
    }
    else{
        fprintf(fp,"%s ","p cnf");
        fprintf(fp,"%d ",word_number);
        fprintf(fp,"%d\n",formula_number);
        while(T){
            struct Literal * current_Literal = T->head;
            while(current_Literal){
                fprintf(fp,"%d ",current_Literal->value);
                current_Literal = current_Literal->next;
            }
            if(T->next!=NULL) fprintf(fp,"0\n");
            T = T->next;
        }
        fprintf(fp,"0");
    }
    fclose(fp);
    return OK;
}


