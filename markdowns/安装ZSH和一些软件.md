# 安装ZSH和一些软件

```bash

hostnamectl set-hostname --static "Alice"
hostnamectl set-hostname --pretty "Alice-Ubuntu22"
hostnamectl set-hostname Alice
usermod -l SheepStarving -d /home/NewUser -m OldUser

arm-linux-gnueabihf：
安装：
sudo apt-get install gcc-arm-linux-gnueabihf
sudo apt-get install g++-arm-linux-gnueabihf
卸载：
sudo apt-get remove gcc-arm-linux-gnueabihf
sudo apt-get remove g++-arm-linux-gnueabihf

gcc-arm-none-eabi：
sudo apt-get install gcc-arm-none-eabi

go：
sudo apt-get install golang

tree:
sudo apt-get install tree

git:
sudo apt-get install git

ffmpeg:
sudo apt-get install ffmpeg

docker:
sudo apt-get install docker

sudo apt install thefuck
```



## 安装zsh

```bash
sudo apt install zsh

sh -c "$(wget https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"

vim ~/.zshrc

ZSH_THEME="gnzh"

#darkblood 	#[双行]有点小帅
#Soliah 		#[双行][带时间]
#steeef 		#[双行]颜色挺好看
#josh    		#[双行]闪电标志
#blinks  		#[双行]深色背景框
#fox    		#[双行]很花哨，跟darkblood一个级别
#xiong-chiamiov  	#[双行][带时间]
#gnzh    		#[双行]最简洁的双行


alias sud='sudo apt update'
alias sug='sudo apt upgrade'
alias sin='sudo apt install'
alias cdwks='cd /home/sheepstarving/workspace' #你自己的路径

#函数
mkcd()
{
    mkdir -p --"$1" && cd -P -- "$1"
}

git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions

git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting

# 设定默认shell
chsh -s /bin/zsh 
```