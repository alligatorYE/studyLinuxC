
# GDB 调试多进程服务程序
## 调试父进程：

```shell
set follow-fork-mode parent #缺省
```

## 调试子进程

```shell
set follow-fork-mode child
```



## 设置调试模式

```shell
set detech-on-fork [on|off] #缺省是on
```

如果是on表示调试当前进程的时候，其他进程继续运行，如果off，调试当前进程时，其他进程被GDB挂起。

## 查看调试的进程

```shell
info inferiors
```

## 切换当前调试的进程：

```shell
inferior 进程id
```

