clc,clear;
addpath('C:\Program Files\MATLAB\R2019b\toolbox\jsonlab');
file_name_1='C:\Program Files\MATLAB\R2019b\toolbox\hands.json';
jsonData_1=loadjson(file_name_1);
file_name_2='C:\Program Files\MATLAB\R2019b\toolbox\smg.json';
jsonData_2=loadjson(file_name_2);
file_name_3='C:\Program Files\MATLAB\R2019b\toolbox\shotgun.json';
jsonData_3=loadjson(file_name_3);
file_name_4='C:\Program Files\MATLAB\R2019b\toolbox\rifle.json';
jsonData_4=loadjson(file_name_4);
sell_num=zeros(4720,1);
buy_num=zeros(4720,1);
sell_reference_price=zeros(4720,1);
buy_max_price=zeros(4720,1);
for i=1:238
    sell_num(i,1)=jsonData_1{1,i}.sell_num;
    buy_num(i,1)=jsonData_1{1,i}.buy_num;
    sell_reference_price(i,1)=str2num(jsonData_1{1,i}.sell_reference_price);
    buy_max_price(i,1)=str2num(jsonData_1{1,i}.buy_max_price);
end
j=1;
for i=239:1602
    sell_num(i,1)=jsonData_2{1,j}.sell_num;
    buy_num(i,1)=jsonData_2{1,j}.buy_num;
    sell_reference_price(i,1)=str2num(jsonData_2{1,j}.sell_reference_price);
    buy_max_price(i,1)=str2num(jsonData_2{1,j}.buy_max_price);
    j=j+1;
end
j=1;
for i=1603:2397
    sell_num(i,1)=jsonData_3{1,j}.sell_num;
    buy_num(i,1)=jsonData_3{1,j}.buy_num;
    sell_reference_price(i,1)=str2num(jsonData_3{1,j}.sell_reference_price);
    buy_max_price(i,1)=str2num(jsonData_3{1,j}.buy_max_price);
    j=j+1;
end
j=1;
for i=2398:4720
    sell_num(i,1)=jsonData_4{1,j}.sell_num;
    buy_num(i,1)=jsonData_4{1,j}.buy_num;
    sell_reference_price(i,1)=str2num(jsonData_4{1,j}.sell_reference_price);
    buy_max_price(i,1)=str2num(jsonData_4{1,j}.buy_max_price);
    j=j+1;
end
x=[5,10,15,20,25];
y=[10,40,90,150,400];
X=[sell_num sell_reference_price];
[f,location]=unique(X,'rows','first');
res=sortrows([location,f]);
new_e=res(:,2:3);
new_location=res(:,1);
for j=1:4639
    z(j,1)=buy_max_price(new_location(j,1));
end
m=new_e(:,1);
n=new_e(:,2);
T=[z m n];
D=sortrows(T);
D=D(238:4639,:);
m=D(:,2);
n=D(:,3);
z=D(:,1);
%Z=griddata(m,n,z,x,y);