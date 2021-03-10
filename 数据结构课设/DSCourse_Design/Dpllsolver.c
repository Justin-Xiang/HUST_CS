//
// Created by JustinXiang on 2021/2/27.
//

#include "define.h"


/*判断单子句，返回单子句里的文字*/
int isUnitClause(struct Clause * root)
{
    struct Clause * T = root;
    while(T!=NULL){
        if(T->head == NULL) continue;
        if(T->head->next==NULL) return T->head->value;
        T = T->next;
    }
    return 0;
}

/*处理单子句*/
status removeClause(struct Clause * root){
    temp = isUnitClause(root);
    if(temp==0) return ERROR; //表示没有单子句
    variable[abs(temp)] = temp >0?1:0;
    struct Clause * T = root,*pre_T = createClause();
    while(T!=NULL){
        struct Literal * current_Literal = T->head, * pre_Literal = createLiteral();
        while(current_Literal!=NULL){
            if(current_Literal->value == temp){
                //删除包含该文字的子句
                if(T==root){
                    *(root) = *(root->next);
                    T = NULL;
                }
                else{
                    pre_T->next = T->next;
                    T = pre_T;
                }
                break;
            }
            else if (current_Literal->value == -temp){   //删除互为相反数的文字
                if(current_Literal == T->head) T->head = current_Literal->next;
                else pre_Literal->next = current_Literal->next;
                current_Literal = pre_Literal;
                continue;
            }
            pre_Literal = current_Literal;
            current_Literal = current_Literal->next;

        }
        pre_T = T;
        T = (T==NULL) ?root :T->next;
    }
    return OK;
}


/*判断正负*/
int judgesign(int a){
    return a>0?1:-1;
}

/*判断只有一种出现形式的文字，返回文字的值*/
int isPureLiteral(struct Clause * root){
    int * mark = (int *)calloc(word_number+1,sizeof(int));  //标志数组，初始化0;
    struct Clause * T = root;
    while(T!=NULL){
        struct Literal * current_Literal = T->head;
        while(current_Literal != NULL){
            if(mark[abs(current_Literal->value)]!=2){
                temp = mark[abs(current_Literal->value)];
                if(temp==0) mark[abs(current_Literal->value)] = judgesign(current_Literal->value);
                else if(temp ==1 && judgesign(current_Literal->value) == -1) mark[abs(current_Literal->value)] = 2;
                else if(temp==-1 && judgesign(current_Literal->value) == 1) mark[abs(current_Literal->value)] = 2;
                //有两种存在形式标记为2
            }
            current_Literal = current_Literal->next;
        }
        T = T->next;
    }
    for(i=1;i<=word_number;i++){
        if(mark[i] == -1 || mark[i] == 1) return i*mark[i];
    }
    return 0;  //没有以一种形式出现的文字
}


/*处理只有一种出现形式的文字*/
status removePureLiteral(struct Clause * root)
{
    temp = isPureLiteral(root);
    if(temp == 0) return ERROR;
    variable[abs(temp)] = temp >0?1:0;
    struct Clause * T = root,* pre_T = createClause();
    while( T != NULL){
        struct Literal *current_Literal = T->head;
        while(current_Literal != NULL){
            if(current_Literal->value == temp){
                if(T == root){
                    * root = *(root->next);
                    T = NULL;
                }
                else{
                    pre_T ->next = T->next;
                    T = pre_T;
                }
                break;
            }
            current_Literal = current_Literal->next;
        }
        pre_T = T;
        T = (T == NULL) ?root:T->next;
    }
    return OK;
}



/*选取假设真值文字*/
int chooseLiteral(struct Clause * root)
{
    if(Way == 1)
    {
        return root->head->value;
    }
    else
    {
        int x,max = 0;
        struct Literal * l = root->head;
        struct Clause * c = root;
        while(c->head == NULL)
        {
            c = c->next;
        }
        l = c ->head;
        while(l)
        {
            if(nums[abs(l->value)-1]>max)
            {
                max = nums[abs(l->value)-1];
                x = abs(l->value);
            }
            l = l->next;
        }
        return x;

    }
}

/*克隆子句*/
struct Clause * cloneClause(struct Clause * re_clause)
{
    struct Clause *  clone_Clause = createClause();
    struct Literal * current_Literal = re_clause->head, * pre_Literal = NULL;
    while(current_Literal != NULL){
        struct Literal * clone_Literal = createLiteral();
        clone_Literal->value = current_Literal->value;
        if(clone_Clause->head == NULL) clone_Clause->head = clone_Literal;
        if(pre_Literal != NULL) pre_Literal->next = clone_Literal;
        pre_Literal = clone_Literal;
        current_Literal = current_Literal->next;
    }
    return clone_Clause;
}


/*克隆全部结构并将选取的文字设为单子句加入存储结构中*/
struct Clause * cloneAll(int a, struct Clause * root)
{
    variable[abs(a)] = a >0?1:0;
    struct Clause * T = root, * new_root = NULL, *pre_Clause = NULL;
    while(T != NULL){
        struct Clause * current_Clause = cloneClause(T);
        if(new_root == NULL) new_root = current_Clause;
        if(pre_Clause != NULL) pre_Clause->next = current_Clause;
        pre_Clause = current_Clause;
        T = T->next;
    }
    struct Clause * new_Clause = createClause();
    struct Literal * new_Literal = createLiteral();
    new_Literal->value = a;
    new_Clause->head = new_Literal;
    new_Clause->next = new_root;
    return new_Clause;
}


/*销毁存储结构*/
void destroyClauses(struct Clause * root)
{
    while(root != NULL){
        struct Clause * next_r = root->next;
        if(root->head != NULL){
            struct Literal * current_Literal = root->head;
            while(current_Literal != NULL){
                struct Literal * next_Literal = current_Literal->next;
                free(current_Literal);
                current_Literal = next_Literal;
            }
        }
        free(root);
        root = next_r;
    }
}


/*判断文字是否均为单一形式出现*/
status isAllPureLiteral(struct Clause * root)
{
    int *mark = (int *)calloc(word_number+1,sizeof(int));
    struct Clause * T = root;
    while(T != NULL)
    {
        struct Literal * current_Literal = T->head;
        while(current_Literal != NULL){
            temp = mark[abs(current_Literal->value)];
            if(temp == 0) mark[abs(current_Literal->value)] = judgesign(current_Literal->value);
            else if(temp != judgesign(current_Literal->value))
            {
                free(mark);
                return ERROR;
            }
            current_Literal = current_Literal->next;
        }
        T = T->next;
    }
    T = root;
    while(T != NULL){
        struct Literal * current_Literal  = T->head;
        while(current_Literal != NULL){
            if(variable[abs(current_Literal->value)]==-1) variable[abs(current_Literal->value)] = current_Literal->value>0 ?1:0;
            current_Literal = current_Literal->next;
        }
        T = T->next;
    }
    return OK;
}


/*判断是否存在空子句*/
status isEmptyClause(struct Clause * root){
    struct Clause * T = root;
    while(T != NULL){
        if(T->head == NULL) return OK;
        T = T->next;
    }
    return ERROR;
}

/*检查当前是否满足*/
status check(struct Clause * root)
{
    if(isEmptyClause(root)) return ERROR; //表示不满足
    if(isAllPureLiteral(root)) return OK; //表示满足
    return Untrue;  //表示未确定
}

/*dpll算法*/
status dpll(struct Clause * root){
    temp = check(root);
    if(temp != Untrue){
        destroyClauses(root);
        return temp;
    }//不是未确定的情况，返回结果
    while(1){//处理单子句
        temp = check(root);
        if(temp != Untrue){
            destroyClauses(root);
            return temp;
        }//同上
        if(!removeClause(root)) break;//处理单子句，没有的话跳出循环
    }
    int new_count = chooseLiteral(root);//选取假设真值
    if(dpll(cloneAll(new_count, root)) == OK) return OK;
    else{
        temp = dpll(cloneAll(-new_count, root));//如果不成功，选取假设真值的相反数
        destroyClauses(root);
        return temp;
    }
}

/*将结果写入同名文件*/
void writeResult(char * filename, int flag, int time)
{
    int temp = 0;
    for(i=0;i<200;i++){
        if(filename[i] == '.')
        {
            filename[i+1] = 'r';
            filename[i+2] = 'e';
            filename[i+3] = 's';
            break;
        }
    }
    FILE * fp = fopen(filename,"w");
    if(fp == NULL)
    {
        printf("求解结果保存失败!\n");
        exit(1);
    }
    if(flag == 1)
    {
        fprintf(fp,"s 1\n");
        fprintf(fp,"v ");
        for(i=1; i<=word_number;i++)
        {
            temp = (variable[i]==0 ?-1:1) *i;
            fprintf(fp,"%d ",temp);
            if(i%10 == 0) fprintf(fp,"\n");
        }
        fprintf(fp,"\nt %f ms\n",time);
    }
    else
    {
        fprintf(fp,"s 0\n");
        fprintf(fp,"v \n");
        fprintf(fp,"t %f ms\n",time);
    }
    printf("求解结果保存成功!\n");
    fclose(fp);
}