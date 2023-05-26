Ubuntu 修改主机名

```bash
sudo hostnamectl set-hostname Ubuntu18
sudo hostnamectl set-hostname "Ubuntu18" --pretty
sudo hostnamectl set-hostname Ubuntu18 --static
sudo hostnamectl set-hostname Ubuntu18 --transient
```

修改用户名
```bash
sudo passwd sheep
```

使用apt安装时报错：

```bash
E: Could not get lock /var/lib/dpkg/lock-frontend - open (11: Resource temporarily unavailable)
E: Unable to acquire the dpkg frontend lock (/var/lib/dpkg/lock-frontend), is another process using it?
```


解决方案：
方案一：

```bash
sudo killall apt apt-get
```


如果提示没有apt进程：

```bash
apt: no process found
apt-get: no process found
```


往下看方案二
方案二：
依次执行：

```bash
sudo rm /var/lib/apt/lists/lock
sudo rm /var/cache/apt/archives/lock
sudo rm /var/lib/dpkg/lock*
sudo dpkg --configure -a
sudo apt update
```

```bash
Errors were encountered while processing:
 libxcb-xfixes0-dev:amd64
 libxcb-present-dev:amd64
 libegl1-mesa-dev:amd64
 libgl1-mesa-dev:amd64
 libgles2-mesa-dev:amd64
 libglu1-mesa-dev:amd64
 libsdl2-dev:amd64
```

```bash
可以通过如下指令进行修复：
sudo apt-get update
sudo apt --fix-broken install
```

