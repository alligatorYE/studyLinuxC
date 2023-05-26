# Ubuntu 上释放空间的简单方法

```bash
df -h
```

```bash
sudo apt-get autoremove --purge
```

```bash
sudo du -sh /var/cache/apt 	#检查当前 APT 缓存文件的使用率。
sudo apt-get autoclean 		#清理过时的 deb 软件包
sudo apt-get clean 			#移除所有在 apt 缓存中的软件包。
```