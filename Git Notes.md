# Git Notes

### 查询当前用户信息

```bash
# 带`--local`参数就是查询局部用户信息，带`--global`就是查询全局用户信息
$ git config --list --global
```

### 添加局部用户信息

```bash
#最后一个带引号的参数为要配置的参数，如果不带这个参数就是查询这个参数
$ git config --local user.name '饮风'
$ git config --local user.name 'youngermind@163.com'
```

### 查看分支和细节

```bash
$ git branch -av
* 0.0.1  a2a86d3 remove C code
  master 449d4a6 initial commit
```



### 切换分支

```bash
git checkout 0.0.1

#或者

git switch master
```

### 创建一个仓库并配置local用户信息

```bash
# 查看当前路径
$ pwd
```

### `git log` 查看版本演变历史

```bash
#不带参数查看
$ git log
```

```bash
#带 `--oneline` 简洁查询
$ git log --oneline
```

```bash
#带`--all`查看所有版本的历史记录
$ git log --all
```

```bash
#带`--graph`查看分支结构图
$ git log --all --graph
```

```bash
#带`-n5` 查看最近的几条记录,5的位置是你想看的最近的几条信息
$ git log --all -n5
```

### git 目录

#### heads ：分支

```bash
$ cd .git/refs/heads
```

查看文件类型

```bash
$ git cat-file -t a2a86d3ce9a8f575601bb0581da40ee666c34d88
```

查看文件内容

```bash
$ git cat-file -p a2a86d3ce9a8f575601bb0581da40ee666c34d88
```

### 分离头指针(detached HEAD)

### 查看与父节点的区别

```bash
# ‘~’后面的数字代表往上追溯到第几代
$ git diff HEAD HEAD~2
```

### 删除分支

```bash
# test01为要删除的分支名
$ git branch -D test01
```

### 变更最近一次commit描述

```bash
$ git commit --amend
```

### 变更历史commit ——`rebase`

```bash

$ git rebase -i a2a86d3ce9a8f575601bb0581da40ee666c34d88
```
>以下是交互界面的内容

```bash
pick 99110d2 add readme.md

# Rebase a2a86d3..99110d2 onto a2a86d3 (1 command)
#
# Commands:
# p, pick <commit> = use commit
# r, reword <commit> = use commit, but edit the commit message
# e, edit <commit> = use commit, but stop for amending
# s, squash <commit> = use commit, but meld into previous commit
# f, fixup <commit> = like "squash", but discard this commit's log message
# x, exec <command> = run command (the rest of the line) using shell
# b, break = stop here (continue rebase later with 'git rebase --continue')
# d, drop <commit> = remove commit
# l, label <label> = label current HEAD with a name
# t, reset <label> = reset HEAD to a label
# m, merge [-C <commit> | -c <commit>] <label> [# <oneline>]
# .       create a merge commit using the original merge commit's
# .       message (or the oneline, if no original merge commit was
# .       specified). Use -c <commit> to reword the commit message.
#
# These lines can be re-ordered; they are executed from top to bottom.
#
# If you remove a line here THAT COMMIT WILL BE LOST.
#
# However, if you remove everything, the rebase will be aborted.
#
```

#### 合并连续的多个commit 

```bash
git rebase -i 
```

