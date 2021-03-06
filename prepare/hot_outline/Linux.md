# Linux（更多面试问题，欢迎关注微信公众号「帅地玩编程」）

## 常用基础命令

### sudo：让用户临时获得管理员权限

### ln  -s source dest：软连接,保存一个路径，相当于快捷方式

### ln source dest：默认硬连接，创建一个真实存在的文件，不过共用一个inode

### more：可以翻页，全部加载，不能往前翻

### less：可以往前翻，加载部分，实时加载

### 搜索相关

- locate

  - 使用 /var/lib/mlocate数据库搜索，速度快，可以用update更新数据库
  - locate [-ir] keyword。-r表示正则

- find

  - find [basedir] [option]
  - 子主题 2

- grep

  - grep [-acinv] [--color=auto] 关键字符串 filename
  - 参数详解

    - -c：统计个数
    - -i：忽略大小写
    - -n：输出行号
    - -v：反向选择

- awk

### 打包相关

- gzip

  - 压缩：gzip -cv filename
  - 解压：gzip -d filename
  - 可以用 zcat, zmore等查看压缩文件

- bzip2

  - bzip2 [-cdzv] filename，其中加了 k 表示保留源文件
  - 可以用 bzcat, bzmore, bzgrep查看压缩文件内容

- tar

  - tar -cvf dest source 打包
  - tar -zcvf dest source ：打包并且压缩
  - tar -xvf filename：解打包

## 文件系统

### 组成

- Inode：一个文件占用一个inode，记录文件属性，同时记录此文件所属的 block 编号
- Block：记录文件的具体内容，文件太大会占用多个 block
- Superblock：记录文件系统的整体信息，包括inode和block的总量，文件系统的格式等
- block bitmap：记录block是否被使用的位图

### 类型

- Exts：要读取文件时，根据 inode来查找对应的block
- Fat：没有inode，每个block中存放着下一个block的编号

## IO操作

### select

- 一个socket连接就会分配一个文件描述符
- socket可以读写了之后会做一个标志，然后唤醒程序，select程序会遍历所有的socket
- 最多1024个

### epoll

- 只把需要做处理的socket发给程序

### 同步

- 例如调用者调用了一个接口，这儿接口比如要执行一些磁盘文件读写操作，或者网络通信等。如果是同步的，则调用者需要等待这些磁盘读写操作完成后才能返回

### 异步

- 异步的话，则直接返回，也不管这个调用有没成功。接口干完了自己的事情之后，而已通过一些内部的通信机制李艾进行通知，也可以通过回调函数来通知
- 同步异步是针对接口的调用，API类库调用

### 阻塞与非阻塞

- 通常是针对底层的 IO 操作来说的
- 例如我们的程序想要通过网络去读取数据
- 如果采用阻塞IO的话，一旦发起请求去内核读取数据，此时内核还没有把数据从网络中读取过来，也就是说内核还没把数据准备好，此时会阻塞，知道内核把数据准备号才返回。
- 而非阻塞的话，如果内核没准备好数据，内核会返回一个信号给程序，告诉它数据还没准备好，然后程序就直接返回了干别的事情了，过会再来询问。

### NIO 与 IO

- 区别

  - IO是面向流的， NIO是面向缓冲的，这意味着NIO有更大的灵活性，可以进行偏移读取等
  - NIO是非阻塞的，当我们去通道读取数据的时候，如果这个通道没数据，线程不会阻塞，而是会不断轮训其他通道。而IO当我们调用read时，如果数据还没准备好，则该线程会阻塞
  - NIO有一个selector的概念，一个选择器可以监控多个通道。

- NIO适合？

  - 监听多个连接，且数据量比较少的，例如聊天系统

### iostat：查看磁盘信息

## 进程相关

### 命令相关

- ps

  - ps -l 查看自己的进程
  - ps aux 查看系统所有进程

- pstree -A
- top
- netstat

### 进程状态

- R
- D：不可中断睡眠，通常为 IO 操作
- S：可中断阻塞，等待某个事情发生
- Z:僵尸进程：进程已经终止，但是父亲没有回收其资源
- T：结束

### SIGCHLD

- 当子进程状态改变时，有两件事会发生在父进程中
- 1、得到 SIGCHLD 信号
- 2、waitpid()或者wait()调用返回

### 孤儿进程

- 一个父进程退出而子进程还在运行，这些进程被称为孤儿进程
- 孤儿进程会被 init 进程收养，所以不会对系统造成危害

### 僵尸进程

- 如果子进程退出，但父进程没有调用 wait()，那么子进程的描述符仍然在系统中，这种称之为僵尸进程
- 消灭僵尸进程可以将其父进程杀死，从而被 init 进程收养。
- 如何避免？

  - fork两次，父进程创建了子进程之后，子进程再创建孙进程，之后自己销毁，这样孙进程就交给init进程了
  - s

## 性能优化

### 项目出问题的排除故障

- 用 top 和 jstack 命令

  - top 直接定位进程
  - top -Hp pid 定位哪个进程
  - jstack pid | grep -A 200 线程id

- pidstat 命令

  - 可以用来分析一个进程的IO,CUP，内存等情况
  - 常用命令

    - pidstat -u 1：CUP
    - pidstat -r 1：内存
    - pidstat -d 1：IO

- 分析Java死锁

  - 用jsp找出对应的Java程序
  - 用jstack查看对应的栈信息

### CPU使用很高，但top却没找出来的原因有哪些

- 短进程太多，例如应用不停着奔溃重启
