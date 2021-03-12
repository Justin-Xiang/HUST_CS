#include "Queue_lab2.h"
using namespace std;
QUEUE::QUEUE(int m) :elems(nullptr), max(m), head(0), tail(0)
{
	cout << "call QUEUE::QUEUE(int m:" << m << "): 0x" << this << " " << endl;
	*(int**)&elems = new int[m];
}

QUEUE::QUEUE(const QUEUE& q) : elems(nullptr), max(q.max), head(q.head), tail(q.tail)
{
	cout << "call QUEUE::QUEUE(const QUEUE& q): 0x" << this << " " << endl;
	*(int**)&elems = new int[max];
	memcpy(elems, q.elems, max * sizeof(int));
}

QUEUE::QUEUE(QUEUE&& q)noexcept : elems(q.elems), max(q.max), head(q.head), tail(q.tail)
{
	cout << "call QUEUE::QUEUE(QUEUE&& q): 0x" << this << " : 0x" << this << " noexcept" << endl;
	*(int**)&q.elems = nullptr;
	*(int*)&q.max = 0;
	q.head = 0; 
	q.tail = 0;
}

QUEUE::operator int() const noexcept
{
	cout << "call QUEUE::operator int(): 0x" << this << " const noexcept" << endl;
	return max ? (tail - head + max) % max : 0;
}

int QUEUE::size() const noexcept
{
	cout << "call int QUEUE::size(): 0x" << this << " const noexcept" << endl;
	return max;
}

QUEUE& QUEUE::operator<<(int e)
{
	cout << "call QUEUE& QUEUE::operator<<(int e:" << e << "): 0x" << this << " " << endl;
	if ((tail + 1) % max == head)
	{
		throw "QUEUE is full!";
	}
	elems[tail] = e;
	tail = (tail + 1) % max;
	return *this;
}

QUEUE& QUEUE::operator>>(int& e)
{
	cout << "call QUEUE& QUEUE::operator>>(int& e): 0x" << this << " " << endl;
	if (head == tail)
	{
		throw "QUEUE is empty!";
	}
	e = elems[head];
	head = (head + 1) % max;
	return *this;
}

QUEUE& QUEUE::operator=(const QUEUE& q)
{
	cout << "call QUEUE& QUEUE::operator=(const QUEUE& q): 0x" << this << " " << endl;
	if (this == &q) { return *this; }
	if (elems) delete elems;
	*(int**)&elems = new int[q.max];
	memcpy(elems, q.elems, max * sizeof(int));
	*(int*)&max = q.max;
	head = q.head;
	tail = q.tail;
	return *this;
}

QUEUE& QUEUE::operator=(QUEUE&& q)noexcept
{
	cout << "call QUEUE& QUEUE::operator=(QUEUE&& q): 0x" << this << " noexcept" << endl;
	if (this == &q) { return *this; }
	if (this->elems) { delete this->elems; }
	*(int**)&elems = q.elems;
	*(int**)&(q.elems) = nullptr;
	*(int*)&max = q.max;
	*(int*)&(q.max) = 0;
	head = q.head;
	tail = q.tail;
	q.head = 0;
	q.tail = 0;
	return *this;
}

char* QUEUE::print(char* s) const noexcept
{
	cout << "call char* QUEUE::print(char* s): 0x" << this << " const noexcept" << endl;
	int qLength, strLength, tempInt, point;
	qLength = int(*this);
	strLength = 0;
	point = head;
	for (tempInt = 0; tempInt < qLength; tempInt++)
	{
		strLength += sprintf(s + strLength, "%d ", *(elems + point));
		point = (point + 1) % max;
	}
	return s;
}

QUEUE::~QUEUE()
{
	cout << "call QUEUE::~QUEUE(): 0x" << this << " " << endl;
	if (elems != nullptr) { delete[]elems; }
	*(int**)&elems = nullptr;
	*(int*)&max = 0;
	head = 0;
	tail = 0;
}
