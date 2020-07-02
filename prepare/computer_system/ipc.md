# APUE 进程进程间通信相关问题

## 管道（匿名）

管道是半双工的，数据只能向一个方向流动；需要双方通信时，需要建立起两个管道 只能用于父子进程或者兄弟进程之间（具有亲缘关系的进程）单独构成一种独立的文件系统：管道对于管道两端的进程而言，就是一个文件，但它不是普通的文件，它不属于某种文件系统，而是自立门户，单独构成一种文件系统，并且只存在与内存中。

fd[0] 为读而打开， fd[1] 为写而打开。

### 局限性

1. 历史上是半双工的；
2. 只能在有祖先关系的进程之间通信。
   1. 先建立管线`pipe(fd)`;
   2. `fork` 建立子进程;
   3. 读的进程关闭 `fd[1]`;
   4. 写的进程关闭 `fd[0]`;

### 函数

```c
#include <unistd.h>

int pipe(int fd[2]);    // fd[0] read fd[1] write
```

### 函数 popen 和 pclose

```c
#include <stdio.h>

// popen 的作用是执行 fork、然后exec cmdstring，之后建立 PIPE 连接
FILE *popen(const char * cmdstring, const char* type);

int pclose(FILE *fp )
```

## FIFO（命名管道）

　FIFO不同于管道之处在于 **它提供一个路径名与之关联** ，**以FIFO的文件形式存在于文件系统中**。这样，即使与FIFO的创建进程不存在亲缘关系的进程，只要可以访问该路径，就能够彼此通过FIFO相互通信。FIFO严格遵循先进先出（first in first out），对管道及FIFO的读总是从开始处返回数据，对它们的写则把数据添加到末尾。它们不支持诸如lseek()等文件定位操作。

* 与 PIPE 的区别：有名称，不相关的进程之间也可以进行数据交换。
* FIFO 是一种文件类型
* FIFO 是全双工的管道

### FIFO 函数

```c
#include<unistd.h>

int mkfifo(const char* path, mode_t mode);
int mkfifoat(int fd, const char* path, mode_t mode);
```

## XSI IPC

消息队列、信号量、共享存储区相似的特征如下：具有标识符和键，标识符是IPC对象的内部名，每个IPC对象都与一个键相关联，创建IPC结构需要指定一个键，键的数据类型为key_t。每个IPC都设置了权限结构。

缺点：IPC结构是在系统范围内起作用，没有访问计数。在文件系统中没有名字，不使用文件描述符，不能对它们使用多路转接I/O函数。

优点：可靠、流是受控的，面向记录、可以用非先进先出方式处理。

## 消息队列

　　消息队列（Messge Queue）：消息队列是消息的连接表，存储在内核中，由消息队列标识符标识。消息由一个正的长整型类型的字段、一个非负的长度以及实际数据字节数。

消息队列有：Posix消息队列SystemV消息队列。

它克服了前两种通信方式中信息量有限的缺点，具有写权限的进程可以按照一定的规则向消息队列中添加新消息；对消息队列有读权限的进程则可以从消息队列中读取消息。

### 消息队列相关函数

```c
#include <sys/msg.h>

int msgget(key_t key, int flag);
int msgctl(int msgid, int cmd, struct msgid_ds *buf);
int msgsnd(int msgid, const void *ptr, size_t nbytes, int flag);
ssize_t msgrecv(int msgid. void *ptr, size_t nbytes, long type, int flag);
```

## 信号量

　　信号量（Semaphore）：主要作为进程之间以及同一进程的不同线程之间的同步和互斥手段，信号量通常在内核里实现。

例如：为了获得共享资源，进程在获得资源前，先获得信号量：

1. 测试控制该资源的信号量；
2. 若信号量为正，则进程使用该资源，并将信号量减一；
3. 否则，若信号量的值为0，进程进入休眠，直到信号量为大于0被唤醒。

## 共享存储

　　共享内存（Shared memory）：可以说这是最有用的进程间通信方式，是**最快的 IPC 方式**。它使得多个进程可以访问同一块内存空间，不同进程可以及时看到对方进程中对共享内存中数据的更新。**这种通信方式需要依靠某种同步机制，如互斥锁和信号量**等。

**一种共享存储的形式是，在多个进程将同一个文件映射到他们的地址空间。XSI 共享存储的区别是，没有相关的文件，共享的存储是内存中的匿名段。**

```c
#include <sys/shm.h>

int shmget(key_t key, size_t size, int flag);
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
void *shmat(int shmid, const void *addr, int flag);
int shmdt(const void *addr);
```

基于 INTEL 的共享内存的典型存储区分布：

* 高地址
  * 命令行参数和环境变量
  * 栈
  * 共享存储
  * 堆
  * bss 未初始化的数据区
  * 已初始化的数据区
  * 程序段
* 低地址

## UNIX 域套接字

UNIX域套接字用于在同一台计算机上运行的进程之间的通信。虽然因特网域套接字可用于同一目的,但UNIX域套接字的效率更高。UNIX域套接字仅仅复制数据,它们并不执行协议处理,不需要添加或删除网络报头,无需计算校验和,不要产生顺序号,无需发送确认报文。

UNIX域套接字提供流和数据报两种接口。UNIX域数据报服务是可靠的,既不会丢失报文也不会传递出错。UNIX域套接字就像是套接字和管道的混合。

## REFERENCE

1. [AUUE 3rd](#apue)
