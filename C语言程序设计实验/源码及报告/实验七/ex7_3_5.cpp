#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct node {
	int data;
	struct node *next;
} NodeType;
static void create_list(NodeType *&h, char a[], int n) { 
	NodeType *p, *r;
	int i = 0;

	h = (NodeType *)malloc(sizeof(NodeType));
	r = h; 

	while(i<n) {
		p = (NodeType *)malloc(sizeof(NodeType));
		p->data = a[n - i - 1] - '0';
		r->next = p;
		r = p;
		i++;
	}

	r->next = NULL;
}
static void display_list(NodeType *h) {
	NodeType *p = h->next; 
	while(p != NULL) {
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}
static void add_list(NodeType *h1, NodeType *h2, NodeType *&h) { // ָ�������
	NodeType *p1 = h1->next; // p1ָ������h1�еĵ�һ�����ݽ��
	NodeType *p2 = h2->next; // p2ָ������h2�еĵ�һ�����ݽ��
	NodeType *p, *r;
	int carry = 0;
// ����ͷ���
	h = (NodeType *)malloc(sizeof(NodeType));
// rָ���´���ͷ���
	r = h;
	while(p1 != NULL && p2 != NULL) {
// �����½��p
		p = (NodeType *)malloc(sizeof(NodeType));
		p->data = (p1->data + p2->data + carry) % 10; // ����
// ���½��p���뵽rָ���ͷ���֮��
		r->next = p;
// r����һ�����
		r = p;
		carry = (p1->data + p2->data + carry) / 10; // ����
// p1��p2ָ����һ�����
		p1 = p1->next;
		p2 = p2->next;
	}
	if(p1 == NULL)
		p1 = p2;

	while(p1 != NULL) {
		p = (NodeType *)malloc(sizeof(NodeType));
		p->data = (p1->data + carry) % 10; // ������
// ���½��p���뵽rָ���ͷ���֮��
		r->next = p;
// r����һ�����
		r = p;
		carry = (p1->data + carry) / 10;
		p1 = p1->next;
	}

// ���carry��Ϊ0ʱ,����һ���������
	if(carry > 0) {
		p = (NodeType *)malloc(sizeof(NodeType));
		p->data = carry;
// ���½��p���뵽rָ���ͷ���֮��
		r->next = p;
// r����һ�����
		r = p;
	}
	r->next = NULL;
}

/*------------------------��������������h--------------------------*/
static void reverse_list(NodeType *&h) {
	NodeType *p = h->next, *q;
	h->next = NULL;
	while(p != NULL) {
		q = p->next;
		p->next = h->next;
		h->next = p;
		p = q;
	}
}
static int mid_list(NodeType *h) {
	NodeType *slow = h; // ������ָ��
	NodeType *quick = h; // �����ָ��

	while(quick != NULL && quick->next != NULL) {
		slow = slow->next; // ��ָ��slowǰ��һ�����
		quick = quick->next->next; // ��ָ��quickǰ���������
	}
	return slow->data;
}

int main(int argc, char *argv[]) {
	NodeType *h1, *h2, *h;
	char s[MAX_SIZE], t[MAX_SIZE];
	printf("��������1: ");
	scanf("%s", s);
	printf("��������2: ");
	scanf("%s", t);
	create_list(h1, s, strlen(s));
	create_list(h2, t, strlen(t));
	add_list(h1, h2, h);
	reverse_list(h);
	printf("���Ϊ:\n");
	display_list(h);
	return 0;
}

