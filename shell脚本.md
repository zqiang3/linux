## 第一个shell脚本

```shell
#!/bin/bash
echo "Hello World!"

cd ~
mkdir shell_tut
cd shell_tut

for ((i=0; i<10; i++)); do
	touch test_$i.txt
done
```

mkdir, touch都是系统自带的程序，一般在/bin或者/usr/bin目录下。for, do, done是sh脚本语言的关键字 

## 运行shell脚本的方法

**作为可执行程序**

chmod +x test.sh

./test.sh

**直接运行解释器**

/bin/sh test.sh

## shell变量

name=zq

变量名和等号之间不能有空格

**只读变量**

readonly var

**删除变量**

unset var



## 字符串

字符串可以用单引号，也可以用双引号，也可以不用引号。

## 命令行参数

$0: 文件名

$1: 第一个参数

依次类推

$#: 传递到脚本的参数个数

```shell
echo $0  # 文件名
echo $1  # 第一个参数
echo $#  # 参数个数
echo $$  # 当前进程的ID号
echo $!  
echo $-  #
echo $?　#　显示最后命令的退出状态，０表示没有错误
```

