# JVM（更多面试问题，欢迎关注微信公众号「帅地玩编程」）

## 垃圾回收算法

### 标记-清除算法

### 标记-整理算法

### 复制算法：分eden区和survivor区

## 如何判断一个对象没用了

### 记数法

### 可达性分析

- 方法的局部变量和类的静态变量可以作为GCRoot，而实例变量不可以

## 垃圾回收器

### serial串行收集器

### parNew并行收集器

- 用于回收新生代
- 复制算法

### CMS收集器

- 采用标记-清除算法
- 用于回收老年代
- 默认使用的CPU核数为(核数+3)/4
- 过程

  - 初始标记：很快，停止用户线程
  - 并发标记：慢，并发进行
  - 重新标记：很快，停止用户线程
  - 清除：慢，并发进行

- 缺点

  - 不能处理浮动垃圾
  - 非常消耗CPU资源
  - Concurrent Mode Failure问题

    - 并发清理垃圾期间，新生代转移到老年代的对象导致老年代不够内存存放
    - -XX：CMSInitiatingOccupancyFaction指定老年代占用多少内存比例触发垃圾回收
    - 此时会触发使用serial垃圾回收器来回收

- 一些参数

  - -XX：+UseCMSCompactAtFullColletion：表示每次Full之后会Stop the world来整理内存碎片
  - -XX:CMSFullGCsBeforeCompaction：表示执行多少次FullGC才整理内存碎片，默认为0
  - -XX:CMSInitiatingOccupancyFaction：设置内存占用多少时触发CMS回收

### G1收集器

- 总体采用标记-清除算法，局部采用标记-整理算法
- 开启：-XX:UseG1GC
- 过程

  - 初始标记
  - 并发标记
  - 最终标记
  - 筛选回收

- 缺点
- 优点

  - 分代收集
  - 可预测停顿

    - 最终每个region的回收价值，优先回收高价值的
    - 最多停留多久：-XX:MaxGCPauseMills

  - 空间整合

    - 把内存分成若干个region，最多分2048个
    - 每个分区被标记了E、S、O和H，H表示这些Region存储的是巨型对象，新建对象大小超过Region大小一半时，直接在新的一个或多个连续分区中分配，并标记为H

## 运行时区域划分

### 程序计数器

### 虚拟机栈

- 操作数栈
- 局部变量
- 方法入口

### 本地方法栈

### Java堆

- 全局变量
- new的对象
- JDK1.8之后字符串常量池也是

### 方法区

- 类信息
- 常量

## 核心问题分析

### Stop the world

## 一些常用命令

### -XX:-handlerPromotionFailure：根据以往新生代进入老年代的平均值来担保，不过JDK1.6之后就废弃了

### 内存分配参数

- -Xms：堆大小
- -Xmx：堆的最大大小
- -Xmn：新生代大小
- -XX:（Max）Permsize：永久代大小
- -Xss：每个线程的栈内存大小

### 如何设置参数

- tomcat可以在catalina.sh配置
- IDEA可以在VM options 设置
- Java -jar 后面跟上参数

### 垃圾回收器相关

- -XX:+UseParNewGC

  - 默认使用线程数和cpu核数一样
  - 可以用 -XX:ParalleGCThreads

### 17 个 JVM 参数

- verbose:gc

  - 启动jvm的时候，输出jvm里面的gc信息

- -XX:+printGC

  - 打印的GC信息

- -XX:+PrintGCDetails

  - 打印GC的详细信息

- -XX:+PrintGCTimeStamps

  - 打印GC发生的时间戳

- -X:loggc:log/gc.log

  - 指定输出gc.log的文件位置

- -XX:+PrintHeapAtGC

  - 表示每次GC后，都打印堆的信息

- -XX:+TraceClassLoading

  - 监控类的加载

- -XX:+PrintClassHistogram

  - 跟踪参数

- -Xmx -Xms

  - 这个就表示设置堆内存的最大值和最小值

- -Xmn

  - 设置新生代的内存大小。

- -XX:NewRatio

  - 新生代和老年代的比例。比如：1：4，就是新生代占五分之一。

- -XX:SurvivorRatio

  - 设置两个Survivor区和eden区的比例。比如：2：8 ，就是一个Survivor区占十分之一。

- XX:+HeapDumpOnOutMemoryError

  - 发生OOM时，导出堆的信息到文件。

- -XX:+HeapDumpPath

  - 表示，导出堆信息的文件路径。

- -XX:OnOutOfMemoryError

  - 当系统产生OOM时，执行一个指定的脚本，这个脚本可以是任意功能的。比如生成当前线程的dump文件，或者是发送邮件和重启系统。

- -XX:PermSize -XX:MaxPermSize

  - 设置永久区的内存大小和最大值；永久区内存用光也会导致OOM的发生。

- -Xss

  - 设置栈的大小。栈都是每个线程独有一个，所有一般都是几百k的大小。

## 如何分析一个系统的多久触发一次full gc

### 首先分析一分钟会产生多少M数据到新生代

### 接着就可以知道新生代大概多久会触发一次垃圾回收

### 触发的时候每次有100分之几是活下来的

### 接下来survivor区能不能放的下来就异常重要了

### 如果放不下来的话：每次进入老年代，显然会很响应性能

### 如果放的下来的话

### 优化

- 尽量保证每次gc存活的对象不能超过s区的50%

## 类的加载过程

### 加载

### 验证

### 准备：类变量内存分配，初始化

### 解析：把符号引用替换成直接引用

### 初始化

- new指令
- 反射
- 子类要初始化时
- 虚拟机启动时，会指定一个主类

### 使用

### 卸载

## 双亲委派机制

### 启动类加载器

- 虚拟机的一部分，C++写的
- 加载 /lib或者Sbootclasspath指定的类
- 程序员不可调用，使用时传入参数null

### 拓展类加载器

- 加载 /lib/ext目录的类

### 应用程序加载器

- 用户路径下classpath路径的类

## 老年代与年轻代

### 什么时候会触发Full GC

- 调用System.gc()
- 老年代空间不足
- 大对象进入老年代，找不到足够大的连续空间
- 预测到晋升为老年代的对象太多以至于放不下
- 永生区空间不足

### 分别使用什么算法

- 新生代使用 复制算法
- 老年代使用标记整理算法
