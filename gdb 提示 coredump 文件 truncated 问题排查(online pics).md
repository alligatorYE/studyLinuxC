# gdb 提示 coredump 文件 truncated 问题排查


> 本文选自“字节跳动基础架构实践”系列文章。
>
> “字节跳动基础架构实践”系列文章是由字节跳动基础架构部门各技术团队及专家倾力打造的技术干货内容，和大家分享团队在基础架构发展和演进过程中的实践经验与教训，与各位技术同学一起交流成长。
>
> 
>
> coredump 我们日常开发中经常会遇到，能够帮助我们辅助定位问题，但如果 coredump 出现 truncate 会给排查问题带来不便。本文以线上问题为例，借助这个Case我们深入了解一下这类问题的排查思路，以及如何使用一些调试工具、阅读内核源代码，更清晰地了解coredump的处理过程。希望能为大家在排查这类问题的时候，提供一个清晰的脉络。

# 问题背景

在 c/cpp 类的程序开发中进程遇到 coredump，偶尔会遇到 coredump truncate 问题，影响 core 后的问题排查。coredump truncate 大部分是由于 core limits 和剩余磁盘空间引发的。这种比较好排查和解决。今天我们要分析的一种特殊的 case。

借助这个 Case 我们深入了解一下这类问题的排查思路，使用一些调试工具和阅读内核源代码能更清晰的了解 coredump 的处理过程。能够在排查这类问题的时候有个清晰的脉络。

业务同学反馈在容器内的服务出 core 后 gdb 调试报错。业务的服务运行在 K8S+Docker 的环境下，服务在容器内最终由 system 托管。在部分机器上的 coredump 文件在 gdb 的时候出现如下警告，导致排查问题受影响。报错信息如下：


```bash
BFD: Warning: /tmp/coredump.1582242674.3907019.dp-b9870a84ea-867bccccdd-5hb7h is truncated: expected core file size >= 89036038144, found: 31395205120.
```

导致的结果是 gdb 无法继续调试。我们登录机器后排查不是磁盘空间和 core ulimit 的问题。需要进一步排查。

# 名词约定

**GDB**：UNIX 及 UNIX-like 下的二进制调试工具。

**Coredump：** 核心转储，是操作系统在进程收到某些信号而终止运行时，将此时进程地址空间的内容以及有关进程状态的其他信息写出的一个磁盘文件。这种信息往往用于调试。

**ELF：** 可执行与可链接格式（Executable and Linkable Format），用于可执行文件、目标文件、共享库和核心转储的标准文件格式。x86 架构上的类 Unix 操作系统的二进制文件格式标准。

**BFD：** 二进制文件描述库(Binary File Descriptor library)是 GNU 项目用于解决不同格式的目标文件的可移植性的主要机制。

**VMA：** 虚拟内存区域（Virtual Memory Area），VMA 是用户进程里的一段 virtual address space 区块，内核使用 VMA 来跟踪进程的内存映射。

# 排查过程

## 用户态排查

开始怀疑是自研的 coredump handler 程序有问题。于是还原系统原本的 coredump。![图片](https://mmbiz.qpic.cn/mmbiz_png/5EcwYhllQOjNa58ZAjdfciaF8ia3z1gHKKkTa3FNGK7cExicgwdtEib4msfg5ebI5wRcuFYm3z7tkfAStNM2OeozEw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

手动触发一次 Coredump。结果问题依然存在。现在排除 coredump handler 的问题。说明问题可能发生在 kernel 层或 gdb 的问题。

需要确定是 gdb 问题还是 kernel 吐 core 的问题。先从 gdb 开始查起，下载 gdb 的源代码找到报错的位置（为了方便阅读，源代码的缩进进行了调整）。

![图片](https://mmbiz.qpic.cn/mmbiz_png/5EcwYhllQOjNa58ZAjdfciaF8ia3z1gHKKQTbR5R0uRWibeGy8OlSBDTXTg4wbmVZIHUM6hIgELMLZXx7ibicyUON7w/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

目前看不是 gdb 的问题。coredump 文件写入不完整。coredump 的写入是由内核完成的。需要从内核侧排查。

在排查之前观察这个 coredump 的程序使用的内存使用非常大，几十 G 规模。怀疑是否和其过大有关，于是做一个实验。写一个 50G 内存的程序模拟，并对其 coredump。


```c
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void){
        for( int i=0; i<1024; i++ ){
                void* test = malloc(1024*1024*50); // 50MB
                memset(test, 0, 1);
        }
        sleep(3600);
}
```

经过测试正常吐 core。gdb 正常，暂时排除 core 大体积问题。

所以初步判断是 kernel 在吐的 core 文件自身的问题。需要在进一步跟进。

查看内核代码发现一处可疑点:


```C
/*
 * Ensures that file size is big enough to contain the current file
 * postion. This prevents gdb from complaining about a truncated file
 * if the last "write" to the file was dump_skip.
 */
void dump_truncate(struct coredump_params *cprm)
{
    struct file *file = cprm->file;
    loff_t offset;

    if (file->f_op->llseek && file->f_op->llseek != no_llseek) {
        offset = file->f_op->llseek(file, 0, SEEK_CUR);
        if (i_size_read(file->f_mapping->host) < offset)
            do_truncate(file->f_path.dentry, offset, 0, file);
    }
}
```

这段代码的注释引起了我们的注意。

![图片](https://mmbiz.qpic.cn/mmbiz_png/5EcwYhllQOjNa58ZAjdfciaF8ia3z1gHKKPsx3M6QcUWfJYO3SWLI2LcuUHm3hdCpFmeickNrgjZFnh8FibibQIsfQA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

现在怀疑在出现这个 case 的时候没有执行到这个 dump_truncate 函数。于是尝试把 dump_truncate 移到第二个位置处。重新编译内核尝试。重新打了测试内核测试后问题依然存在。于是继续看代码。

![图片](https://mmbiz.qpic.cn/mmbiz_png/5EcwYhllQOjNa58ZAjdfciaF8ia3z1gHKKShvia35vrqgZo88foEm8PicWS96tgKm3l9zSp54bMLAibDEcl6j4fy9Xw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

这段代码引起了注意。怀疑某个时刻执行 get_dump_page 的时候返回了 NULL。然后走到了 dump_skip 函数，dump_skip 返回 0，导致 goto end_coredump。于是 stap 抓下。

不出所料，dump_skip 返回 0 后 coredump 停止。**也就是说第二阶段只 dump 了一部分 vma 就停止了。**导致 coredump 写入不完整。

# VMA 部分 dump 分析

再看下 dump_skip 函数。



```c
int dump_skip(struct coredump_params *cprm, size_t nr)
{
    static char zeroes[PAGE_SIZE];
    struct file *file = cprm->file;
    if (file->f_op->llseek && file->f_op->llseek != no_llseek) {
        if (dump_interrupted() ||
            file->f_op->llseek(file, nr, SEEK_CUR) < 0)
            return 0;
        cprm->pos += nr;
        return 1;
    } else {
        while (nr > PAGE_SIZE) {
            if (!dump_emit(cprm, zeroes, PAGE_SIZE))
                return 0;
            nr -= PAGE_SIZE;
        }
        return dump_emit(cprm, zeroes, nr);
    }
}
```

因为 coredump 是 pipe 的，所以是没有 llseek 操作的，因此会走到 else 分支里。也就是 dump_emit 返回 0 导致的。于是 stap 抓下 dump_emit 函数 。

![图片](https://mmbiz.qpic.cn/mmbiz_png/5EcwYhllQOjNa58ZAjdfciaF8ia3z1gHKKH4icCGHvtLutcJxEPN1uaILlFeico77UzZ4AWcxYbAfxHHibZYfHOYT4Q/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)



```go
function func:string(task:long)
%{
    snprintf(STAP_RETVALUE, MAXSTRINGLEN, "%s", signal_pending(current) ? "true" : "false");
%}

probe kernel.function("dump_emit").return
{
    printf("return: %d, cprm->limit:%d, cprm->written: %d, signal: %s\n", $return, @entry($cprm->limit), @entry($cprm->written), func($return));
}
```

结果如下：


```bash
return: 1, cprm->limit:-1, cprm->written: 0, signal: false
return: 1, cprm->limit:-1, cprm->written: 64, signal: false
return: 1, cprm->limit:-1, cprm->written: 120, signal: false
... 省略9221238行 ...
return: 1, cprm->limit:-1, cprm->written: 37623402496, signal: false
return: 1, cprm->limit:-1, cprm->written: 37623406592, signal: false
return: 1, cprm->limit:-1, cprm->written: 37623410688, signal: false
return: 0, cprm->limit:-1, cprm->written: 37623414784, signal: true
```

不出意外和怀疑的一致，dump_emit 返回 0 了，此时写入到 core 文件的有 37623414784 字节。主要因为 dump_interrupted 检测条件为真。(cprm->limit = -1 不会进入 if 逻辑，kernrel_wirte 写 pipe 也没有出错)。

下面我们看 dump_interrupted 函数。为了方便阅读，整理出相关的函数。



```c
static bool dump_interrupted(void){
    /*
     * SIGKILL or freezing() interrupt the coredumping. Perhaps we
     * can do try_to_freeze() and check __fatal_signal_pending(),
     * but then we need to teach dump_write() to restart and clear
     * TIF_SIGPENDING.
     */
    return signal_pending(current);
}

static inline int signal_pending(struct task_struct *p){
    return unlikely(test_tsk_thread_flag(p,TIF_SIGPENDING));
}
static inline int test_tsk_thread_flag(struct task_struct *tsk, int flag){
    return test_ti_thread_flag(task_thread_info(tsk), flag);
}
static inline int test_ti_thread_flag(struct thread_info *ti, int flag){
    return test_bit(flag, (unsigned long *)&ti->flags);
}

/**
 * test_bit - Determine whether a bit is set
 * @nr: bit number to test
 * @addr: Address to start counting from
 */
static inline int test_bit(int nr, const volatile unsigned long *addr){
    return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}
```

相关的宏：

```c
#ifdef CONFIG_64BIT
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif /* CONFIG_64BIT */
#define TIF_SIGPENDING      2   /* signal pending */ 平台相关。以X64架构为例。
```

有上面的代码就很清楚 dump_interrupted 函数就是检测 task 的 thread_info->flags 是否 TIF_SIGPENDING 置位。

目前怀疑还是和用户的内存 vma 有关。但什么场景会触发 TIF_SIGPENDING 置位是个问题。dump_interrupted 函数的注释中已经说明了，一个是接收到了 KILL 信号，一个是 freezing()。freezing()一般和 cgroup 有关，一般是 docker 在使用。KILL 有可能是 systemd 发出的。于是做了 2 个实验：

#### 实验一：



> 1. systemd启动实例，bash裸起服务，不接流量。
> 2. 测试结果gdb正常...
> 3. 然后再用systemd起来，不接流量。测试结果也是正常的。
> 4. 这就奇怪了。但是不能排除systemd。
> 5. 回想接流量和不接流量的区别是coredump的压缩后的体积大小不同，不接流量vma大都是空，空洞比较多，因此coredump非常快，有流量vma不是空的，coredump比较慢。因此怀疑和coredump时间有关系，超过某个时间就有TIF_SIGPENDING被置位。


#### 实验二：




> 1. 是产生一个50G的内存。
> 2. 代码如最上方。在容器内依然使用systemd启动一个测试程序（直接在问题容器内替换这个bin。然后systemctl重启服务）
> 3. 然后发送SEGV信号。stap抓一下。
> 4. coredump很漫长。等待结果结果很意外。core正常，gdb也正常。


这个 TIF_SIGPENDING 信号源是个问题。

还有个排查方向就是 get_dump_page 为啥会返回 NULL。所以现在有 2 个排查方向：

1. 需要确定 TIF_SIGPENDING 信号源。
2. get_dump_page 返回 NULL 的原因。

# get_dump_page 返回 NULL 分析

首先看 get_dump_page 这个返回 NULL 的 case：

```bash
* Returns NULL on any kind of failure - a hole must then be inserted into * the corefile, to preserve alignment with its headers; and also returns * NULL wherever the ZERO_PAGE, or an anonymous pte_none, has been found - * allowing a hole to be left in the corefile to save diskspace.
```

看注释返回 NULL，一个是 page 是 ZERO_PAGE，一个是 pte_none 问题。

首先看 ZREO 问题，于是构造一个 ZERO_PAGE 的程序来测试：


```C
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

const int BUFFER_SIZE = 4096 * 1000;
int main(void){
    int i = 0;
    unsigned char* buffer;
    for( int n=0; n<10240; n++ ){
        buffer = mmap(NULL, BUFFER_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
        for (i = 0; i < BUFFER_SIZE - 3 * 4096; i += 4096){
            buffer[i] = 0;
        }
    }
    // zero page
    for (i=0; i < BUFFER_SIZE - 4096; i += 4096) {
        char dirty = buffer[i];
        printf("%c", dirty);
    }
    printf("ok...\n");

    sleep(3600);
}
```

测试结果是 coredump 正常，同时 trace 一下 get_dump_page 的返回值。结果和预想的有些不同，返回了很多个 NULL。说明和 get_dump_page 函数的因素不大。

于是转向到 TIF_SIGPENDING 信号发生源。

# TIF_SIGPENDING 信号来源分析

bpftrace 抓一下看看：

- 
- 
- 
- 
- 
- 
- 
- 
- 
- 

```c
#!/usr/bin/env bpftrace
#include <linux/sched.h>

kprobe:__send_signal
{
        $t = (struct task_struct *)arg2;
        if ($t->pid == $1) {
                printf("comm:%s(pid: %d) send sig: %d to %s\n", comm, pid, arg0, $t->comm);
        }
}
```

结果如下：

![图片](https://mmbiz.qpic.cn/mmbiz_png/5EcwYhllQOjNa58ZAjdfciaF8ia3z1gHKKsLp9IFRUOELbwdvGCrzb8xbiaGv3dMxpk8QVAWyn65MfkiaqUvN9xyUQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

结果比较有趣。kill 和 systemd 打断了 coredump 进程。信号 2(SIGINT)和信号 9(SIGKILL)都足以打断进程。现在问题变为 kill 和 systemd 为什么会发送这 2 个信号。一个怀疑是超时。coredump 进程为 not running 太久会不会触发 systemd 什么机制呢。

于是查看了 systemd service 的 doc 发现这样一段话：

> TimeoutAbortSec=
> This option configures the time to wait for the service to terminate when it was aborted due to a watchdog timeout (see WatchdogSec=). **If the service has a short TimeoutStopSec= this option can be used to give the system more time to write a core dump of the service.** **Upon expiration the service will be forcibly terminated by SIGKILL (see KillMode= in systemd.kill(5)). The core file will be truncated in this case.** Use TimeoutAbortSec= to set a sensible timeout for the core dumping per service that is large enough to write all expected data while also being short enough to handle the service failure in due time.
>
> Takes a unit-less value in seconds, or a time span value such as "5min 20s". Pass an empty value to skip the dedicated watchdog abort timeout handling and fall back TimeoutStopSec=. Pass "infinity" to disable the timeout logic. Defaults to DefaultTimeoutAbortSec= from the manager configuration file (see systemd-system.conf(5)).
>
> If a service of Type=notify handles SIGABRT itself (instead of relying on the kernel to write a core dump) it can send "EXTEND_TIMEOUT_USEC=…" to extended the abort time beyond TimeoutAbortSec=. The first receipt of this message must occur before TimeoutAbortSec= is exceeded, and once the abort time has exended beyond TimeoutAbortSec=, the service manager will allow the service to continue to abort, provided the service repeats "EXTEND_TIMEOUT_USEC=…" within the interval specified, or terminates itself (see sd_notify(3)).

标红的字引起了注意，于是调大一下(TimeoutAbortSec="10min") 再试。无效...

无效后就很奇怪，难道 system 都不是信号的发起者，是信号的"传递者"? 现在有 2 个怀疑，一个是 systemd 是信号的发起者，一个是 systemd 不是信号的发起者，是信号的“传递者”。于是这次同时抓业务进程和 systemd 进程看看。结果如下：

![图片](https://mmbiz.qpic.cn/mmbiz_png/5EcwYhllQOiaMRSRiaB3YU50uhlFA9SlLMsMbM1FpkBjYjUJ02ZQSMOyZPvMPyBhRhKOH9W5BrkAu93veu6VIm2g/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

其中 3533840 是容器的 init 进程 systemd。3533916 是业务进程。和预想的一样，systemd 并不是信号的第一个发起者。systemd 是接收到 runc 的信号 15（SIGTERM）而停止的，停止前会对子进程发起 kill 行为。也就是最后的 systemd send sig。

有个疑问就来了，之前用程序 1 测试了 system+docker 的场景，没有复现，回想一下 coredump 的过程应该是这样的，程序 1 没有对每个 page 都写，只写了一个 malloc 之后的第一个 page 的第一个一个字节。coredump 在遍历每个 vma 的时候耗时要比都写了 page 要快很多（因为没有那么多空洞，VMA 不会那么零碎）。coredump 体积虽然大，但时间短，因此没有触发这个问题，对于排查这个问题带来一定的曲折。

于是排查方向转到 kill 命令和 runc 经过排查发现 K8S 的一个 lifecycle 中的 prestop 脚本有 kill 行为。把这个脚本停到后再次抓一下：

![图片](https://mmbiz.qpic.cn/mmbiz_png/5EcwYhllQOjNa58ZAjdfciaF8ia3z1gHKKnicNBMfwvJPywgBWZQRRUj7ibntadmbyJkQLGprrOJb2V1eicO6KVL2iaQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

这次没有 kill 行为，但是 systemd 还是被 runc 杀死了，发送了 2 个信号，一个是 SIGTERM，一个是 SIGKILL 现在解释通了 kill 信号的来源，这也就解释了 kill 的信号来源。其实 kill 和 systemd 的信号根源间接或直接都是 runc。runc 的销毁指令来自 k8s。

于是根据 K8S 的日志继续排查。经过排查发现最终的触发逻辑是来自字节内部实现的 Load 驱逐。该机制当容器的 Load 过高时则会把这个实例驱逐掉，避免影响其他实例。因为 coredump 的时候 CPU 会长期陷入到内核态，导致 load 升高。所以 I 引发了 Pod 驱逐。

coredump 期间实例的负载很高，导致 k8s 的组件 kubelet 的触发了 load 高驱逐实例的行为。删除 pod。停止 systemd。杀死正在 coredump 的进程，最终导致 coredump 第二阶段写 vma 数据未完成。

## 验证问题

在做一个简单的验证，停止 K8S 组件 kubelet，然后对服务发起 core。最后 gdb。验证正常，gdb 正常读取数据。至此这个问题就排查完毕了。最后修改内部实现 cgroup 级的 Load（和整机 load 近似的采集数据的方案）采集功能，过滤 D 状态的进程（coredump 进程在用户态表现为 D 状态）后，这个问题彻底解决。

# 总结

本次 coredump 文件 truncate 是因为 coredump 的进程被杀死（SIGKILL 信号）导致 VMA 没有写入完全（只写入了一部分）导致，。解决这个问题通过阅读内核源代码加以使用 bpftrace、systemtap 工具追踪 coredump 的过程。打印出关心的数据，借助源代码最终分析出问题的原因。同时我们对内核的 coredump 过程有了一定的了解。

最后，欢迎加入字节跳动基础架构团队，一起探讨、解决问题，一起变强！



**附：coredump 文件简单分析**

在排查这个问题期间也阅读了内核处理 coredump 的相关源代码，简单总结一下:

coredump 文件其实是一个精简版的 ELF 文件。coredump 过程并不复杂。coredump 的过程分为 2 个阶段，一个阶段是写 program header（第一个 program header 是 Note Program Header）,每个 program header 包含了 VMA 的大小和在文件的偏移量。gdb 也是依此来确定每个 VMA 的位置的。另一个阶段是写 vma 的数据，遍历进程的所有 vma。然后写入文件。一个 coredump 文件的结构可以简单的用如下图的结构表示。

![图片](https://mmbiz.qpic.cn/mmbiz_png/5EcwYhllQOjNa58ZAjdfciaF8ia3z1gHKKq4lmt2vlaE7qkAkIL0TvdQFMkjzelTIcDiaXRBntiaSwZrdSSLmvSyicQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

# 参考文献

1. Binary_File_Descriptor_library **(https://en.wikipedia.org/wiki/Binary_File_Descriptor_library)**
2. systemd.service — Service unit configuration **(https://www.freedesktop.org/software/systemd/man/systemd.service.html)**
3. Kubernets Pod Lifecycle **(https://kubernetes.io/docs/concepts/workloads/pods/pod-lifecycle/)**