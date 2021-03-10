#include<stdio.h>
struct bits{
	unsigned char bit0:1,bit1:1,bit2:1,bit3:1,bit4:1,bit5:1,bit6:1,bit7:1;
}a; 
union w{
	unsigned char t;
	struct bits a;
}m;
void f0(struct bits b){
	printf("the 1 function %d is called!\n",b.bit0);
}
void f1(struct bits b){
	printf("the 2 function %d is called!\n",b.bit1);
}
void f2(struct bits b){
	printf("the 3 function %d is called!\n",b.bit2);
}
void f3(struct bits b){
	printf("the 4 function %d is called!\n",b.bit3);
}
void f4(struct bits b){
	printf("the 5 function %d is called!\n",b.bit4);
}
void f5(struct bits b){
	printf("the 6 function %d is called!\n",b.bit5);
}
void f6(struct bits b){
	printf("the 7 function %d is called!\n",b.bit6);
}
void f7(struct bits b){
	printf("the 8 function %d is called!\n",b.bit7);
}

int main(void)
{
	void(*p_fun[8])(struct bits b);
	printf("input char:");
	m.t=getchar();
	m.a.bit0=1;
	p_fun[0]=f0;
	p_fun[1]=f1;
	p_fun[2]=f2;
	p_fun[3]=f3;
	p_fun[4]=f4;
	p_fun[5]=f5;
	p_fun[6]=f6;
	p_fun[7]=f7;
	if(m.a.bit0)  p_fun[0](m.a);
	if(m.a.bit1)  p_fun[1](m.a);
	if(m.a.bit2)  p_fun[2](m.a);
	if(m.a.bit3)  p_fun[3](m.a);
	if(m.a.bit4)  p_fun[4](m.a);
	if(m.a.bit5)  p_fun[5](m.a);
	if(m.a.bit6)  p_fun[6](m.a);
	if(m.a.bit7)  p_fun[7](m.a);
	return 0;
}
