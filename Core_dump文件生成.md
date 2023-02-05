# Core_dump文件生成


 ## 1.查看core文件受限状态
 ```bash
 ulimit -a
 ```
输出为：

 ```bash
core file size              (blocks, -c) 0
 ```

显示为受限

## 2.解除core文件大小限制：

 ```bash
 ulimit -c unlimited
 ```

输出为：

 ```bash
core file size              (blocks, -c) unlimited
 ```

显示为不限

 ## 3.将core_dump文件重定向到工程目录，以下方法只在当前终端连接中有效

 ```bash
 echo "/workspace/CPP/String/core-%t-%p" > /proc/sys/kernel/core_pattern
 ```
%t和%p 用来防止重名

 ## 4.在CMakelist.txt文件中设置为debug模式或者添加“-g”参数

 ```CMakeList
 set(CMAKE_BUILD_TYPE "Debug")
 add_definitions("-Wall -g")
 ```
## 5.加载CMake工程
 ```bash
 cmake .
 ```
## 6.编译工程
 ```bash
make
 ```
## 7.运行目标文件
 ```bash
 ./build
 ```
## 8.gdb 查看core_dump报错信息
 ```bash
gdb build core-1675510529-84585
 ```