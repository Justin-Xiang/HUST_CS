设置共享目录使本机上的文件用于虚拟机

mkdir  /mnt/share(用于创建共享目录)

mount -t vboxsf Downloads /mnt/share

​               共享名    挂载点

 

sudo adduser hadoop sudo(增加管理员权限方便后续部署)

 

配置ssh无密码登录

```
ssh-keygen -t rsa(利用ssh-keygen生成密钥)
```

cat ./id_rsa.pub >> ./authorized_keys(将密码加入授权中)

 

配置java环境变量

cd ~

gedit ~/.bashrc

打开这个文件后在文件开头添加如下内容

```
export JAVA_HOME=/usr/lib/jvm/jdk1.8.0_162
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib
export PATH=${JAVA_HOME}/bin:$PATH
```

source ~/.bashrc(让.bashrc文件配置立马生效)

 

 

 