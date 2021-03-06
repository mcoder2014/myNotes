# Redis（更多面试问题，欢迎关注微信公众号「帅地玩编程」）

## 基本数据结构及其应用

### 字符串

- 1、缓存功能 2、计数，例如浏览量的统计
- 共享session
- 限制过期时间，例如短信验证吗的有效期

### 列表

- 消息队列
- 文章列表

### 集合

- 给用户打标签
- 点赞、关注之类的，由于集合之间支持合并等操作，可以用来求共同好友之类的

### 有序集合

- 排名系统

### 哈希

- 缓存一些对象
- 底层实现原理

  - 由dict结构表示

    - dictType *type
    - void *privatedata 私有数据
    - dictht ht[2]
    - int trehashidx，如果没有在rehash则值为-1

- rehash过程

  - 拓展

    - 大小为 used * 2 的 2^n
    - 渐进式rehash

      - rehashidx记录哈希到n哪了，如果有增删改查的话，则会现在ht[0]进行，如果没有则到ht[1]

    - 如果没有执行 bgsave命令，则负载因子大于等于1，否则大于等于5

  - 收缩

    - 负载因子为 0.1

## 面试题相关

### 为什么Redis很快

- 采用非阻塞的IO多路复用，使得单个线程可以处理多个连接，并且把相关请求直接直接压到队列中
- 纯内存操作：文件事件分派器从队列中取出事件分配给对应处理器进行处理（连接应答、命令请求、命令回复三中处理器）
- 单线程避免的线程上下文切换的消耗、加锁、解锁等消耗

### 过期按键删除策略以及内存淘汰机制

- 定期删除+惰性删除，注意，定期删除每隔一段时间是随机抽取一些元素删除的
- 内存淘汰机制

### 并发竞争问题

## 集群

## 哨兵

## 如何保证高可用

### 单机redis很难支撑10+的qps

### 主从复制

## 事务

### 把命令放入队列，直到提交才开始执行

### 不具有原子性，也就是说不会回滚，因此也没有一致性

### 不过又隔离性和持久性

## 数据库、缓存双写不一致问题

### 1、采用先删除缓存后更新数据库的策略  + 对同一商品的更新、读取的请求映射到同一个队列

### 先更新数据库在删除缓存会，如果删除缓存失败会出现不一致问题

### 先更新缓存在更新数据库可能会出现不一致和如果更新操作频繁的话，会出现资源浪费问题

## 如何解决多线程竞争问题

### 可以采用分布式锁 + 时间戳

## 持久化

### AOF

- 开启AOF：appendonly yes
- 大致过程

  - 写入命令追加到 aof_buf 缓存区
  - AOF 缓冲区根据对应策略做硬盘同步操作
  - AOF越来越大，所以会做重写操作
  - 加载AOF恢复

- 文件同步机制

  - always

    - 命令写入aof_buf后马上调用fsync命令操作做同步操作

  - everysec

    - 先调用系统write操作，之后返回。fsync操作由专门的线程每隔1秒调用一次

  - no

    - 调用write，不对aof文件做同步操作，同步操作由操作系统自己负责，周期最长为30秒

- wirte和fsync解释

  - write

    - 会触发延迟写机制。Linux内核会提供一个页缓冲区来提供IO性能。write操作写入缓冲区后直接返回

  - fsync

    - 强制硬盘同步，将阻塞知道写入硬盘完成

- 重写机制

  - fork一个子进程来重写，父进程依然响应，把命令存放再AOF重写缓冲区中。子进程完成后，父进程再把AOF缓存区的数据写入到AOF文件中

- 相关问题定位

### RDB

- Save：阻塞持久化
- bgsave：阻塞fork子进程持久化
- 采用LZF压缩算法
- 优点

  - 压缩的二进制文件恢复非常快
  - 适合全量复制等场景

- 缺点

  - 无法做到实时持久化，频繁操作成本高
  - 不同版本的RDB格式可能无法兼容

## 用redis实现分布式锁
