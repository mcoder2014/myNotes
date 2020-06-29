# java

## 基础

### java特性

- 继承
- 多态

  - 编译时多态通过方法重载

    - 重载只能通过不同的方法参数区分

      - 参数个数不同
      - 参数类型不同

    - 通过指向父类的指针，来调用在不同子类中实现的方法

  - 运行时多态通过方法重写

### 多态用到了动态绑定

- 编译时类型与运行时类型不一致就会发生运行时动态绑定（典型的就是重载）

### java元注解

- 能注解到注解上的注解，能用在其他注解上的注解
- 自定义注解：[java内置注解、元注解和自定义注解](https://www.cnblogs.com/yanze/p/9296237.html)

### java注解

- 注解的本质就是一个继承了 Annotation 接口的接口
- 解析一个类或者方法的注解往往有两种形式

  - 一种是编译期直接的扫描
  - 一种是运行期反射

### String StringBuffer StringBuilder

- stringBuffer是线程安全
- String s = new String(“zsx”);

  - 创建了2个String对象和一个引用。

- String+是StringBuffer的append()方法来实现的

### 抽象类和接口区别

- 一个类只可以继承一个抽象类，但可以实现多个接口
- 抽象类可以有构造方法，接口中不能有构造方法
- 抽象类可以有普通的成员变量，接口中不能有普通的成员变量
- 抽象类中可以包含静态方法，接口中不能包含静态方法

### 反射

- class.forname

  - 是运用反射的原理创建对象

- private修饰的方法与变量能否反射（不能）
- 在 Java 的反射中，
Class.forName 和 ClassLoader 的区别

  - classloader值是将类的.class文件加载到jvm中,不会执行static代码块
  - class.forName不但将类的.class文件加载到jvm中，还会执行static代码块

- classloader

  - 类加载器分类
    - 启动类加载器
      - 加载 Java 的核心库
    - 扩展类加载器
      - 加载 Java 的扩展库
    - 应用程序类加载器
      - 加载Java 应用的类

- 作用

  - 在运行时创建对象
  - 获取任意一个类所具有的成员变量和方法
  - 判断一个对象所属的类
  - 调用一个对象的任意方法

### 序列化

- 对象中被static或transient修饰的变量，在序列化时不被保存

### 动态代理

- 加事务
- 加日志
- 加权限
- spring AOP
- 想给一个类加一些额外的方法，可以对proxy代理类（中间类）添加一些额外的方法

### 克隆

- 浅克隆

  - 浅克隆不会克隆原对象中的引用类型，仅仅拷贝了引用类型的指向

- 深克隆

  - 深克隆的实现就是在引用类型所在的类实现Cloneable接口，
并使用public访问修饰符重写clone方法。

### 关键字

- throw和throws
- final、finally、finalize
- try、catch、finally
- Exception和Error
- switch支持的数据类型（java8）

  - byte、short、int 、char及其包装类型和string

### DOM和SAX解析xml的不同

- dom是基于内存的，把xml读到内存中，消耗很大的内存空间；
SAX是基于事件驱动的方式，事件被触发时，获取相应的xml数据解析
- dom可以向xml插入数据，SAX不可以
- dom可以随机访问，SAX不可以

### Java包装类的缓存

- 具体的实现方式为在类中预先创建频繁使用的包装类对象，当需要使用某个包装类的对象
时，如果该对象封装的值在缓存的范围内，就返回缓存的对象，否则创建新的对象并返回
- 哪些包装类没有缓存

  - float、double

### BIO、NIO、AIO

- NIO原理

  - 缓冲区buffer
  - 通道channel
  - 选择器select、poll、epoll

    - select和poll具有O(n)的无差别轮询复杂度
    - epoll事件复杂度为O(1),基于时间驱动的

### io

- 字节流

  - 按字节读，可用于文件、图片、视频、音频

- 字符流

  - 按照字符读，一般用于文件

### 异常

- 出现这类异常的时候程序会由虚拟机接管
- checkedException
  - 主要是指IO异常、SQL异常等。对于这种异常，
JVM要求我们必须对其进行cathc处理

### #字节码的结构

- 魔数
- 副版本号
- 主版本号
- 常量池
- 类索引
- 访问标志
- 方法集合
- 方法计数器

### Enum类中为什么构造函数必须是私有的

- 了保证每一个枚举类元素的唯一实例,是不会允许外部进行new的

### sort排序原理

- 使用了两种排序方法，快速排序和优化的归并排序
- 快速排序主要是对那些基本类型数据排序，
 而归并排序用于对Object类型进行排序。

### 面向接口编程的好处

- 接口本质上就是由制定者来协调实现者和调用者之间的关系
- 设计模式的原则里的开闭原则，
其实就是要使用接口来实现对扩展开放，对修改关闭
- 子主题

## 容器

### List

- ArrayList
  - 默认大小是10，每次1.5倍

- stack
- vector
- LinkedList

### CopyonWriteArrayList和CopyOnWriteArraySet

- 原理：读写分离，读支持高并发，写需要加锁
- 问题
  - 内存占用
  - 数据一致性问题，支持最终一致性，不支持实时一致性

### Set

- hashset
- treeset
  - TreeSet可以确保集合元素处于排序状态

### map

- HashMap
  - HashMap1.7为什么使用的是头插法，1.8后使用尾插法，这个改变有什么作用吗
  - jdk8之前hashmap这种插入方法在并发场景下如果多个线程同时扩容会出现循环列表
  - HashMap在jdk1.8之后引入了红黑树的概念，表示若桶中链表元素超过8时，会自动转化成红黑树；若桶中元素小于等于6时，树结构还原成链表形式。
    - 选择6和8的原因
      - 中间有个差值7可以防止链表和树之间频繁的转换
    - 不安全主要发生在扩容时，容易产生循环链表

- TreeMap
- HashTable
- LinkedHashMap
- ConcurrentHashMap
  - 1.7与1.8的区别
    - 1.8使用Unsafe类的CAS自旋赋值+synchronized同步+LockSupport阻塞等手段实现的高效并发
    - 采用头插法

### Iterator和ListIterator

- ListIterator有add()方法，可以向List中添加对象，而Iterator不能
- iterator()方法在set和list接口中都有定义，ListIterator（）仅存在于list接口中（或实现类中）
- ListIterator有hasPrevious()和previous()方法，可以实现逆向（顺序向前）遍历
- ListIterator可以定位当前的索引位置，nextIndex()和previousIndex()可以实现。Iterator没有此功能

### queue

- PriorityQueue

### fail-fast机制

- 集合结构上发生了改变（.remove(i)）该机制将尽最大努力抛出异常

## jvm

### JVM的栈上分配与逃逸分析(Escape Analysis）

- 原本分配到堆上的对象分配到栈上

### 内存分配与回收策略

- Minor gc
- Major gc
- Full gc
- 如何减少gc的次数

  - 尽量少用静态变量
  - 对象不用时最好显式置为null
  - 增大堆的最大值设置
  - 尽量使用stringBuffer而不是string，减少不必要的中间对象
  - 经常使用的图片可以使用软引用类型

### 内存泄漏（无法释放已申请的内存空间）

- 什么条件下会造成内存泄漏

  - 对象可达但是无用

- 内存泄漏的场景

  - 循环创建对象
  - 各种连接没有及时释放资源

- 使用Jconsole查找内存泄漏

### 内存溢出（没有足够的内存供申请者使用）

- 虚拟机和本地方法栈溢出
- 堆溢出
- 方法区溢出
- 内存映像分析工具（eclipse）

  - 对dump出来的堆转存快照

### 调优工具

- jmap

  - 用于生成堆转储快照文件（某一时刻的）

- jhat

  - 对生成的堆转储快照文件进行分析

- jconsole

  - 内存监控和线程监控

- 通过jvm 查看死锁

  - jstack -l jvm_pid

### new的对象如何不分配在堆而分配在栈上

- 方法逃逸

## 多线程

### 线程

- 创建线程的方式

  - runnable
  - callable

    - future
    - future task
    - Callable接口的任务线程能返回执行结果

  - Thread
  - 一个类可以同时继承Thread和实现Runnable接口
  - 实现Callable接口的任务线程能返回执行结果；而实现Runnable接口的任务线程不能返回结果
  - future的底层实现异步原理

    - 提供了三种功能

      - 判断任务是否完成
      - 能够中断任务
      - 能够获取任务执行结果

    - future的底层实现异步原理

      - 在客户端请求的时候，直接返回客户端需要的数据（此数据不一定完整，只是简单的一点不耗时的操作），但是客户端并不一定马上使用所有的信息，此时就有了时间去完善客户需要的信息

    - 与FutureTask的区别和联系
      - future是个接口，futuretask可以通过实现该接口，
调用get方法返回执行结果

- 守护线程

  - 守护线程通常执行一些任务,当所有非守护线程终止的时候,J
VM简单的丢弃掉所有现存的守护线程.一旦其它非守护线程执
行完,不一定所有的守护线程都会执行完才退出,它们可能在非
守护线程执行完后的某个时刻退出
  - 使用场景

    - 来为其它线程提供服务支持.

- 线程上下文切换
- 线程的状态

  - 创建、就绪、运行、阻塞、死亡

- 线程调度器

  - 负责为runnable状态线程分配cpu时间

### 线程池

- 创建线程池的方式

  - 创建线程池

    - newSingleThreadExecutor（单线程线程池）

      - 适用场景

        - 适用于串行执行任务的场景

    - newFixedThreadPool（固定大小线程池）

      - 特点

        - coresize和maxsize相同
        - 队列用的LinkedBlockingQueue无界
        - keepAliveTime为0

      - 工作机制

        - 1.线程数少于核心线程数，新建线程执行任务
        - 2.线程数等于核心线程数后，将任务加入阻塞队列
        - 3.执行完任务的线程反复去队列中取任务执行

      - 适用场景

        - 适用于处理CPU密集型的任务，确保CPU在长期被工作线程使用的情况下，尽可能的少的分配线程即可。一般Ncpu+1

    - newCachedThreadPool（可缓存线程的线程池）

      - 特点

        - 核心线程数为0，且最大线程数为Integer.MAX_VALUE
        - 阻塞队列是SynchronousQueue
        - keepAliveTime为60s

      - 工作机制

        - 1.没有核心线程，直接向SynchronousQueue中提交任务
        - 2如果有空闲线程，就去取出任务执行；如果没有空闲线程，就新建一个
        - 3.执行完任务的线程有60秒生存时间，如果在这个时间内可以接到新任务，就继续，否则结束生命

      - 适用场景

        - 用于并发执行大量短期的小任务

    - newScheduledThreadPool

      - 特点

        - 最大线程数为Integer.MAX_VALUE
        - 阻塞队列是DelayedWorkQueue

      - 工作机制

        - 1.线程从 DelayQueue 中获取 time 大于等于当前时间的
        - 2.执行完后修改这个 task 的 time 为下次被执行的时间
        - 3.再把这个 task 放回队列中

      - 适用场景

        - 用于需要多个后台线程执行周期任务，同时需要限制线程数量的场景。

  - 两种启动线程池的方法：submit（有返回值）和execute（无返回值）
  - 线程池的核心

    - 生产者消费者模型

      - 生产者将需要处理的任务放入队列
      - 消费者从任务队列中取出任务处理

  - 线程池的参数（ThreadPoolExecutor）

    - maximumPoolSize：最大线程数
    - corePollSize：核心线程数
    - keepAliveTime：空闲的线程保留的时间
    - workQueue任务队列）：用于保存等待执行的任务的阻塞队列
    - ThreadFactory
      - 用于设置创建线程的工厂，可以通过线程工厂给每个创建出来的线程做些更有意义的事情，比如设置daemon和优先级等等

    - RejectedExecutionHandler（饱和策略）
      - AbortPolicy：直接抛出异常。
      - CallerRunsPolicy：只用调用者所在线程来运行任务。
      - DiscardOldestPolicy：丢弃队列里最近的一个任务，并执行当前任务。
      - DiscardPolicy：不处理，丢弃掉。
    - TimeUnit：空闲线程的保留时间单位

- 单机上一个线程正在处理服务，如果忽然断电了怎么办（正在处理和阻塞队列里的请求怎么处理）
  - 阻塞队列持久化，正在处理事物控制。断电之后正在处理的回滚，日志恢复该次操作。服务器重启后阻塞队列中的数据再加载
- 线程池关闭相关操作
  - shutdown
    - shutdown()后线程池将变成shutdown状态，此时不接收新任务，但会处理完正在运行的 和 在阻塞队列中等待处理的任务。

  - shutdownNow
    - shutdownNow()后线程池将变成stop状态，此时不接收新任务，不再处理在阻塞队列中等待的任务，还会尝试中断正在处理中的工作线程。

### 阻塞队列

- 支持两个附加操作

  - 当队列满时，存储元素的线程会等待队列可用
  - 当队列空时，获取元素的线程会等待队列变为非空

- 线程池队列

  - ArrayBlockingQueue（有界队列）

    - 是一个基于数组结构的有界阻塞队列，此队列按 FIFO（先进先出）原则对元素进行排序
    - 可以指定缓存队列的大小，当正在执行的线程数等于corePoolSize时，多余的元素缓存在ArrayBlockingQueue队列中等待有空闲的线程时继续执行，当ArrayBlockingQueue已满时，加入ArrayBlockingQueue失败，会开启新的线程去执行，当线程数已经达到最大的maximumPoolSizes时，再有新的元素尝试加入ArrayBlockingQueue时会报错

  - LinkedBlockingQueue（无界队列）
    - 一个基于链表结构的阻塞队列，此队列按FIFO （先进先出） 排序元素，吞吐量通常要高于ArrayBlockingQueue。静态工厂方法Executors.newFixedThreadPool()使用了这个队列。
    - maximumPoolSizes为无效
      - 当前执行的线程数量达到corePoolSize的数量时，剩余的元素会在阻塞队列里等待

  - SynchronousQueue（同步队列）
    - 一个不存储元素的阻塞队列。每个插入操作必须等到另一个线程调用移除操作，否则插入操作一直处于阻塞状态，吞吐量通常要高于LinkedBlockingQueue，静态工厂方法Executors.newCachedThreadPool使用了这个队列。
    - maximumPoolSizes为无界
      - 使用SynchronousQueue阻塞队列一般要求maximumPoolSizes为无界，避免线程拒绝执行操作

    - 特点
      - SynchronousQueue 队列中没有任何缓存的数据，可以理解为容量为 0
      - SynchronousQueue 提供两种实现方式，分别是
    - 一个具有优先级得无限阻塞队列

### 判断线程是否停止的方法interrupted和isinterrupted的区别

- interrupted

  - 静态方法
  - 作用于当前正在运行的线程
  - 会清除线程中断状态

- isinterrupted

  - 非静态方法
  - 作用于该方法的调用对象所对应的线程

### 三个线程交替顺序打印ABC

- 使用synchronized, wait和notifyAll
- 使用Lock->ReentrantLock 和 state标志
- 使用Lock->ReentrantLock 和
Condition（await 、signal、signalAll）
- 使用Semaphore
- 使用AtomicInteger

### 多线程中join()方法

- t.join()方法只会使主线程进入等待池并等待t线程
执行完毕后才会被唤醒。并不影响同一时刻处在
运行状态的其他线程

### 缓存一致性问题

- 加lock锁
- 缓存一致性协议

### ThreadLocal

- 相当于一个容器，用于存放每个线程的局部变量
- 底层也是封装了ThreadLocalMap集合类来绑定当
前线程和变量副本的关系，各个线程独立并且访问安全

### sleep()、wait

### notify和notifyAll

### run和start

### 锁优化

- 减少锁的持有时间
- 减少锁得用于粒度
- 锁分离

  - 读锁
  - 写锁

- 锁粗化

  - 如果一段程序要多次请求锁，锁之间的代码执行时间比较少，就应该整合成一个锁

- 自旋锁（不可重入锁）
- 锁清除

  - 堆检测到不可能存在共享数据竞争的锁进行清除（逃逸分析技术）

- 锁降级

  - 指的是把持住(当前拥有的)写锁，再获取到读锁，随后释放(先前有用的)写锁的过程

### volatile

- 可见性
  - 底层是共享变量
- 禁止重排序
  - 内存屏障
    - LoadLoad
    - StoreStore
    - LoadStore
    - StoreLoad

- 内部实现机制

  - 将当前内核高速缓存行的数据立刻回写到内存
  - 使在其他内核里缓存了该内存地址的数据无效
  - MESI协议，该解决缓存一致性的思路是：当CPU写数据时，如果发现操作的变量是共享变量，即在其他CPU中也存在该变量的副本，那么他会发出信号通知其他CPU将该变量的缓存行设置为无效状态。当其他CPU使用这个变量时，首先会去嗅探是否有对该变量更改的信号，当发现这个变量的缓存行已经无效时，会从新从内存中读取这个变量。

### 用户态和核心态

### 无锁化编程实现线程安全

- final（数据不可修改）
- CAS
- 线层本地存储ThreadLocal（私藏）
- 原子类
- Copy-on-write

### 读写锁

- 写独占，读共享，写锁优先级高（本质上是一种自旋锁）

### 如何判断一个线程是否拥有锁

- Thread的holdsLock方法

### happens-before原则

- 如果前一个操作(A)必须要对后一个操作（C）可见 ，那么这两个操作（A C） 指令不能重排

### 乐观锁（适用于大并发量）

- CAS
- atomic

### 悲观锁（适用于并发量不大的场景）

- Lock

  - 悲观锁、可中断锁、可公平锁、可重入锁)

- synchronized

  - 悲观锁、不可中断锁、非公平锁、可重入锁)
  - 底层通过操作系统的互斥量实现，适用于竞争不激烈的场景

### 可重入锁和不可重入锁（自旋锁）

- 可重入锁实现原理：当一个线程请求成功后，JVM会记下持有锁的线程，
并将计数器计为1。此时其他线程请求该锁，则必须等待；
而该持有锁的线程如果再次请求这个锁，就可以再次拿到这个锁，同时计数器会递增

### synchronized 和 volatile 的区别是什么

- volatile本质是在告诉jvm当前变量在寄存器（工作内存）中的值是不确定的，
需要从主存中读取； synchronized则是锁定当前变量，只有当前线程可以
访问该变量，其他线程被阻塞住
- volatile仅能使用在变量级别；synchronized则可以使用在变量、方法、和类级别的
- volatile仅能实现变量的修改可见性，不能保证原子性；
而synchronized则可以保证变量的修改可见性和原子性
- volatile不会造成线程的阻塞；synchronized可能会造成线程的阻塞
- volatile标记的变量不会被编译器优化；synchronized标记的变量可以被编译器优化

### synchronized 和 ReentrantLock 区别是什么

- synchronized是关键字、ReentrantLock是类

  - ReentrantLock是类，那么它就提供了比synchronized更多更灵活的特性，
可以被继承、可以有方法、可以有各种各样的类变

- ReentrantLock可以对获取锁的等待时间进行设置
- ReentrantLock可以获取各种锁的信息
- sychronized是不可中断锁、非公平锁；ReentrantLock是可中断，可公平锁
- ReentrantLock需在finally中手工释放锁

### 高并发系统限流中的算法

- 漏桶算法

  - 一个固定容量的漏桶，按照固定常量速率流出请求，
流入请求速率任意，当流入的请求数累积到漏桶容量时，
则新流入的请求被拒绝

- 令牌桶算法

  - 一个存放固定容量令牌的桶，按照固定速率往桶里添加令牌，填满了就丢弃令牌，请求是否被处理要看桶中令牌是否足够，当令牌数减为零时则拒绝新的请求

- 计数器限流算法

  - 用来限制一定时间内的总并发数，比如数据库连接池、线程池、秒杀的并发数

## JUC

### Semaphore

- Semaphore翻译成字面意思为 信号量，Semaphore可以控同时访问的线程
个数，通过 acquire() 获取一个许可，如果没有就等待，而 release() 释放一个许可
- 主要用来限流
- 核心就是自增自减，通过内部类：abstract static class Sync extends AbstractQueuedSynchronizer

### CountDownLatch

- CountDownLatch 类中主要的方法

  - await 当前线程等待直到计数器为0
  - countDown();          //调用此方法则计数减1

- 使用场景

  - 开启多个线程分块下载一个大文件，每个线程只下载固定的一截，最后由另外一个线程来拼接所有的分段
  - 应用程序的主线程希望在负责启动框架服务的线程已经启动所有的框架服务之后再执行
  - 确保一个计算不会执行，直到所需要的资源被初始化

- 原理

  - 在并发环境下由线程进行减1操作，当计数值变为0之后，被await方法阻塞的线程将会唤醒，实现线程间的同步
  - 还是内部类来维护同步：private static final class Sync extends AbstractQueuedSynchronizer

- 与CyclicBarrier的区别

  - CountDownLatch强调一个线程等多个线程完成某件事情。CyclicBarrier是多个线程互等，等大家都完成。
  - CountDownLatch减计数，CyclicBarrier加计数
  - CountDownLatch是一次性的，CyclicBarrier可以重用
  - 原理

    - CycliBarrier 主要是依赖于 ReenTrantLock 来实现线程同步安全的

### SynchronousQueue LinkedBlockingQueue ArrayBlockingQueue

### CyclicBarrier

- 循环屏障，让一组线程到达一个屏障（同步点）被阻塞，直到最后一个线程到达屏障时，屏障才打开

### CopyOnWriteArrayList, CopyOnWriteArraySet和ConcurrentSkipListSet

### ConcurrentHashMap

### Future

- FutureTask

### ReentrantLock

- 适用于竞争激烈的场景
- ReentrantLock的API里面，
lock()和trylock()的区别？

  - lock函数是阻塞的
  - trylock()是非阻塞的，调用后立即返回

### 阻塞队列s

- 同步阻塞队列

  - 如果一个线程获取锁失败，则会采用CAS机制把该线程封装成节点加入到队列的尾部
  - 同步队列遵循FIFO，首节点拥有锁，释放的时候会把后续节点设置为首节点，由于此时只有一个线程获取锁，所以此时设置的时候是单线程的，不需要CAS机制，

## 设计模式

### 单例模式

- 懒汉

  - synchroinzed

- 饿汉
- 双重校验锁

  - volatile/synchronized

- 使用场景：网站计数器、windows系统的任务管理器

### 观察者模式

- zookeeper的设计模式

### 装饰者模式

- java I/O库是由一些基本的原始流处理器和
围绕它们的装饰流处理器所组成的

### 适配器模式

- Java的I/O类库中有许多这样的需求，如将字符串转成字节数据保存到文件中，将字节数据变成数据流等。
具体来说，InputStreamReader和OutputStreamWriter就是适配器的体现

### 工厂模式

- hibernate里通过sessionFactory创建session、通过代理方式生成ws客户端时，
通过工厂构建报文中格式化数据的对象

### 代理模式

- 静态代理和动态代理的区别

  - 在程序运行前就已经存在代理类的字节码文件，代理类和委托类的关系在运行前就确定了。

    - 静态代理通常只代理一个类

  - 代理类和委托类的关系是在程序运行时确定。

    - 动态代理是代理一个接口下的多个实现类

### 设计模式之六大原则

- 单一职责原则

  - 一个类只负责一个功能领域中的相应职责

- 开闭原则

  - 一个软件实体应当对扩展开放，对修改关闭

- 里氏替换原则

  - 所有引用基类（父类）的地方必须能透明地使用其子类的对象

- 依赖倒置原则

  - 需要针对抽象层编程，而将具体类的对象通过依赖注入(DependencyInjection, DI)的方式注入到其他对象中

- 接口隔离原则

  - 当一个接口太大时，我们需要将它分割成一些更细小的接口

- 迪米特法则

  - 一个模块发生修改时，应该尽量少地影响其他模块

## JDK1.9特性

### Java 平台模块系统的引入，创建出只包含所依赖的 JDK 模块的自定义运行时镜像，极大的减少 Java 运行时环境的大小

### shell 为 Java 增加了类似 NodeJS 和 Python 中的读取-求值-打印循环，在 jshell 中可以直接输入表达式并查看其执行结果

### j子主题在集合上，Java 9 增加 了 List.of()、Set.of()、Map.of() 和 Map.ofEntries()等工厂方法来创建不可变集合

## JDK8的特性

### Lambda 表达式 − Lambda允许把函数作为一个方法的参数

### 方法引用 − 方法引用提供了非常有用的语法，可以直接引用已有Java类或对象（实例）的方法或构造器

### Stream API −新添加的Stream API，允许以声明性方式处理数据集合

- JDK8 Stream 详细使用

  - Stream 的获取

    - 通过集合Collection获取
    - 通过数组获取
    - 直接通过值获取

  - Stream 常用管道操作

    - 筛选 filter
    - 去重 distinct
    - 截取流的前N个元素:limit
    - 跳过流的前n个元素skip
    - 合并多个流 flatMap
    - 归约统计：求最值、均值

### Date Time API − 加强对日期与时间的处理

## java三大器

### 过滤器

- 原理

  - 函数回调

- 适用场景

  - url级别的权限访问控制
  - 过滤敏感词汇

### 监听器

- 原理

  - 基于事件

- 适用场景

  - 统计网站在线人数
  - 清楚过期session

### 拦截器(Interceptor)

- 概念

  - 拦截器用于在某个方法或者字段被访问之前，进行拦截然后再之前或者之后加入某些操作

- 原理

  - 基于JDK实现的动态代理

- 场景

  - 拦截未登录用户
  - 审计日志

- Spring拦截器：HandlerInterceptor接口和HandlerInterceptorAdapter类
