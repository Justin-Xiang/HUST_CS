#pragma once
//
// Created by DELL on 2020/10/25.
//
#pragma  once
#ifndef QUEUE_QUEUE_LAB1_H
#define QUEUE_QUEUE_LAB1_H
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
struct Queue
{
    int* const elems;
    const int max;
    int head, tail;
};
void initQueue(Queue* const p, int m);  //初始化p指队列，最多申请m个元素
void initQueue(Queue* const p, const Queue& s);  //用s深拷贝初始化p值队列
void initQueue(Queue* const p, Queue&& s); //用s移动初始化p指队列
int number(const Queue* const p); //返回p指队列的实际元素个数
int size(const Queue* const p); //返回p指队列申请的最大元素个数max
Queue* const enter(Queue* const p, int e); //将e入队列尾部，并返回p
Queue* const leave(Queue* const p, int& e); //从队首出元素到e，并返回p
Queue* const assign(Queue* const p, const Queue& q); //深拷贝赋s给队列并返回p
Queue* const assign(Queue* const p, Queue&& q); //移动赋s给队列并返回p
char* print(const Queue* const p, char* s); //打印p指队列至s尾部并返回s:s[0] = '\0'
void destroyQueue(Queue* const p); //销毁p指向的队列
#endif //QUEUE_QUEUE_LAB1_H
