#include "Stack_lab.h"
#define POP_STACK_COMPLEX 1
using namespace std;
STACK::STACK(int m) :q(m), QUEUE(m) { cout << "call STACK::STACK(int m:" << m << ")" << endl; }  		//初始化栈：最多存放2m-2个元素
STACK::STACK(const STACK& s) : q(s.q), QUEUE(s.q.size())
{
	cout << "call STACK::STACK(const STACK& s:)" << endl;
	QUEUE::operator=(s);
} //用栈s深拷贝初始化栈
STACK::STACK(STACK&& s)noexcept :q(0), QUEUE(0)
{
	cout << "call STACK::STACK(STACK&& s:)noexcept" << endl;
	QUEUE::operator=((STACK&&)s);
	q.operator=((QUEUE&&)s.q);
} //用栈s移动拷贝初始化栈
int  STACK::size()const noexcept
{
	cout << "call int STACK::size()const noexcept" << endl;
	return (QUEUE::size()) * 2;
}		  		//返回栈的容量即2m
STACK::operator int() const noexcept
{
	cout << "call STACK::operator int()const noexcept" << endl;
	return (QUEUE::operator int()) + q.operator int();
}	   		//返回栈的实际元素个数
#ifdef POP_STACK_COMPLEX
STACK& STACK::operator<<(int e)
{
	cout << "call STACK& STACK::operator<<(int e:" << e << ")" << endl;
	int t, l;
	if (QUEUE::operator int() == QUEUE::size() - 1)
	{
		if (q.operator int() == QUEUE::size() - 1) { throw "STACK is full!"; }
		q << (QUEUE::operator>>(t), t);
	}
	QUEUE::operator<<(e);
	return *this;
}

STACK& STACK::operator>>(int& e)
{
	cout << "call STACK& STACK::operator>>(int& e:)" << endl;
	int t, l;
	if (QUEUE::operator int() == 0)
	{
		if (q.operator int() == 0) { throw "STACK is empty!"; }
		while (q.operator int())
		{
			QUEUE::operator<<((q >> t, t));
		}
	}

	l = QUEUE::operator int();
	l--;
	for (int i = 0; i < l; i++)
	{
		QUEUE::operator<<((QUEUE::operator>>(t), t));
	}
	QUEUE::operator>>(e);
	return *this;
}

#else
STACK& STACK::operator<<(int e)
{
	int t, l;
	if (QUEUE::operator int() == QUEUE::size() - 1)
	{
		if (q.operator int() != 0) { throw "STACK is full!"; }
		while (QUEUE::operator int())
		{
			q << (QUEUE::operator>>(t), t);
		}
	}
	QUEUE::operator<<(e);
	l = QUEUE::operator int();
	l--;
	for (int i = 0; i < l; i++)
	{
		QUEUE::operator<<((QUEUE::operator>>(t), t));
	}
	return *this;
} 	     		//将e入栈，并返回当前栈

STACK& STACK::operator>>(int& e)
{
	int t, l;
	if (QUEUE::operator int() == 0)
	{
		if (q.operator int() == 0) { throw "STACK is empty!"; }
		while (q.operator int())
		{
			QUEUE::operator<<((q >> t, t));
		}
	}
	QUEUE::operator>>(e);
	return *this;
}//出栈到e，并返回当前栈
#endif // POP_STACK_COMPLEX

STACK& STACK::operator=(const STACK& s)
{
	cout << "call STACK& STACK::operator=(const STACK& s)" << endl;
	if (this == &s) { return *this; }
	QUEUE::operator=(s);
	q = s.q;
	return *this;
}	//深拷贝赋值并返回被赋值栈
STACK& STACK::operator=(STACK&& s)noexcept
{
	cout << "call STACK& STACK::operator=(STACK&& s)noexcept" << endl;
	if (this == &s) { return *this; }
	QUEUE::operator=((STACK&&)s);
	q = (STACK&&)s.q;
	return *this;
}//移动赋值并返回被赋值栈

#ifdef POP_STACK_COMPLEX
char* STACK::print(char* b)const noexcept
{
	cout << "call char* STACK::print(char* b)const noexcept" << endl;
	int l, i, t, offstr, i2, l2, count;
	int* tempIntL;
	l = q.operator int();
	offstr = 0;
	t = 0;
	if (l)
	{
		l--;
		l2 = q.size();
		count = 0;
		for (i2 = 0; i2 < l2; i2++)
		{
			for (i = 0; i <= l; i++)
			{
				((QUEUE*)&q)->QUEUE::operator>>(t);
				((QUEUE*)&q)->QUEUE::operator<<(t);
				if (i == count)
				{
					offstr += sprintf(b + offstr, "%d ", t);
					count++;
				}
			}
		}
	}
	l = QUEUE::operator int();
	l--;
	l2 = QUEUE::size();
	count = 0;
	for (i2 = 0; i2 < l2; i2++)
	{
		for (i = 0; i <= l; i++)
		{
			(*(STACK*)this).QUEUE::operator>>(t);
			(*(STACK*)this).QUEUE::operator<<(t);
			if (i == count)
			{
				offstr += sprintf(b + offstr, "%d ", t);
				count++;
			}
		}
	}
	return b;
}
#else
char* STACK::print(char* b)const noexcept
{
	int* tempIntL;
	int l, i, t, offstr;
	tempIntL = new int[q.size() * 2];
	l = q.operator int();
	offstr = 0;
	t = 0;
	if (l != 0)
	{
		for (i = 0; i < l; i++)
		{
			((QUEUE*)&q)->QUEUE::operator>>(t);
			tempIntL[i] = t;
			((QUEUE*)&q)->QUEUE::operator<<(t);
		}
		while (true)
		{
			i--;
			if (i < 0) { break; }
			offstr += sprintf(b + offstr, "%d ", tempIntL[i]);
		}
	}
	l = QUEUE::operator int();
	for (i = 0; i < l; i++)
	{
		(*(STACK*)this).QUEUE::operator>>(t);
		tempIntL[i] = t;
		(*(STACK*)this).QUEUE::operator<<(t);
	}
	while (true)
	{
		i--;
		if (i < 0) { break; }
		offstr += sprintf(b + offstr, "%d ", tempIntL[i]);
	}
	delete[]tempIntL;
	return b;
}	//从栈底到栈顶打印栈元素 
#endif // POP_STACK_COMPLEX

STACK::~STACK()noexcept
{
	cout << "call STACK::~STACK()noexcept" << endl;
	q.~QUEUE();
	QUEUE::~QUEUE();
}	             	//销毁栈

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