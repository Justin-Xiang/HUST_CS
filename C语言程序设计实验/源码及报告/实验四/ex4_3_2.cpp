#include<stdio.h>
#include<math.h>
void zimi(int k) {
	if(k==0) {
		return;
	} else if(k==3) {
		int num[3],n,m,i,count=0,sum[10];
		for(n=100; n<=999; n++) {
			m=n;
			for(i=0; i<3; i++) {
				num[i]=m%10;
				m/=10;
			}
			if(n==((pow(num[0],3)+pow(num[1],3)+pow(num[2],3)))) {
				sum[count]=n;
				count++;
			}

		}
		printf("三位的水仙花数共有%d个：",count);
		for(i=0; i<count; i++) {
			printf("%d ",sum[i]);
		}
		printf("\n");
	} else if(k==4) {
		int num[4],n,m,i,count=0,sum[10];
		for(n=1000; n<=9999; n++) {
			m=n;
			for(i=0; i<4; i++) {
				num[i]=m%10;
				m/=10;
			}
			if(n==((pow(num[0],4)+pow(num[1],4)+pow(num[2],4)+pow(num[3],4)))) {
				sum[count]=n;
				count++;
			}

		}
		printf("四位的水仙花数共有%d个：",count);
		for(i=0; i<count; i++) {
			printf("%d ",sum[i]);
		}
		printf("\n");
	} else if(k==5) {
		int num[5],n,m,i,count=0,sum[10];
		for(n=10000; n<=99999; n++) {
			m=n;
			for(i=0; i<5; i++) {
				num[i]=m%10;
				m/=10;
			}
			if(n==((pow(num[0],5)+pow(num[1],5)+pow(num[2],5)+pow(num[3],5)+pow(num[4],5)))) {
				sum[count]=n;
				count++;
			}

		}
		printf("五位的五角星数共有%d个：",count);
		for(i=0; i<count; i++) {
			printf("%d ",sum[i]);
		}
		printf("\n");

	} else if(k==6) {
		int num[6],n,m,i,count=0,sum[10];
		for(n=100000; n<=999999; n++) {
			m=n;
			for(i=0; i<6; i++) {
				num[i]=m%10;
				m/=10;
			}
			if(n==((pow(num[0],6)+pow(num[1],6)+pow(num[2],6)+pow(num[3],6)+pow(num[4],6)+pow(num[5],6)))) {
				sum[count]=n;
				count++;
			}

		}
		printf("六位的六合数共有%d个：",count);
		for(i=0; i<count; i++) {
			printf("%d ",sum[i]);
		}
		printf("\n");
	} else if(k==7) {
		int num[7],n,m,i,count=0,sum[10];
		for(n=1000000; n<=9999999; n++) {
			m=n;
			for(i=0; i<7; i++) {
				num[i]=m%10;
				m/=10;
			}
			if(n==((pow(num[0],7)+pow(num[1],7)+pow(num[2],7)+pow(num[3],7)+pow(num[4],7)+pow(num[5],7)+pow(num[6],7)))) {
				sum[count]=n;
				count++;
			}

		}
		printf("七位的北斗七星数共有%d个： ",count);
		for(i=0; i<count; i++) {
			printf("%d ",sum[i]);
		}
		printf("\n");
	} else if(k==8) {
		int num[8],n,m,i,count=0,sum[10];
		for(n=10000000; n<=99999999; n++) {
			m=n;
			for(i=0; i<8; i++) {
				num[i]=m%10;
				m/=10;
			}
			if(n==((pow(num[0],8)+pow(num[1],8)+pow(num[2],8)+pow(num[3],8)+pow(num[4],8)+pow(num[5],8)+pow(num[6],8)+pow(num[7],8)))) {
				sum[count]=n;
				count++;
			}

		}
		printf("八位的八仙数共有%d个：",count);
		for(i=0; i<count; i++) {
			printf("%d ",sum[i]);
		}
		printf("\n");
	}
}
int main(void) {
	
	
	int k,flag=1;
	char c;
	while(flag)
	{
	printf("请输入你想知道的自幂数的位数，我会告诉你有多少个并输出\n");
	printf("输入0可退出程序\n");
	scanf("%d",&k);
	if(k==0)
	{
		flag=0;
	 } 
	if(k!=0)
	zimi(k);
}
	return 0;
}
    
