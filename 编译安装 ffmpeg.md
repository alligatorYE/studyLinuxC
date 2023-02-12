# 编译安装 ffmpeg

## 1. 编译 yasm
```bash
wget http://www.tortall.net/projects/yasm/releases/yasm-1.3.0.tar.gz
tar zxvf yasm-1.3.0.tar.gz
cd yasm-1.3.0
./configure
make && sudo make install
```

## 2. 编译 fdk-aac
```bash
wget https://jaist.dl.sourceforge.net/project/opencore-amr/fdk-aac/fdk-aac-2.0.2.tar.gz
wget https://jaist.dl.sourceforge.net/project/opencore-amr/fdk-aac/fdk-aac-0.1.6.tar.gz
tar -xvf fdk-aac-2.0.2.tar.gz
cd fdk-aac-2.0.2
./configure
make && make install
```
## 3. 安装lame
```bash
wget http://downloads.sourceforge.net/project/lame/lame/3.99/lame-3.99.5.tar.gz
tar -xzf lame-3.99.5.tar.gz
cd lame-3.99.5
./configure
make && sudo make install
```

## 4. 安装nasm
```bash
 wget https://www.nasm.us/pub/nasm/releasebuilds/2.13.03/nasm-2.13.03.tar.gz
 tar xvf nasm-2.13.03.tar.gz
 cd nasm-2.13.03
 ./configure
 make && sudo make install
```
## 5. 安装x264
```bash
wget http://mirror.yandex.ru/mirrors/ftp.videolan.org/x264/snapshots/x264-snapshot-20191217-2245.tar.bz2
bunzip2 x264-snapshot-20191217-2245.tar.bz2
tar -vxf x264-snapshot-20191217-2245.tar
cd x264-snapshot-20191217-2245
./configure --enable-static --enable-shared --disable-asm --disable-avs
make && make install
```


## 6. 安装FFmpeg

```bash
wget -c http://ffmpeg.org/releases/ffmpeg-snapshot.tar.bz2
bunzip2 ffmpeg-snapshot.tar.bz2
tar -xvf ffmpeg
cd ffmpeg
./configure --prefix=/usr/local/ffmpeg --enable-gpl --enable-small --arch=x86_64 --enable-nonfree --enable-libfdk-aac --enable-libx264 --enable-filter=delogo --enable-debug --disable-optimizations --enable-shared
make && make install
```

## FFmpeg编译的问题

- 问题一：找不到 fdk-aac库

  在编译ffmpeg时，有可能会报找不到fdk_aac库的错误。此时我们应该设置一下 PKG_CONFIG_PATH，指定ffmpeg到哪里找我们安装好的库。

  上面通过源码安装的库，默认地址为/usr/local/lib下面，当然你可以通过./configure 中的–prefix参数改变这个目录。

  如果使用默认路径的话，可以通过下面的命令来指定编译时去哪里找库

  ```bash
  export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig
  ```

  如果你改变了默认路径，则将后面的 `/usr/local/lib/pkgconfig`修改为你变更后的路径`/xxx/.../lib/pkgconfig`即可。

