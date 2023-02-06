# Core_dump文件生成


 ## 1. 查看core文件受限状态
 ```bash
 ulimit -a
 ```
输出为：

 ```bash
core file size              (blocks, -c) 0
 ```

显示为受限

## 2. 解除core文件大小限制：

 ```bash
 ulimit -c unlimited
 ```

输出为：

 ```bash
core file size              (blocks, -c) unlimited
 ```

显示为不限

 ## 3. 将core_dump文件重定向到工程目录，以下方法只在当前终端连接中有效

 ```bash
 echo "/workspace/CPP/String/core-%t-%p" > /proc/sys/kernel/core_pattern
 ```
%t和%p 用来防止重名

 ## 4. 在CMakelist.txt文件中设置为debug模式或者添加“-g”参数

 ```CMakeList
 set(CMAKE_BUILD_TYPE "Debug")
 add_definitions("-Wall -g")
 ```
## 5. 加载CMake工程
 ```bash
 cmake .
 ```
## 6. 编译工程
 ```bash
make
 ```
## 7. 运行目标文件
 ```bash
 ./build
 ```
## 8. gdb 查看core_dump报错信息
 ```bash
gdb build core-1675510529-84585
 ```

## 9. 使用bt命令可以查看程序core文件现场的调用栈

```bash
:~/test/core> gdb a.out -c a.dump
(gdb) bt
#0  0x0000000000000000 in ?? ()
#1  0x000000000040058f in register_tm_clones ()
#2  0x00000000004005b0 in register_tm_clones ()
#3  0x0000000000000000 in ?? ()
```

栈帧0明显是对空指针函数进行调用，导致内存访问出错。

## 10. `i r`可以查看寄存器，`x`可以查看内存空间，例如`x/20wx $sp`查看栈顶的20个WORD。

## 11. `info proc mappings`查看内存映射表。

## 12. 在arm程序中，由于压栈的寄存器不一致的问题，可能会导致gdb回溯调用栈失败,如下所示，此时需要结合汇编代码人工对调用栈进行回溯。

```bash
(gdb) bt
#0  0xf72e12a0 in pthread_rwlock_timedwrlock () from /lib/libpthread-2.22.so
Backtrace stopped: previous frame identical to this frame (corrupt stack?)
```

## 13. 交叉环境下的core dump

例如在Arm平台上执行的程序发生了core dump, 但是希望在x86平台的linux机器上对core文件进行调试, 则需要使用交叉环境的arm-linux-gdb，而不是x86的gdb。有两个选择：

1. 下载gdb源码，编译target为arm平台的arm-linux-gdb。
2. 下载预编译的arm-linux-gdb。这里提供一个网上的预编译好的gcc工具链[Linaro Releases](https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/arm-linux-gnueabi/).

