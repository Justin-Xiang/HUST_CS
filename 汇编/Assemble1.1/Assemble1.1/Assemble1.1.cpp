// Assemble1.1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
int m = 10;
unsigned int n = 1;
int  a[5] = { 1, 2, 3, 4, 5 };
short x = 100;
short y = -32700;  //注意观察初始值较大带来的问题
int  psub;
int sum(int a[], unsigned length)
{
	int i;
	int result = 0;
	for (i = 0; i < length; i++)
		result += a[i];

	return result;
}
int main(int argc, char* argv[])
{
	short z;
	char str[10] = "The end!";
	z = sum(a, 5);
	printf("sum : %d \n", z);
	if (x > y)
		printf("condition1:  %d > %d \n", x, y);
	else
		printf("condition1:  %d < %d \n", x, y);
	z = x - y;
	printf("condition2: (%d) - (%d) = %d \n", x, y, z);
	psub = &x - &y;
	if (psub < 0)
		printf("condition3: & %d < & %d \n", x, y);
	printf(str);
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
