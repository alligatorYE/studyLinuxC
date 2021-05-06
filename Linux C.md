# Linux C

## 嵌入式C语言高阶
### gcc的内容及其常用选项

gcc将人能理解的高级语言（如C、c++）翻译成机器能理解的机器语言，最初的全称是**GUN C Compiler**

随着GCC支持的语言越来越多，它的名称变成了**GUN Compiler Collection** ，就像一个翻译组织，他有很多成员，我们要找到相应的成员帮我们进行语言的翻译。

#### 命令格式

```shell
gcc -o output
#gcc -0 输出的文件名 输入的文件名
```

```shell
gcc -o build 001.c
```

输出的文件名不用加后缀，与Windows中加`.exe` 不同



### c语言编译过程

##### 预处理
```shell 
cpp -o a.i 001.c #先将001.c 翻译成 a.i 以便后面把a.i 翻译成a.s
```
等价于**`gcc -E`**

##### 使用gcc命令

```shell
gcc -v -o build 001.c

​```shell
可以看到下面的信息：

​```shell
[root@VM-0-3-centos c]# vim 001.c
[root@VM-0-3-centos c]# gcc -v -o build 001.c
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/libexec/gcc/x86_64-redhat-linux/8/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-redhat-linux
Configured with: ../configure --enable-bootstrap --enable-languages=c,c++,fortran,lto --prefix=/usr --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=http://bugzilla.redhat.com/bugzilla --enable-shared --enable-threads=posix --enable-checking=release --enable-multilib --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-gnu-unique-object --enable-linker-build-id --with-gcc-major-version-only --with-linker-hash-style=gnu --enable-plugin --enable-initfini-array --with-isl --disable-libmpx --enable-offload-targets=nvptx-none --without-cuda-driver --enable-gnu-indirect-function --enable-cet --with-tune=generic --with-arch_32=x86-64 --build=x86_64-redhat-linux
Thread model: posix
gcc version 8.3.1 20191121 (Red Hat 8.3.1-5) (GCC)
COLLECT_GCC_OPTIONS='-v' '-o' 'build' '-mtune=generic' '-march=x86-64'
 /usr/libexec/gcc/x86_64-redhat-linux/8/cc1 -quiet -v 001.c -quiet -dumpbase 001.c -mtune=generic -march=x86-64 -auxbase 001 -version -o /tmp/ccnUPurh.s
GNU C17 (GCC) version 8.3.1 20191121 (Red Hat 8.3.1-5) (x86_64-redhat-linux)
        compiled by GNU C version 8.3.1 20191121 (Red Hat 8.3.1-5), GMP version 6.1.2, MPFR version 3.1.6-p2, MPC version 1.0.2, isl version isl-0.16.1-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
ignoring nonexistent directory "/usr/lib/gcc/x86_64-redhat-linux/8/include-fixed"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-redhat-linux/8/../../../../x86_64-redhat-linux/include"
#include "..." search starts here:
#include <...> search starts here:
 /usr/lib/gcc/x86_64-redhat-linux/8/include
 /usr/local/include
 /usr/include
End of search list.
GNU C17 (GCC) version 8.3.1 20191121 (Red Hat 8.3.1-5) (x86_64-redhat-linux)
        compiled by GNU C version 8.3.1 20191121 (Red Hat 8.3.1-5), GMP version 6.1.2, MPFR version 3.1.6-p2, MPC version 1.0.2, isl version isl-0.16.1-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
Compiler executable checksum: b4c753e942ce676d6a1adf00f0b0ee6d
COLLECT_GCC_OPTIONS='-v' '-o' 'build' '-mtune=generic' '-march=x86-64'
 as -v --64 -o /tmp/ccVYmI9C.o /tmp/ccnUPurh.s
GNU assembler version 2.30 (x86_64-redhat-linux) using BFD version version 2.30-49.el8
COMPILER_PATH=/usr/libexec/gcc/x86_64-redhat-linux/8/:/usr/libexec/gcc/x86_64-redhat-linux/8/:/usr/libexec/gcc/x86_64-redhat-linux/:/usr/lib/gcc/x86_64-redhat-linux/8/:/usr/lib/gcc/x86_64-redhat-linux/
LIBRARY_PATH=/usr/lib/gcc/x86_64-redhat-linux/8/:/usr/lib/gcc/x86_64-redhat-linux/8/../../../../lib64/:/lib/../lib64/:/usr/lib/../lib64/:/usr/lib/gcc/x86_64-redhat-linux/8/../../../:/lib/:/usr/lib/
COLLECT_GCC_OPTIONS='-v' '-o' 'build' '-mtune=generic' '-march=x86-64'
 /usr/libexec/gcc/x86_64-redhat-linux/8/collect2 -plugin /usr/libexec/gcc/x86_64-redhat-linux/8/liblto_plugin.so -plugin-opt=/usr/libexec/gcc/x86_64-redhat-linux/8/lto-wrapper -plugin-opt=-fresolution=/tmp/ccvFA60Y.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --no-add-needed --eh-frame-hdr --hash-style=gnu -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o build /usr/lib/gcc/x86_64-redhat-linux/8/../../../../lib64/crt1.o /usr/lib/gcc/x86_64-redhat-linux/8/../../../../lib64/crti.o /usr/lib/gcc/x86_64-redhat-linux/8/crtbegin.o -L/usr/lib/gcc/x86_64-redhat-linux/8 -L/usr/lib/gcc/x86_64-redhat-linux/8/../../../../lib64 -L/lib/../lib64 -L/usr/lib/../lib64 -L/usr/lib/gcc/x86_64-redhat-linux/8/../../.. /tmp/ccVYmI9C.o -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-redhat-linux/8/crtend.o /usr/lib/gcc/x86_64-redhat-linux/8/../../../../lib64/crtn.o
COLLECT_GCC_OPTIONS='-v' '-o' 'build' '-mtune=generic' '-march=x86-64'
[root@VM-0-3-centos c]#

```
##### 编译
第13行中的 `/usr/libexec/gcc/x86_64-redhat-linux/8/cc1 -quiet -v 001.c`（`cc1 -o *.s 001.c` ）等价于**`gcc -S`**
##### 汇编

`as -o a.o a.s` <=> **`gcc -c`**

### C语言预处理

`#define`  宏	替换，不进行语法检查

习惯

```c
#define 宏名 宏体 #保持对宏体加括号的习惯
```

示例：

```c
#define	ABC (5+3)
#define ABC(x)	(5+(x))
```

```c
#ifdef
#else
#endif
```



##### 系统定义宏

```c
__FUNCTION__ //函数名
__LINE__ //行号
__FILE__ // 文件名
```

示例：

```c
#include<stdio.h>

int main(int argc, char* argv[])
 {
    printf("the %s,%s,%d\n",__FUNCTION__,__FILE__,__LINE__);

    return 0;
 }


```

编译后输出：

```shell
[root@VM-0-3-centos c]# gcc -o build 002.c
[root@VM-0-3-centos c]# ./build
the main,002.c,5
```

打印出了，所在的函数，所在的文件，所在的行号

条件与处理举例：**调试版** **发行版**

```c
#include<stdio.h>

int main(int argc, char* argv[])
 {
#ifdef DEBUG
    printf("the %s,%s,%d\n",__FUNCTION__,__FILE__,__LINE__);
#endif
    return 0;
 }
```
编译时，加上`-D` 再加上DEBUG，才能能看到DEBUG信息
```shell
gcc -DDEBUG -o build3 003.c
```

### 宏展开下的 \# 、##使用

\#      作用是**字符串化**

\##	作用是**连接符号**

```c
#include <stdio.h>
#define ABC(x) #x
#define DAY(x) myDay##x //给x加一个前缀
int main()
{
    int myDay1 = 10;
    int myDay2 = 20;
    printf(ABC(x\n));//将打印  ab
    printf("the day is %d\n",DAY(1)); //将打印	the day is 10
    printf("the day is %d\n",DAY(2)); //将打印	the day is 20
}
```

### C语言常用关键字及运算符

> how to do？
>
> when to do?
>
> why to do?

C语言32关键字

`sizeof();`是关键字，不是函数

#### 数据类型关键字

> char
>
> int
>
> short、long
>
> unsinged、signed
>
> float、double
>
> void

C语言的操作对象:资源/内存【内存类型的资源，LCD缓存、LED灯】

C语言如何描述这些资源的属性呢？

> 限制内存（土地）的大小，关键字

##### char类型

硬件芯片操作的最小单位：

> bit 	1	0

软件操作的最小单位：

> 8bit == 1Byte

char 的应用场景：

> 硬件处理的最小单位

```c
char buf[xx];
int buf[x];
```

char 是1Byte，而int是2Byte或者4Byte

显然应该用char来定义buffer

##### int、 long、 short

> 8bit == 256 
>
> char a =300; 将产生溢出 

编译器最优的处理大小：

> 系统一个周期所能接受的最大处理单位，int
>
> 64bit	8Byte	int
>
> 32bit	4Byte	int
>
> 16bit	2Byte	int

int的大小其实是不固定的，最终大小由编译器来决定

> int a;

如果说变量a只进行一些数据的处理用`int`肯定比char合理

##### signed、usigned

无符号：数据

有符号：数字

内存空间的最高字节是**符号位** 还是 **数据位**

右移操作：`>>`

```C
char a = -1; //实际上是0xff
a>>1;
```

有符号数，因为有最高位的**符号位**存在，不管右移操作多少次，都无法变为0；

```c
unsigned char b = 0xff;
b>>1; 
```

无符号数，最高位是数据为，8次右移操作后就会变为0；

##### float、double

> float 	4Byte
>
> double	8Byte

> 浮点数、整数

> 内存存在形式
>
> 0x10			16
>
> 0001 0000	16

浮点型常量

> 1.0 1.1 double	8Byte
>
> 1.0f	float			4Byte

小数不加f处理为double，占8个字节空间，在小数后面加上`f`后处理为float类型，占4个字节空间

#### 自定义数据类型struct、union

> 自定义 == 基本元素的集合

C语言默认定义的资源分配不符合实际资源的形式

##### 结构体

**struct **大小是结构体中各元素大小的和

```c
struct myABC{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
};
```

##### 共用体

**union** 共用起始地址的一段内存

 共用体其实就是共用大家的起始地址，如果先定义了一个较小的类型，后面又定义了一个较大的类型，那么后面定义的类型会覆盖前面类型的空间大小（并不是物理上的覆盖）；

#### 自定义数据类型**enum**

枚举类型

```c
enum week{
    Monday = 0,Tuesday = 1,Wednesday = 2,
    Thursday, Friday,
    Saturday, SUnday    
};
```

`enum 枚举名称 {常量列表};`

可以用#define替代，但是方便程序的阅读，程序设计人员交流。

#### typedef

取别名

int a;	a是一个int类型的变量

typedef int a；a是一个int类型的外号

#### 逻辑关键字

#### 类型修饰符

对内存资源存放位置的限定

资源属性中位置的限定

>auto
>
>register
>
>static
>
>const
>
>extern
>
>volatile

##### auto

> auto是一种默认情况→分配的内存都是可读可写的区域

```c
auto char a;//默认情况可以不加auto，变量存放在普通内存区域，可读可写
```

如果放在花括弧中：

```c
{
    auto char a;//变量将存放在栈空间中，也是可读可写的
}
```

##### register

> 限制变量定义在寄存器上的修饰符

```c
int a;//等价于 auto int a;
register int a;//编译器会尽量的安排CPU的寄存器去存放这个变量a,如果寄存器不足时，a还是存放在存储器中。
```

> 内存（存储器）：比如电脑的内存条，访问速度相对于寄存器很慢
>
> 寄存器：在CPU上，CPU直接访问效率非常的高，比内存更高

取地址符号`&`对register修饰的变量是不起作用的

##### static

应用场景：

修饰3种数据：

###### 1.函数内部的变量

```c
int fun()
{
    int a;//==>static int a;
}
```

###### 2.函数外部的变量

```c
int a;//==>static int a;
int fun()
{
    
}
```

###### 3.函数的修饰符

```c
static int fun()
{
    
}
```
> 关于static的三种应用场景，将在内存架构中详细分析

##### const

常量的定义

只读的变量

##### volatile

告知编译器编译方法的关键字，不优化编译

```c
int a = 100;
while (a==10);
myLCD();
```

```ASM
[a]: a的地址

f1:LDR R0, [a]
f2:CMP R0, #100
f3:JMPEQ f1 		--->a不加volatile 编译器将优化为: JMPEQ f2
f4:myLCD();
```

#### 运算符

> 算术操作运算
>
> 逻辑运算
>
> 赋值运算
>
> 内存访问符号

##### +、 -

\+ 两边一般是同种数据类型，所以一般尽量保持左右两边的类型一致

##### \*、/

> \*和/ 在C语言种，或者说在大部分的CPU中是不支持的

```c
int a = b*10;	//CPU可能需要多个周期，甚至需要利用软件的模拟方法去实现乘法
```

```c
int a = b + 10;	//CPU一个周期就可以处理
```

##### % 求模

###### 应用场景

1. 取一个范围的数：取一个1~100的任意数

```c
m % 100; //得到一个0~99的数，再加上1，就得到1~100的数
(m%100)+1 ==>res;
```

 2. 得到M进制的个位数，比如上面的M=100

3. 循环数据结构的下标


#### 逻辑运算符

A||B

A&&B

A、B的位置交换与之前的表达式不是等价的

#### 位运算符

##### 移位运算符

###### 左移: << 			每左移一位相当于乘以2

乘法，*2，二进制下的移位

```c
m << 1; m*2
```

```c
m << n; m*2^n 左移n位，相当于乘以了2的n次方
```

> 4:	0010
>
> 8:	0100

```c
int a = b * 32; //编译器会翻译成 b<<5;CPU一个周期就可以处理完成了，所以平时编程尽量使用2的倍数
```

> 数据	数字

> -1*2 → -2
>
> 8bit
>
> 1000 0001	最高位为符号位 1为负数，0为正数
>
> 1111 1110	对数据为取反
>
> 1111 1111	然后加1，这才是-1在计算机内存中的表示方式，-1的表示其实是在内存中全高电平

>	-1						-2
>
>1000 0001		1000 0010
>
>1111 1110		  1111 1101		分别对每位取反
>
>1111 1111		  1111 1110		-1左移一位，并不会出现符号位的问题，左移末位补零，符号位仍然是1

###### 右移： >>			每右移一位相当于除以2

右移操作符一定要注意符号位,养成使用`unsigned`关键字的习惯

```c
unsigned int a;
a >> n;
```

如果a是有符号数:

```c
int a;
a >> n;//在右移的时候，如果a是负数符号位填的是“1”，如果这个数原来是正数的时候，符号位将填“0”
```

注意，当a为负数的时候，由于符号位永远是“1”，所以右移不能得到0，

#### & 、| 、^  与，同或，异或

A&0→0

&：屏蔽

```c
int a = 0x1234;
a & 0xff00; → 0x1200 屏蔽低8bit，取出高8bit
```

A&1→A	取出

&：取出

&：清零器 `clr`

A|0 →A

|：保留

A|1 → 1

设置为高电平的方法

|：设置器 `set`

> 设置一个资源的bit5（第0位：bit0、第1位：bit1···第5位：bit5）为高，其他位不变

```c
int a;
a=(a|(0x1<<5));// →a|(0x1<<n)
```

> 清除第五位

```c
int a;
a=a&~(0x1<<5);//→ &(~(0x1<<n)),清除第n位，先左移n位，再取反，再和a相与，完成清除
```

###### 异或和取反（^、~）

>三次异或完成数值交换

```c
a = a^b;
b = a^b;
a = a^b;
```

##### "→"和“.”

如果定义如下：
A *p则使用：p->play(); 左边是结构指针。
A p 则使用：p.paly(); 左边是结构变量。
总结：
箭头（->）：左边必须为指针；
点号（.）：左边必须为实体。

## C语言内存空间

### 指针

可以理解为内存类型资源的地址、门牌号的代名词

> C语言编译器对指针这个特殊的概念，有两个疑问：
>
> 1. 分配一个盒子要多大呢？ 
>
>    ​	在32位系统中，指针就4个字节，在64位系统中，指针就是8个字节，跟指向什么类型没有关系。
>
> 2. 盒子里存放的地址 所指向 内存的读取方法是什么？一次读多少字节呢？
>
>    ​	int *p 	int类型告诉编译器，一次读4个字节
>
>    ​	char *p   char类型告诉编译器，一次读1个字节

指针指向的内存空间一定要保证合法性，不能指向非法地址，无权访问的地址。

一般出现段错误( segmentation fault )，就跟指针指向非法内存地址有关

> 关于占位符
>
>  1、%d 为整数占位符，10进制表示，默认有符号，占4字节
>
> 2、%u 为整数占位符，10进制表示，无符号表示，最高位算作值的一部分
>
> 3、%o 为整数占位符，8进制表示
>
> 4、%x 为整数占位符， 16进制表示
>
> 5、%f为浮点数占位符
>
> 6、%s为字符串占位符
>
> 7、%c为字符占位符

```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a = 12, b = -20; // 默认10进制赋值
    char *str = "jack";
    // 1、%d 为整数占位符，10进制表示，默认有符号，占4字节
    printf("a + b = %d\n", a + b);
    // 2、%u 为整数占位符，10进制表示，无符号表示，最高位算作值的一部分
    printf("无符号打印b = %u\n", b);
    // 3、%o 为整数占位符，8进制表示
    printf("a = %d, 8进制为 %o\n", a, a);
    // 4、%x 为整数占位符， 16进制表示
    printf("a = %d, 16进制为 %x\n", a, a);
    float c = 12.5, d = 3.14;
    // 5、%f为浮点数占位符
    printf("c + d = %f\n", c + d);\
    // 6、%s为字符串占位符
    printf("Hello, %s\n", str);
    // 7、%c为字符占位符
    char a = 'a';
    char b = 97;
    printf("a = %c, b = %c\n", a, b);

    int e = 0123; // 0开头，8进制赋值
    int f = 0x1ab; // 0x开头，16进制赋值
    printf("e = [10]%d, [8]%o, [16]%x\n", e, e, e);
    printf("f = [10]%d, [8]%o, [16]%x\n", f, f, f);

    return 0;
}
```

### const

> char *p;


p可以指向任意的只读空间，也就是拍的指向可以变，但是必须指向只读空间
> const char *p;// 两种方式意义相同，推荐把第一种，把const 放在类型前面
> char const *p;

p的指向不能改变，只能指向固定的空间，但是这个固定空间中的内容可以不断的刷新，比如LCD、显卡等硬件资源
> char* const  p;//两种方式意义相同，推荐第一种
> char *p const;

p的指向不能改变，并且只能指向只读空间，比如ROM

> const char * const p;

```shell
[root@VM-0-3-centos c]# cat 006.c
#include<stdio.h>

int main(int argc, char* argv[])
{
    char *p = "hello world";
    char buf[] = {"hello world"};
    char *p2 = buf;
    printf("the one is %x\n",*p);
    *p2 = 'a';
    printf("the %s\n",p2);
}
[root@VM-0-3-centos c]# ./build
the one is 68
the aello world
```

### volatile

防止编译器优化指向内存地址

```c
char *p;
while(*p == 0x10);//被编译器优化后，将有可能进入死循环

volatile char *p1;
*p1 == 0x10;
```

### typedef

取别名

```c 
char* name_t; // name_t 是一个char型的指针，指向了一个char型的内存
```

```c
typedef char* name_t; // name_t 是一个指针类型的名称，指向了一个char型的内存
name_t abc; //后面可以直接用来定义这种类型的变量
```

### 指针运算符

#### ++、--、+、-

```c
int *p = xxx [0x12]
p+1		[0x12 + 1*sizeof(*p)]
```

指针的加法、减法运算，实际上加的是一个单位，单位的大小可以使用`sizeof(p[0])`

> int *p	p+1
>
> char *p  p+1
>
> 以上两个p+1得到的是完全不同的

##### p++、p--  更新地址

`p++`和`p--`与p+1、p-1是不同的，p++、p--带有更新的思想，会改变p自身的值，而p+1、p-1是不改变p的值的

#### []	方括号

变量名[n] 

n:ID 标签

地址内容的标签访问方式，非线性的，跳跃式访问，p[0]、p[5]，不需要一个一个的移动指针，

`p[n]`得到的是内容，p+n得到的是地址

指针越界访问

指针逻辑运算符操作

#### 逻辑操作符

```c
int *p1;
int *p2;
p1 > p2;
*p1 > *p2;
```

1. 跟一个特殊值进行比较(==、!=)	0x0:地址的无效值，结束标志

   ​	if （p == 0x0）

   ​		NULL

2. 指针必须是同类型的比较才有意义

   ​	char*

   ​		int*

#### 多级指针

存放地址的地址空间

不管是多少级指针，最终的实质还是存放地址的盒子，只是盒子里的内容可能又是指针

![image-20210505215726581](..\studyLinuxC\imgs\image-20210505215726581.png)

通过多级指针，在没有关系的变量中间建立线性关系。

多级指针更多的是描述内存与内存之间的线性关系

![image-20210505222955911](..\studyLinuxC\imgs\image-20210505222955911.png)

### 数组的定义及初始化

数组任然是一种内存分配形式

定义一个空间：

1. 大小

2. 读取方式

   `数据类型 数组名[m]`	在右方，通过方括号将数组空间申请为连续的空间, 有m个这样的空间，m的作用域只在申请的时候起作用

注意：数组名是一个常量符号，一定不要放到“=”的左边，错误示例：

> char buf[100]; 
>
> buf = "hello world";

