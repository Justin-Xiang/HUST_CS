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
void initQueue(Queue* const p, int m);  //��ʼ��pָ���У��������m��Ԫ��
void initQueue(Queue* const p, const Queue& s);  //��s�����ʼ��pֵ����
void initQueue(Queue* const p, Queue&& s); //��s�ƶ���ʼ��pָ����
int number(const Queue* const p); //����pָ���е�ʵ��Ԫ�ظ���
int size(const Queue* const p); //����pָ������������Ԫ�ظ���max
Queue* const enter(Queue* const p, int e); //��e�����β����������p
Queue* const leave(Queue* const p, int& e); //�Ӷ��׳�Ԫ�ص�e��������p
Queue* const assign(Queue* const p, const Queue& q); //�����s�����в�����p
Queue* const assign(Queue* const p, Queue&& q); //�ƶ���s�����в�����p
char* print(const Queue* const p, char* s); //��ӡpָ������sβ��������s:s[0] = '\0'
void destroyQueue(Queue* const p); //����pָ��Ķ���
#endif //QUEUE_QUEUE_LAB1_H
