clc,clear;
addpath('C:\Program Files\MATLAB\R2019b\toolbox\jsonlab');
file_name='C:\Program Files\MATLAB\R2019b\toolbox\machinegunOrder.json';
jsonData=loadjson(file_name);
date=zeros(1,10740);
date_1=zeros(1,10740);
price=zeros(1,10740);
for i=1:10740
    date(1,i)=jsonData{1,i}.date;
    date_1(1,i)=ceil(ConvertToMatlabDate(date(1,i)))-18247;
    price(1,i)=str2num(jsonData{1,i}.price);
end
m=1;
a=zeros(1,10740);
Date=zeros(1,375);
Price=zeros(1,375);
for i=1:10740
    if a(1,i)==0
        Date(1,m)=date_1(1,i);
        for j=1:10740
            if date_1(1,j)==date_1(1,i)
                a(1,j)=1;
                Price(1,m)=Price(1,m)+price(1,j);
            end
        end
        m=m+1;
    end
end
[A,index]=sort(Date');
B=zeros(375,1);
for n=1:375
    B(n)=Price(1,index(n));
end
plot(A(255:375,1),B(255:375,1))
function [date_1] = ConvertToMatlabDate(date)
date_1= (date+28800)/86400;
end