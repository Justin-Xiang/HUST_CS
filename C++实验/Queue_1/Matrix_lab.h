#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable : 4996)
#include <iomanip> 
#include <exception>
#include <typeinfo>
#include <string.h>
using namespace std;
template <typename T>
class MAT {
	T* const e;							//指向所有整型矩阵元素的指针
	const int r, c;							//矩阵的行r和列c大小
public:
	MAT(int r, int c);						//矩阵定义
	MAT(const MAT& a);				//深拷贝构造
	MAT(MAT&& a)noexcept;			//移动构造
	virtual ~MAT()noexcept;
	virtual T* const operator[ ](int r);//取矩阵r行的第一个元素地址，r越界抛异常
	virtual MAT operator+(const MAT& a)const;	//矩阵加法，不能加抛异常
	virtual MAT operator-(const MAT& a)const;	//矩阵减法，不能减抛异常
	virtual MAT operator*(const MAT& a)const;	//矩阵乘法，不能乘抛异常
	virtual MAT operator~()const;					//矩阵转置
	virtual MAT& operator=(const MAT& a);		//深拷贝赋值运算
	virtual MAT& operator=(MAT&& a)noexcept;	//移动赋值运算
	virtual MAT& operator+=(const MAT& a);		//“+=”运算
	virtual MAT& operator-=(const MAT& a);		//“-=”运算
	virtual MAT& operator*=(const MAT& a);		//“*=”运算
//print输出至s并返回s：列用空格隔开，行用回车结束
	virtual char* print(char* s)const noexcept;
};

template <typename T>
MAT<T>::MAT(int r, int c) : r(r), c(c), e(nullptr)
{
	cout << "call MAT<" << typeid(T).name() << ">::MAT<" << typeid(T).name() << ">(int r:" << r << ",int c:" << c << ")" << endl;
	*(T**)(&e) = new T[r * c];
}

template <typename T>
MAT<T>::MAT(const MAT& a) :r(a.r), c(a.c), e(nullptr)
{
	cout << "call MAT<" << typeid(T).name() << ">::MAT(const MAT& a)" << endl;
	*(T**)(&e) = new T[r * c];
	for (register int tr = 0; tr < r; tr++)
	{
		for (register int tc = 0; tc < c; tc++)
		{
			(this->operator[](tr))[tc] = ((MAT&)a)[tr][tc];
		}
	}
}

template <typename T>
MAT<T>::MAT(MAT&& a) noexcept :r(a.r), c(a.c), e(a.e)
{
	cout << "call MAT<" << typeid(T).name() << ">::MAT(MAT&& a)noexcept" << endl;
	*(int*)&(a.r) = 0;
	*(int*)&(a.c) = 0;
	*(T**)&(a.e) = nullptr;
}

template <typename T>
MAT<T>::~MAT()noexcept
{
	cout << "call MAT<" << typeid(T).name() << ">::~MAT()noexcept" << endl;
	*(int*)&r = 0;
	*(int*)&c = 0;
	if (e) { delete[]e; }
	*(T**)(&e) = nullptr;
}

template <typename T>
T* const MAT<T>::operator[ ](int r)
{
	cout << "call " << typeid(T).name() << "* const MAT<" << typeid(T).name() << ">::operator[](int r:" << r << ")" << endl;
	if (r < 0 || r >= this->r) { throw ""; }
	return e + r * c;
}//取矩阵r行的第一个元素地址，r越界抛异常

template <typename T>
MAT<T> MAT<T>::operator+(const MAT& a)const
{
	cout << "call MAT<" << typeid(T).name() << "> MAT<" << typeid(T).name() << ">::operator+(const MAT& a)const" << endl;
	if (r != a.r || c != a.c) { throw""; }
	MAT tm(r, c);
	for (register int tr = 0; tr < r; tr++)
	{
		for (register int tc = 0; tc < c; tc++)
		{
			tm[tr][tc] = (((MAT*)this)->operator[](tr))[tc] + ((MAT&)a)[tr][tc];
		}
	}
	return tm;
}

template <typename T>
MAT<T> MAT<T>::operator-(const MAT& a)const
{
	cout << "call MAT<" << typeid(T).name() << "> MAT<" << typeid(T).name() << ">::operator-(const MAT& a)const" << endl;
	if (r != a.r || c != a.c) { throw""; }
	MAT tm(r, c);
	for (register int tr = 0; tr < r; tr++)
	{
		for (register int tc = 0; tc < c; tc++)
		{
			tm[tr][tc] = (((MAT*)this)->operator[](tr))[tc] - ((MAT&)a)[tr][tc];
		}
	}
	return tm;
}//矩阵减法，不能减抛异常

template <typename T>
MAT<T> MAT<T>::operator*(const MAT& a)const
{
	cout << "call MAT<" << typeid(T).name() << "> MAT<" << typeid(T).name() << ">::operator*(const MAT& a)const" << endl;
	if (c != a.r) { throw""; }
	MAT tm(r, a.c);
	char tmp[1000];
	for (register int tr = 0; tr < r; tr++)
	{
		for (register int tc = 0; tc < a.c; tc++)
		{
			tm[tr][tc] = 0;
			for (register int tt = 0; tt < c; tt++)
			{
				tm[tr][tc] += (((MAT*)this)->operator[](tr))[tt] * ((MAT&)a)[tt][tc];
			}
		}
	}
	return tm;
}	//矩阵乘法，不能乘抛异常

template <typename T>
MAT<T> MAT<T>:: operator~()const
{
	cout << "call MAT<" << typeid(T).name() << "> MAT<" << typeid(T).name() << ">::operator~()const" << endl;
	MAT tm(c, r);
	for (register int tr = 0; tr < tm.r; tr++)
	{
		for (register int tc = 0; tc < tm.c; tc++)
		{
			tm[tr][tc] = (((MAT*)this)->operator[](tc))[tr];
		}
	}
	return tm;
}//矩阵转置

template <typename T>
MAT<T>& MAT<T>::operator=(const MAT& a)
{
	cout << "call MAT<" << typeid(T).name() << ">& MAT<" << typeid(T).name() << ">::operator=(const MAT& a)" << endl;
	if (this == &a) { return *this; }
	*(int*)&r = a.r;
	*(int*)&c = a.c;
	if (e) { delete[]e; }
	*(T**)(&e) = new T[r * c];
	for (register int tr = 0; tr < r; tr++)
	{
		for (register int tc = 0; tc < c; tc++)
		{
			(this->operator[](tr))[tc] = ((MAT&)a)[tr][tc];
		}
	}
	return *this;
}//深拷贝赋值运算

template <typename T>
MAT<T>& MAT<T>::operator=(MAT&& a)noexcept
{
	cout << "call MAT<" << typeid(T).name() << ">& MAT<" << typeid(T).name() << ">::operator=(MAT&& a)noexcept" << endl;
	if (this == &a) { return *this; }
	*(int*)&r = a.r;
	*(int*)&c = a.c;
	if (e) { delete[]e; }
	*(T**)(&e) = a.e;
	*(int*)&(a.r) = 0;
	*(int*)&(a.c) = 0;
	*(T**)&(a.e) = nullptr;
	return *this;
}//移动赋值运算


template <typename T>
MAT<T>& MAT<T>::operator+=(const MAT& a)
{
	cout << "call MAT<" << typeid(T).name() << ">& MAT<" << typeid(T).name() << ">::operator+=(const MAT& a)" << endl;
	return (*this = *this + a);
}

template <typename T>
MAT<T>& MAT<T>::operator-=(const MAT& a)
{
	cout << "call MAT<" << typeid(T).name() << ">& MAT<" << typeid(T).name() << ">::operator-=(const MAT& a)" << endl;
	return (*this = *this - a);
}

template <typename T>
MAT<T>& MAT<T>::operator*=(const MAT& a)
{
	cout << "call MAT<" << typeid(T).name() << ">& MAT<" << typeid(T).name() << ">::operator*=(const MAT& a)" << endl;
	return (*this = *this * a);
}

int print_my(char* s, int t)
{
	return sprintf(s, "%6ld", t);
}
int print_my(char* s, long long int t)
{
	return sprintf(s, "%6lld", t);
}
int print_my(char* s, float t)
{
	return sprintf(s, "%8f", t);
}
int print_my(char* s, double t)
{
	return sprintf(s, "%8lf", t);
}
template <typename T>
char* MAT<T>::print(char* s)const noexcept
{
	cout << "call char* MAT<" << typeid(T).name() << ">::print(char* s)const noexcept" << endl;
	int offstr;
	static int f = 0;
	offstr = 0;
	for (register int tr = 0; tr < r; tr++)
	{
		for (register int tc = 0; tc < c; tc++)
		{
			offstr += print_my(s + offstr, ((MAT*)this)->operator[](tr)[tc]);
		}
		offstr += sprintf(s + offstr, "\n");
	}
	f++;
	return s;
}
