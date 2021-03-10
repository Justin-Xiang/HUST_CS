clc,clear;
addpath('C:\Program Files\MATLAB\R2019b\toolbox\jsonlab');
file_name='C:\Program Files\MATLAB\R2019b\toolbox\knifeOrder.json';
jsonData=loadjson(file_name);
date=zeros(1,43635);
date_1=zeros(1,43635);
price=zeros(1,43635);
for i=1:43635
    date(1,i)=jsonData{1,i}.date;
    date_1(1,i)=ceil(ConvertToMatlabDate(date(1,i)))-17784;
    price(1,i)=str2num(jsonData{1,i}.price);
end
m=1;
a=zeros(1,43635);
Date=zeros(1,399);
Price=zeros(1,399);
for i=1:43635
    if a(1,i)==0
        Date(1,m)=date_1(1,i);
        for j=1:43635
            if date_1(1,j)==date_1(1,i)
                a(1,j)=1;
                Price(1,m)=Price(1,m)+price(1,j);
            end
        end
        m=m+1;
    end
end
[A,index]=sort(Date');
B=zeros(399,1);
for n=1:399
    B(n)=Price(1,index(n));
end
plot(A(250:370,1),B(250:370,1))
function [date_1] = ConvertToMatlabDate(date)
date_1= (date+28800)/86400;
end