//
// Created by DELL on 2020/10/25.
//
#include "Queuelab_1.h"
#pragma warning(disable:4996)
using namespace std;
void initQueue(Queue* const p, int m)
{
    cout << "call void initQueue(Queue *const p:" << p << ",int m:" << m << ")" << endl;
    int* temp;
    temp = (int*)malloc(sizeof(int) * m);
    if (temp == NULL) { return; }
    *(int**)&(p->elems) = temp;
    *(int*)&(p->max) = m;
    p->head = p->tail = 0;
} //初始化p指队列：最多申请m个元素

void initQueue(Queue* const p, const Queue& s)
{
    cout << "call void initQueue(Queue * const p:" << p << "const Queue &s)" << endl;
    int* temp;
    temp = (int*)malloc(sizeof(int) * s.max);
    if (temp == NULL) { return; }
    *(int**)&(p->elems) = temp;
    memcpy(temp, s.elems, (s.max) * sizeof(int));
    *(int*)&(p->max) = s.max;
    p->head = s.head;
    p->tail = s.tail;
} //用s深拷贝初始化p指队列

void initQueue(Queue* const p, Queue&& s)
{
    cout << "call void initQueue(Queue * const p:" << p << "Queue **s)" << endl;
    *(int**)&(p->elems) = s.elems;
    *(int**)&(s.elems) = NULL;
    *(int*)&(p->max) = s.max;
    *(int*)&(s.max) = 0;
    p->head = s.head;
    p->tail = s.tail;
    s.head = s.tail = 0;
} //用s移动初始化p指队列

int number(const Queue* const p)
{
    cout << "call int number(const Queue * const p:" << p << ")" << endl;
    return p->max ? (p->tail - p->head + p->max) % p->max : 0;
} //返回p指队列的实际元素个数

int size(const Queue* const p)
{
    cout << "call int size(const Queue * const p:" << p << ")" << endl;
    return p->max;
} //返回p指队列申请的最大元素个数

Queue* const enter(Queue* const p, int e)
{
    cout << "call Queue * const enter(Queue * const p:" << p << ",int e:" << e << ")" << endl;
    if ((p->tail + 1) % p->max == p->head) { throw "Queue is full!"; }
    *(p->elems + p->tail) = e;
    p->tail = (p->tail + 1) % p->max;
    return p;
} //将e入队列尾部，并返回p

Queue* const leave(Queue* const p, int& e)
{
    cout << "call Queue * const leave(Queue * const p:" << p << ",int &e)" << endl;
    if (p->head == p->tail) { throw "Queue is empty!"; }
    e = *(p->elems + p->head);
    p->head = (p->head + 1) % p->max;
    return p;
} //从队首出元素到e，并返回p

Queue* const assign(Queue* const p, const Queue& s)
{
    cout << "call Queue * const assign(Queue * const p:" << p << ",const Queue &s)" << endl;
    int* temp;
    if (p == &s) { return p; }
    temp = (int*)malloc(sizeof(int) * (s.max));
    if (temp == NULL) { return p; }
    memcpy(temp, s.elems, (s.max) * sizeof(int));
    destroyQueue(p);
    *(int**)&(p->elems) = temp;
    *(int*)&(p->max) = s.max;
    p->head = s.head;
    p->tail = s.tail;
    return p;
} //深拷贝赋s给队列并返回p

Queue* const assign(Queue* const p, Queue&& s)
{
    cout << "call Queue* const assign(Queue* const p:" << p << ",Queue&& s)" << endl;
    if (p == &s) { return p; }
    destroyQueue(p);
    *(int**)&(p->elems) = s.elems;
    *(int**)&(s.elems) = NULL;
    *(int*)&(p->max) = s.max;
    *(int*)&(s.max) = 0;
    p->head = s.head;
    p->tail = s.tail;
    s.head = s.tail = 0;
    return p;
}//移动赋s给队列并返回p

char* print(const Queue* const p, char* s)
{
    cout << "call char* print (const Queue * const p:" << p << ",char *s)" << endl;
    int qLength, strLength, tempInt, point;
    qLength = number(p);
    strLength = 0;
    point = p->head;
    for (tempInt = 0; tempInt < qLength; tempInt++)
    {
        strLength += sprintf(s + strLength, "%d ", *(p->elems + point));
        point = (point + 1) % p->max;
    }
    return s;
} //打印p指队列至s尾部并返回s:s[0] ='\0'

void destroyQueue(Queue* const p)
{
    cout << "call void destroyQueue(Queue * const p:" << p << ")" << endl;
    if (p->elems) { free(p->elems); }
    *(int**)&(p->elems) = NULL;
    *(int*)&(p->max) = 0;
    p->head = p->tail = 0;
} //销毁p指向的队列