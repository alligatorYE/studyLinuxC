# libvirt for qemu
 > `libvirt` 是目前使用最为广泛的针对 KVM 虚拟机进行管理的工具和 API。`libvirtd` 是一个 daemon 进程，可以被本地和远程的 virsh (命令行工具) 调用，Libvirtd 通过调用 qemu-kvm 操作管理虚拟机。libvirt 由应用程序编程接口 (API) 库、一个守护进程 (libvirtd)，和默认命令行实用工具 `(virsh)` 等部分组成



```
yum install -y qemu-kvm qemu-kvm-tools libvirt virt-install
```

# libvirtd

```
systemctl status libvirtd.service
● libvirtd.service - Virtualization daemon
     Loaded: loaded (/lib/systemd/system/libvirtd.service; enabled; vendor preset: enabled)
     Active: active (running) since Mon 2020-08-24 09:22:15 CST; 7h ago
TriggeredBy: ● libvirtd-admin.socket
             ● libvirtd.socket
             ● libvirtd-ro.socket
       Docs: man:libvirtd(8)
             https://libvirt.org
   Main PID: 1022 (libvirtd)
      Tasks: 20 (limit: 32768)
     Memory: 65.7M
     CGroup: /system.slice/libvirtd.service
             ├─1022 /usr/sbin/libvirtd
             ├─1412 /usr/sbin/dnsmasq --conf-file=/var/lib/libvirt/dnsmasq/default.conf --leasefile-ro --dhcp-script=/usr/lib/libvirt/libvirt_leaseshelper
             └─1413 /usr/sbin/dnsmasq --conf-file=/var/lib/libvirt/dnsmasq/default.conf --leasefile-ro --dhcp-script=/usr/lib/libvirt/libvirt_leaseshelper
```

主要提供的功能包括：

- 虚拟机生命周期管理：包括不同的领域生命周期操作，比如：启动、停止、暂停、保存、恢复和迁移。支持多种设备类型的热插拔操作，包括：磁盘、网卡、内存和 CPU。
- 本地 && 远程访问：通过在本地运行 libvirt daemon, 本机和远程机器，都可以访问并使用 libvirt 的功能。远程一般通过简单配置 SSH 即可。
- 存储管理：除了虚拟机管理，任何运行了 libvirt daemon 的主机都可以用来管理不同类型的存储：创建不同格式的文件镜像（qcow2、vmdk、raw 等）、挂接 NFS 共享、列出现有的 LVM 卷组、创建新的 LVM 卷组和逻辑卷、对未处理过的磁盘设备分区、挂接 iSCSI 共享等。
- 虚拟网络管理：可以用来管理和创建虚拟网络，管理物理和逻辑的网络接口。

## 配置文件

libvirtd 服务的配置文件: `/etc/libvirt/libvirtd.conf`

客户端主配置文件: `/etc/libvirt/libvirt.conf`

qemu 的主配置文件: `/etc/libvirt/qemu.conf`

### libvirtd.conf

- 日志配置

```
log_filters="1:libvirt 1:util 1:qemu"
log_outputs="1:file:/var/log/libvirt/libvirtd.log"
```

# qemu

## libvirt 与 qemu 如何绑定

> 通过最新 qemu 源码编译的 qemu-kvm，被 libvirt 进行管理

virsh 编辑配置文件的 `emulator` 部分：

```
<emulator>/usr/local/bin/qemu-system-x86_64</emulator>
```

修改后使其生效时，会出现权限错误：

```
# virsh define ./qemu/win10.xml
error: Failed to define domain from ./qemu/win10.xml
error: internal error: Failed to start QEMU binary /usr/local/bin/qemu-system-x86_64 for probing: libvirt:  error : cannot execute binary /usr/local/bin/qemu-system-x86_64: Permission denied
```

解决方法：

> 在 `/etc/apparmor.d/usr.sbin.libvirtd` 文件中，添加一行:
>
> ```
> /usr/local/bin/* PUx,
> ...
> # force the use of virt-aa-helper
> ...
> /usr/local/bin/* rmix,
> ```
>
> 使能生效：`sudo systemctl reload apparmor` 或 `sudo systemctl restart apparmor.service`

原因： `libvirtd` 应用的权限被 `apparmor-profiles` 所控制，而 `/usr/local/bin` 目录下的可执行文件，没有被添加到 apparmor-profiles 的配置中，因此使用时检测到没有权限。

- AppArmor 是一款与 SeLinux 类似的安全框架 / 工具，其主要作用是控制应用程序的各种权限，例如对某个目录 / 文件的读 / 写，对网络端口的打开 / 读 / 写等
- Ubuntu 的默认选择
- 在 `centos` 中如果出现该错误，可以通过临时禁用 SELinux 进行测试: `setenforce 0`

`apparmor-profiles` 的状态：

```
sudo apparmor_status
```

开启虚拟机时，出现无法执行错误：

```
error: internal error: process exited while connecting to monitor: libvirt:  error : cannot execute binary /usr/local/bin/qemu-system-x86_64: Permission denied
```

原因：不能在[ apparmor 禁用](https://blog.csdn.net/iteye_12675/article/details/82519399)`usr.sbin.libvirtd`，`usr.lib.libvirt.virt-aa-helper`, 也就是将其生成软连接到 `/etc/apparmor.d/disable`. 如果要禁掉可能必须重新编译 libvirt 同时添加 `--without-apparmor` 选项 (未测试)

### 其他 apparmor 权限的问题

在 libvirtd 中对 qemu 的运行存在一些权限的设置，为了方便调试，将权限控制禁用。在配置文件 `/etc/libvirt/qemu.conf` 中添加下行代码：

```
security_driver = "none"
```

重启 `libvirtd.service` 服务:

```
sudo systemctl restart libvirtd.service
```

# virsh

## 查看虚拟机状态

```
$virsh list --all
 Id   Name          State
 ------------------------------
  -    ubuntu20.04   shut off
  -    win10         shut off
```

## 显示虚拟机的 XML 配置

```
$virsh dumpxml ubuntu20.04
```

## 编辑虚拟机的 XML 配置文件

```
virsh edit ubuntu20.04
```

## 常用命令

| 命令                                | 描述                                                         |
| ----------------------------------- | ------------------------------------------------------------ |
| `virsh list`                        | 显示正在运行的虚拟机                                         |
| `virsh list --all`                  | 显示所有的虚拟机                                             |
| `virsh start vm-name`               | 启动 vm-name 虚拟机                                          |
| `virsh shutdown vm-name`            | 关闭 vm-name 虚拟机                                          |
| `virsh destroy vm-name`             | 虚拟机 vm-name 强制断电                                      |
| `virsh suspend vm-name`             | 挂起 vm-name 虚拟机                                          |
| `virsh define vm-name`              | 将 domain 注册，但是没有启动，下次启动时生效                 |
| `virsh undefine vm-name`            | 删除虚拟机，慎用                                             |
| `virsh dominfo vm-name`             | 查看虚拟机的配置信息                                         |
| `virsh domiflist`                   | 查看网卡配置信息                                             |
| `virsh domblklist vm-name`          | 查看该虚拟机的磁盘位置                                       |
| `virsh edit vm-name`                | 修改 vm-name 的 xml 配置文件                                 |
| `virsh dumpxml vm-name`             | 查看 KVM 虚拟机当前配置                                      |
| `virsh autostart vm-name`           | KVM 物理机开机自启动虚拟机，配置后会在此目录生成配置文件 /etc/libvirt/qemu/autostart/vm-name.xml |
| `virsh autostart --disable vm-name` | 取消开机自启动                                               |

# 命令行参数转 XML 配置文件

## domxml-from-native

```
sudo virsh domxml-from-native qemu-argv aa.txt
```

错误：

```
error: this function is not supported by the connection driver: virConnectDomainXMLFromNative
```

> 最新 qemu 中删除了该功能，因为在实践中它过于不可靠和不完整而无用

# 配置

## 添加显卡显示 SDL

```
<graphics type='sdl' display=':0.0' xauth='/root/.Xauthority'>
    <gl enable='yes'/>
</graphics>
```

> **以上配置在 `Xfce` 桌面环境下可以生效**

### 权限错误:

```
error: internal error: cannot load AppArmor profile 'libvirt-39466e8a-545d-420e-ba0f-b942d09a5bdb'
```

解决方法：在 `/etc/apparmor.d/usr.sbin.libvirtd` 配置文件中添加 `/usr/local/bin/* rmix,`

### SDL

```
Could not initialize SDL(x11 not available) - exiting
```

原因：未找到
解决方法：安装 xfce 桌面环境

```
yum groups install Xfce
```



> for centos7.8

## 编译使能 SDL

在配置中使能 SDL：`--enable-sdl`

## 异常错误

### mlock

```
qemu-system-x86_64: -realtime mlock=off: warning: '-realtime mlock=...' is deprecated, please use '-overcommit mem-lock=...' instead
```

# 实例

虚拟机配置文件：[ubuntu20.04](https://winddoing.github.io/src/ubuntu20.04.xml)

````
```

## 域——domain

## 池——pool


# 升级libvirt

## libvirt5.0.0 for centos7

``` shell
#!/bin/bash

#url="http://mirror.centos.org/centos/7.8.2003/virt/x86_64/libvirt-latest/"
url="http://mirrors.huaweicloud.com/centos/7/virt/x86_64/libvirt-latest/"

curl $url > page.txt

grep "5.0.0-1.el7.x86_64" page.txt > fff.txt

while read line
do
    #截取href前多余字符串
    aaa=${line: 24}
    #截取title后多余字符串
    bbb=${aaa%title*}
    #设置为href变量
    export $bbb
    #去掉变量值两边的引号
    ccc=`echo $href | sed 's/\"//g'`

    echo $url$ccc
    wget $url$ccc

done < fff.txt

rm page.txt fff.txt -rf

#yum install ./*
````

# 参考

- [Domain XML format](https://libvirt.org/formatdomain.html)
- [QEMUSwitchToLibvirt](https://wiki.libvirt.org/page/QEMUSwitchToLibvirt)
- [libvirt 原理](https://www.cnblogs.com/wn1m/p/11280605.html)
- [Changing libvirt emulator: Permission denied](https://unix.stackexchange.com/questions/471345/changing-libvirt-emulator-permission-denied)
- [虚拟化技术之 kvm 管理工具 virsh 常用基础命令（一）](https://www.cnblogs.com/qiuhom-1874/p/13508231.html)
- [编译 qemu 和 libvirt 使支持 SDL](https://blog.csdn.net/jiuzuidongpo/article/details/44342509)
- [Virtualization - libvirt](https://discourse.ubuntu.com/t/virtualization-libvirt/11522/1)
- [KVM 虚拟机 XML 配置文件详解](https://blog.51cto.com/4746316/2336524)
- [虚拟化调试和优化指南](https://access.redhat.com/documentation/zh-cn/red_hat_enterprise_linux/7/html-single/virtualization_tuning_and_optimization_guide/index#sect-Virtualization_Tuning_Optimization_Guide-NUMA-Auto_NUMA_Balancing)
- [Windows 10 Virtualization with KVM](https://www.funtoo.org/Windows_10_Virtualization_with_KVM)