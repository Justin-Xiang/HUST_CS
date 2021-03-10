#include<stdio.h>
#include<string.h>
#define STU struct student

STU{
    int gra;
    char na[20];
};

void input(STU *p,int n) {
    printf("Input names and grades:\n");
    
    int te;
    for(te=1; te<=n; te++) {
        scanf("%s",&((*p).na));
        scanf("%d",&((*p).gra));
        p++;
    }
}

void sort(STU *p,int n) {
    if(n<=1)
        return;

    int l,r;
    l=0;
    r=n-1;
    STU head=*p;

    while(l!=r) {
        while((*(p+r)).gra<=(*(p+l)).gra&&l!=r)
            r--;
        *(p+l)=*(p+r);
        while((*(p+r)).gra<=(*(p+l)).gra&&l!=r)
            l++;
        *(p+r)=*(p+l);
    }

    *(p+l)=head;
    if(!l)
    sort(p,l);
    if(r!=n-1)
    sort(p+r+1,n-l-1);
}

void output(STU *p,int n) {
	int tem;
    for(tem=1; tem<=n; tem++) {
        printf("%s\t%d\n",p->na,p->gra);
        p++;
    }
}

void search(STU *p,int n,int grade){
	int tem;
	int judge=1;
	for(tem=0;tem<n;tem++){
		if((*(p+tem)).gra==grade){
			printf("%s\t%d\n",(*(p+tem)).na,(*(p+tem)).gra);
			judge=0;
		}
	}
	
	if(judge){
		printf("not found!\n");
	}
}

int main()
{
    int n;
    int jud;
    printf("Input the number of students:\n");
    scanf("%d",&n);
    STU new[n];
    STU *point;
    point=new;

    input(point,n);

    printf("If want to sort,input 1,otherwise input 0:\n");
    scanf("%d",&jud);
    if(jud)
        sort(point,n);
    
    printf("Here are the outputs:\n");
    output(point,n);
    
    printf("Input someone's grade for searching:\n");
    int grade;
    scanf("%d",&grade);
    search(point,n,grade);

    return 0;
}
