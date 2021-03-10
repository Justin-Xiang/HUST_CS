clc,clear;
addpath('C:\Program Files\MATLAB\R2019b\toolbox\jsonlab');
file_name='C:\Program Files\MATLAB\R2019b\toolbox\pistolOrder.json';
jsonData=loadjson(file_name);
date=zeros(1,107111);
date_1=zeros(1,107111);
price=zeros(1,107111);
for i=1:107111
    date(1,i)=jsonData{1,i}.date;
    date_1(1,i)=ceil(ConvertToMatlabDate(date(1,i)))-18246;
    price(1,i)=str2num(jsonData{1,i}.price);
end
m=1;
a=zeros(1,107111);
Date=zeros(1,622);
Price=zeros(1,622);
for i=1:107111
    if a(1,i)==0
        Date(1,m)=date_1(1,i);
        for j=1:107111
            if date_1(1,j)==date_1(1,i)
                a(1,j)=1;
                Price(1,m)=Price(1,m)+price(1,j);
            end
        end
        m=m+1;
    end
end
[A,index]=sort(Date');
B=zeros(622,1);
for n=1:622
    B(n)=Price(1,index(n));
end
plot(A(502:622,1),B(502:622,1))
function [date_1] = ConvertToMatlabDate(date)
date_1= (date+28800)/86400;
end