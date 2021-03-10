#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct stu_grade
{
    char id[10] ;
    char name[10] ;
    float English ;
    float math ;
    float physics ;
    float C_language;
    float average ;
    struct stu_grade *next ;
}stu_grade;
void Input(stu_grade **p); 
void Output(stu_grade *p);       
void Change(stu_grade *p);               
void Averae(stu_grade *p);               
void Outputpart(stu_grade *p);          
void sort(stu_grade *p);            
void save(stu_grade *p);            
void FileOutput(stu_grade **p);             
void swapstr(char *a,char *b);      
void swapnum(float *a,float *b);   
int main(void)
{
    int i;
    stu_grade *p;
    while(1){
        printf("1.Input the information\n2.Output the information\n3.change the particular data\n4.calculate the average\n5.Output the details\n6.save\n7.open the file\n8.exit\n");
        printf("Please input a number:");
        scanf("%d",&i);
        switch(i){
            case 1: Input(&p);break;
            case 2: Output(p);break;
            case 3: Change(p);break;
            case 4: Averae(p);break;
            case 5: Outputpart(p);break;
            case 6: save(p);break;
            case 7: FileOutput(&p);break;
            case 8: return 0;
            default : continue;
        }
    }
}
void Input(stu_grade **p)
{
    stu_grade *hd,*tail,*temp;
    hd = (stu_grade *)malloc(sizeof(stu_grade));
    printf("please input the details of a student,end of Ctrl+Z: \n");
    tail = hd ;
    while((scanf("%s%s%f%f%f%f",tail->id,tail->name,&tail->English,&tail->math,&tail->physics,&tail->C_language))==6){
        tail -> next = (stu_grade *)malloc(sizeof(stu_grade));
        temp = tail;
        tail = tail -> next;
    }
    temp->next = NULL;
    *p=hd;
    putchar('\n');
}
void Output(stu_grade *p)
{
    stu_grade *p_itr = p;
    printf("number\tname\tEnglish\tmath\tPhysics\tC programmar language\n");
    while(p_itr){
        printf("%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",p_itr->id,p_itr->name,p_itr->English,p_itr->math,p_itr->physics,p_itr->C_language);
        p_itr = p_itr -> next;
    }
    putchar('\n');
}
void Change(stu_grade *p)
{
    char stutochange[10];
    printf("Input the number or name£º");
    scanf("%s",stutochange);
    stu_grade *ptr=p;
    while(1){
        if((strcmp(ptr -> name,stutochange)==0)||(strcmp(ptr -> id,stutochange)==0)){
            printf("Please reinput");
            scanf("%f%f%f%f",&ptr->English,&ptr->math,&ptr->physics,&ptr->C_language);
            return;
        }
        else{
            ptr = ptr -> next;
        }
    }
    putchar('\n');
}
void Averae(stu_grade *p)
{
    stu_grade *ptr=p;
    while (ptr)
    {
        float a;
        a=(ptr->C_language + ptr->math + ptr->English + ptr->physics)/4.0;
        ptr->average=((float)((int)((a+0.005)*100)))/100;
        ptr = ptr -> next;
    }
    putchar('\n');
}
void Outputpart(stu_grade *p)
{
    stu_grade *ptr=p;
    sort(ptr);
    printf("number\tname\ttotal\taverage\n");
    while (ptr)
    {
        printf("%s\t%s\t%.2f\t%.2f\n",ptr->id,ptr->name,(ptr->C_language + ptr->math + ptr->physics + ptr->English),ptr->average);
        ptr=ptr->next;
    }
    putchar('\n');
    
}
void sort(stu_grade *p)
{
    stu_grade *ptr1=p,*ptr2=p;
    int len=0,i,j,t;
    while(ptr1){
        len++;
        ptr1=ptr1->next;
    }
    for ( i=0, ptr1=p ; i<len-1 ; i++, ptr1 = ptr1->next){
        for( j=0, ptr2=p ; j<len-i-1 ; j++ ,ptr2 = ptr2->next){
            if(ptr2->average > ptr2->next->average){
                swapstr(ptr2->id,ptr2->next->id);
                swapstr(ptr2->name,ptr2->next->name);
                swapnum(&ptr2->English,&ptr2->next->English);
                swapnum(&ptr2->math,&ptr2->next->math);
                swapnum(&ptr2->physics,&ptr2->next->physics);
                swapnum(&ptr2->C_language,&ptr2->next->C_language);
                swapnum(&ptr2->average,&ptr2->next->average);
            }
        }
    }
}
void swapstr(char *a,char *b)
{
    char p[15];
    strcpy(p,a);
    strcpy(a,b);
    strcpy(b,p);
}
void swapnum(float *a,float *b)
{
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void save(stu_grade *p)
{
    stu_grade *ptr=p;
    FILE *fp;
    fp=fopen("D:\\stu.dat","wb+");
    while(ptr){
        fprintf(fp,"%s ",ptr->id);
        fprintf(fp,"%s ",ptr->name);
        fprintf(fp,"%.2f ",ptr->English);
        fprintf(fp,"%.2f ",ptr->math);
        fprintf(fp,"%.2f ",ptr->physics);
        fprintf(fp,"%.2f\n",ptr->C_language);
        ptr=ptr->next;
    }
    fclose(fp);
}
void FileOutput(stu_grade **p)
{
    FILE *fp;
    fp=fopen("D:\\stu.dat","rb");
    stu_grade *hd,*tail,*temp;
    hd = (stu_grade *)malloc(sizeof(stu_grade));
    tail=hd;
    while(fscanf(fp,"%s%s%f%f%f%f",tail->id,tail->name,&tail->English,&tail->math,&tail->physics,&tail->C_language)==6){
        tail->next=(stu_grade *)malloc(sizeof(stu_grade));
        temp=tail;
        tail=tail->next;
    }
    fclose(fp);
    temp->next=NULL;
    *p=hd;
    Output(*p);
}
