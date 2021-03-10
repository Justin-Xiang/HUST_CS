clc,clear;
addpath('C:\Program Files\MATLAB\R2019b\toolbox\jsonlab');
file_name='C:\Program Files\MATLAB\R2019b\toolbox\history.json';
jsonData=loadjson(file_name);
date=zeros(1,1154604);
date_1=zeros(1,1154604);
price=zeros(1,1154604);
for i=1:1154604
    date(1,i)=str2num(jsonData{1,i}.date);
    date_1(1,i)=ceil(ConvertToMatlabDate(date(1,i)))-18275;
    price(1,i)=jsonData{1,i}.price;
end
m=1;
a=zeros(1,1154604);
Date=zeros(1,92);
Price=zeros(1,92);
for i=1:1154604
    if a(1,i)==0
        Date(1,m)=date_1(1,i);
        for j=1:1154604
            if date_1(1,j)==date_1(1,i)
                a(1,j)=1;
                Price(1,m)=Price(1,m)+price(1,j);
            end
        end
        m=m+1;
    end
end
[A,index]=sort(Date');
B=zeros(92,1);
for n=1:92
    B(n)=Price(1,index(n));
end
plot(A,B)
function [date_1] = ConvertToMatlabDate(date)
date_1= (date+28800)/86400;
end