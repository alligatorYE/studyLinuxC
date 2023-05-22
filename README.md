# Linux C

## 嵌入式C语言高阶
### gcc的内容及其常用选项

gcc将人能力理解的高级语言（如C、c++）翻译成机器能理解的机器语言，最初的全称是**GUN C Compiler**

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

#### 使用gcc命令

```shell
gcc -v -o build 001.c
```
可以看到下面的信息：

```shell
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

第13行 `/usr/libexec/gcc/x86_64-redhat-linux/8/cc1 -quiet -v 001.c` 中的 `cc1 -quiet -v 001.c`

### 查看磁盘空间

```shell
df -h
```

### 清理删除了的文件

```shell
lsof | grep deleted
```

