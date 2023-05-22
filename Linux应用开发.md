# Linux应用开发

## IO系统编程

>应用层 ——C/C++、Java、数据结构、Android、Linux命令
>
>-----------------Linux下的高级编程，应用层与内核层之间的过渡层（或者称之为内核提供给用户的接口层）----------
>
>内核层
>
>硬件层

```c
[root@VM-0-3-centos iotest]# cat 001.c
#include<unistd.h>

#include<stdio.h>

int main(int argc,char* argv[])
{
    //printf("%d",sizeof("hello linux\n"));
    write(1,"hello linux\r\n",13);
    return 0;
}
[root@VM-0-3-centos iotest]#
[root@VM-0-3-centos iotest]# ./build
hello linux
```



## 进程间通信

## 多线程编程

## 网络编程

**客户端**-----------------通信连接----------------------------**服务器端**

局域网拓补

![image-20210509080507155](..\Alligator\imgs\image-20210509080507155.png)

广域网拓补

![image-20210509080718224](..\Alligator\imgs\image-20210509080718224.png)

### TCP 传输控制协议

向用户进程提供可靠的全双工字节流。可靠的：面向连接的

### UDP用户数据报协议

UDP 是一种无连接的协议

![image-20210509082728822](..\Alligator\imgs\image-20210509082728822.png)

1. 绑定众所周知的IPv4地址（INADDR_ANY）和端口号（8888）
2. 将套接字转换成监听套接字
3. 睡眠等待客户端连接
4. 读取客户端数据

![image-20210509093005333](..\Alligator\imgs\image-20210509093005333.png)

