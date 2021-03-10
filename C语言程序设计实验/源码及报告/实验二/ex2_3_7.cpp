#include<stdio.h>
int main(void)
{
	int year,date,i;
	int month1[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	int month2[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	printf("Please enter the year and day:");
	scanf("%d %d",&year,&date);
	if((year% 4 == 0 && year% 100 != 0) ||(year%400==0))
	{
	for(i=0;i<12;i++)
	{
		if(date<=month1[i])
		{
			break;
		}
		date=date-month1[i];
	}}
	else
	{
	
		for(i=0;i<12;i++)
	{
		if(date<=month2[i])
		{
			break;
		}
		date=date-month2[i];
	}
	}
	printf("ÊÇ%dÔÂ%dÈÕ",i+1,date);
	return 0;
	}
	

