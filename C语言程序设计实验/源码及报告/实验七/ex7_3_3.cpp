#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define null NULL
#define val tp

struct stu{
	long num;
	char s[10];
	int c1;
	int c2;
	int c3;
	int c4;
	double tp;
	int sum;
	struct stu*next;
}; 

void creatlist(struct stu **headp);
void outputlist(struct stu *headp);
void correctlist(struct stu **headp);
//void avstu(struct stu *headp);
//void sumstu(struct stu *headp);
struct stu* sortList(struct stu **head);
struct stu* merge(struct stu *left,struct stu *right);
struct stu* getMidNode(struct stu* node);

void Free_list(struct stu * pHead) //释放链表
{
  struct stu * p;
  while(pHead != NULL)
  {
    p = pHead;
    pHead = pHead->next;
    free(p);
    p = NULL;
  }
}

int main(void)
{
	struct stu *head=NULL;
	creatlist(&head);
	outputlist(head);
	correctlist(&head);
	//avstu(head);
	//sumstu(head);
	outputlist(head);
	outputlist(sortList(&head));
	Free_list(head);
	
	return 0;
}

void creatlist(struct stu **headp)
{
	long n;
	
	struct stu *tail,*temp;
	*headp=(struct stu *)malloc(sizeof(struct stu));
	tail=*headp;
	printf("please input the following item divided by squre\n");
	printf("ID\tname\tEnglishgrade\tmathgrade\tphysicsgrade\tC language grade");
	printf("\nEnd with 0\n");
	while(1)
	{
		scanf("%ld",&n);
		if(n==0)  break;
		
		tail->num=n;
		scanf("%s %d %d %d %d",tail->s,&tail->c1,&tail->c2,&tail->c3,&tail->c4);
		tail->sum=tail->c1+tail->c2+tail->c3+tail->c4;
		tail->tp=tail->sum/4.0;
		
		tail->next=(struct stu *)malloc(sizeof(struct stu));
		temp=tail;
		tail=tail->next;
	}
	
	free(tail);
	temp->next=NULL;
}

void outputlist(struct stu *p)
{
	
	while(p!=NULL)
	{
		printf("ID %ld   NAME  %s  ENG  %d  MATH  %d  PHY  %d  C  %d SUM %d AVERAGE %.2f\n"
		,p->num,p->s,p->c1,p->c2,p->c3,p->c4,p->sum,p->tp);
		p=p->next;
	}
}

void correctlist(struct stu **headp)
{
	char c;
	struct stu *p,*temp;
	int jud=1;
	p=*headp;
	temp=*headp;
	printf("1:look up by name\n");
	printf("2:look up by number\n");
	c=getchar();
	c=getchar();
	switch(c)
	{
		case '1':printf("please input the name\n");
		         char t[10];
		         scanf("%s",t);
		         
		         while(p!=NULL){
		         if(!strcmp(p->s,t)){
		             printf("FIND ID %ld   NAME  %s  ENG  %d  MATH  %d  PHY  %d  C  %d\n"
		,p->num,p->s,p->c1,p->c2,p->c3,p->c4);
				jud=0;
				
				}
				temp=p;
				p=p->next;
			}
			if(jud){
				printf("NOT FOUND\n");
		          	 return ;
			}
			p=temp;
				 break;
		case  '2':printf("please input the number\n");
		          long tmp;
		          scanf("%ld",&tmp);
		          while(p!=NULL){
		          if(tmp==p->num){
		              printf("FIND ID %ld   NAME  %s  ENG  %d  MATH  %d  PHY  %d  C  %d\n"
		,p->num,p->s,p->c1,p->c2,p->c3,p->c4);
					jud=0;
					
				}
				temp=p;
				p=p->next;
	}
		          if(jud){
				printf("NOT FOUND\n");
		          	 return ;
			}
			p=temp;
				  break;
	}
	printf("which one to change?\n");
	printf("1:number\n");
	printf("2:name\n");
	printf("3:Grade of English\n");
	printf("4:Grade of Math\n");
	printf("5:Grade of Physics\n");
	printf("6.Grade of C Language\n");
	printf("7:I don't want to change anything\n");
	c=getchar();
	c=getchar();
	printf("please re-input\n");
	switch(c){
		case '1':scanf("%ld",&p->num);break;
		case '2':scanf("%s",p->s);break;
		case '3':scanf("%d",&p->c1);break;
		case '4':scanf("%d",&p->c2);break;
		case '5':scanf("%d",&p->c3);break;
		case '6':scanf("%d",&p->c4);
		default: return ;
	}
}

/*void avstu(struct stu *p)
{
	
	for(;p!=NULL;p=p->next)
	{
		printf("ID %ld Name %s average %.2lf\n",p->num,p->s,p->tp);
	}
}
*/

/*void sumstu(struct stu *p)
{
	
	for(;p!=NULL;p=p->next)
	{
		int sum;
		sum=p->c1+p->c2+p->c3+p->c4;
		printf("ID %ld Name %s sum %d average %.2lf\n",p->num,p->s,sum,p->tp);
	}
} 
*/

struct stu* sortList(struct stu **head) {
	
	printf("\n\n");
        if(*head == null || (*head)->next == null) return *head;
        
        struct stu* mid = getMidNode(*head);// 获取中间节点
        struct stu* left = *head;
        struct stu* right = mid->next;
        mid->next = null;  // 这一点很重要，不然可能出现循环链表
        *head=merge(sortList(&left),sortList(&right)); 
        return *head;
}
// 合并链表，代码比较长，但是很好理解，头节点需要单独考虑一下
struct stu* merge(struct stu *left,struct stu *right){
    if(left == null) return right;
   if(right == null) return left;
        
    struct stu* head = null, *p = null; // head 头节点，p用于遍历操作
        while(left != null && right != null){
            if(head == null){
                if(left->val < right->val){
                    head = left;
                    left = left->next;
                }else{
                    head = right;
                    right = right->next;
                }
                p = head;
            }else{
                if(left->val < right->val){
                    p->next = left;
                    left = left->next;
                }else{
                    p->next = right;
                    right = right->next;
                }
                p = p->next;
            }
        }
        // 对剩下的节点进行merge
        if(left != null) p->next = left; 
        else p->next = right;
        return head;
    }
    // 使用快慢指针快速找到中间节点
struct stu* getMidNode(struct stu* node){
        if(node == null || node->next == null) return node;
        struct stu* low = node;
        struct stu* fast = node;
        while(fast->next != null && fast->next->next != null){
            low = low->next;
            fast = fast->next->next;
        }
        return low;
}
