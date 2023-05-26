# Linux进程控制

## 进程创建

### 获取进程标识

```c
#include<sys/types.h>
#include<unistd.h>

pid_getpid(void);		//返回:调用进程的进程ID
pid_getppid(void);		//返回：调用进程的父进程ID
uid_t getuid(void);		//返回：调用进程的实际用户ID
uid_geteuid(void);		//返回：调用进程的有效用户ID
uid_getgid(void);		//返回：调用进程的实际组ID
uid_getegid(void);		//返回：调用进程的有效组ID
```

### 进程创建

#### pid_t fork(void);

返回：子进程中为0，在父进程中为子进程的ID，出错为-1.

#### pid_t vfork(void);

返回：子进程中为0，在父进程中为子进程的ID，出错为-1.

区别：`fork()`不保证父进程和子进程哪一个先执行，而`vfork()`可以保证先执行子进程再执行父进程，`vfork()`主要用于`exec`函数的的时候

