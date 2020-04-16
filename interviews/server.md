# 后台开发可能问到的比较深的问题

## STL 各类容器的底层实现
1. vector: 数组，动态增长
2. array: 数组，不增长
3. map multimap: 红黑树
4. set multiset: 红黑树
5. 优先队列: 堆
6. unordered_map: 哈希表

## 链表逆置
头插法、尾插法、就地逆置

## 分布式系统
## 设计模式
## Redis 分布式的实现
## 分库分表

刚开始我们只用单机数据库就够了，随后面对越来越多的请求，**我们将数据库的写操作和读操作进行分离， 使用多个从库副本（Slaver Replication）负责读，使用主库（Master）负责写， 从库从主库同步更新数据，保持数据一致。** 架构上就是数据库主从同步。 从库可以水平扩展，所以更多的读请求不成问题。

但是当用户量级上来后，写请求越来越多，该怎么办？加一个Master是不能解决问题的， 因为数据要保存一致性，写操作需要2个master之间同步，相当于是重复了，而且更加复杂。
**这时就需要用到分库分表（sharding），对写操作进行切分。**

**解决方法** ：分散请求到多个服务器上； 其实用户请求和执行一个sql查询是本质是一样的，都是请求一个资源，只是用户请求还会经过网关，路由，http服务器等。

**垂直切分和水平切分**
- 单个库太大： 单个数据库处理能力有限；单库所在服务器上磁盘空间不足；单库上操作的IO瓶颈 解决方法：切分成更多更小的库。**如果是因为表多而数据多，使用垂直切分，根据业务切分成不同的库。**
- 单个表太大： CRUD都成问题；索引膨胀，查询超时 解决方法：切分成多个数据集更小的表。**如果是因为单张表的数据量太大，这时要用水平切分 ，即把表的数据按某种规则切分成多张表，** 甚至多个库上的多张表。 **分库分表的顺序应该是先垂直分，后水平分。** 因为垂直分更简单，更符合我们处理现实世界问题的方式。

**垂直分表**

也就是“大表拆小表”，基于列字段进行的。一般是表中的字段较多，将不常用的， 数据较大，长度较长（比如text类型字段）的拆分到“扩展表“。 一般是针对那种几百列的大表，也避免查询时，数据量太大造成的“跨页”问题。

**垂直分库**

垂直分库针对的是一个系统中的不同业务进行拆分，比如用户User一个库，商品Producet一个库，订单Order一个库。 切分后，要放在多个服务器上，而不是一个服务器上。

我们想象一下，一个购物网站对外提供服务，会有用户，商品，订单等的CRUD。没拆分之前， 全部都是落到单一的库上的，这会让数据库的单库处理能力成为瓶颈。按垂直分库后，如果还是放在一个数据库服务器上， 随着用户量增大，这会让单个数据库的处理能力成为瓶颈，还有单个服务器的磁盘空间，内存，tps等非常吃紧。 所以我们要拆分到多个服务器上，这样上面的问题都解决了，以后也不会面对单机资源问题。

**水平分表**

针对数据量巨大的单张表（比如订单表），按照某种规则（RANGE,HASH取模等），切分到多张表里面去。 但是这些表还是在同一个库中，所以库级别的数据库操作还是有IO瓶颈。不建议采用。

**水平分库分表**

将单张表的数据切分到多个服务器上去，每个服务器具有相应的库与表，只是表中数据集合不同。 水平分库分表能够有效的缓解单机和单库的性能瓶颈和压力，突破IO、连接数、硬件资源等的瓶颈。

**水平分库分表的切分规则**

1. **range** 0-10000 一个表， 10001-20000一个表；
2. **哈希取模** 一个商场系统，一般都是将用户，订单作为主表，然后将和它们相关的作为附表，这样不会造成跨库事务之类的问题。 **取用户id，然后hash取模，分配到不同的数据库上。**
3. **地理区域** 按地区区分业务，比如 华东、华南、华北等；
4. **时间** 按照时间切分，将更久以前的数据切分到另一张表上，因为比较久的数据被访问的可能性小，没必要和热数据放在一起。

**分库分表产生的问题**
1. **事务变成了分布式事务。**
2. **多个库的查询结果集合并。**
3. **跨库 join** 分库分表后表之间的关联操作将受到限制，我们无法join位于不同分库的表，也无法join分表粒度不同的表， 结果原本一次查询能够完成的业务，可能需要多次查询才能完成。**粗略的解决方法** ： 全局表：基础数据，所有库都拷贝一份。 字段冗余：这样有些字段就不用join去查询了。 系统层组装：分别查询出所有，然后组装起来，较复杂。

## 链表逆置（头插法、尾插法）
## 数据库事务已经发生死锁了该如何解决？
## 几种锁

**参考**
1. [解决死锁之路（终结篇） - 再见死锁](https://www.aneasystone.com/archives/2018/04/solving-dead-locks-four.html)

## 一致性哈希
**问题由来** ：在使用n台缓存服务器时，一种常用的负载均衡方式是，对资源o的请求使用`hash(o) mode n`来映射到某一台缓存服务器。当增加或减少一台缓存服务器时这种方式可能会改变所有资源对应的hash值，也就是所有的缓存都失效了，这会使得缓存服务器大量集中地向原始内容服务器更新缓存。因此需要一致哈希算法来避免这样的问题。 一致哈希尽可能使同一个资源映射到同一台缓存服务器。这种方式要求增加一台缓存服务器时，新的服务器尽量分担存储其他所有服务器的缓存资源。减少一台缓存服务器时，其他所有服务器也可以尽量分担存储它的缓存资源。 一致哈希算法的主要思想是将每个缓存服务器与一个或多个哈希值域区间关联起来，其中区间边界通过计算缓存服务器对应的哈希值来决定。（定义区间的哈希函数不一定和计算缓存服务器哈希值的函数相同，但是两个函数的返回值的范围需要匹配。）如果一个缓存服务器被移除，则它所对应的区间会被并入到邻近的区间，其他的缓存服务器不需要任何改变。

**适用于分布式系统，当数据量特别大时需要做分布式处理。** 假设，我们有一个社交网站，需要使用Redis存储图片资源，存储的格式为键值对，key值为图片名称，value为该图片所在文件服务器的路径，我们需要根据文件名查找该文件所在文件服务器上的路径，数据量大概有2000W左右，按照我们约定的规则进行分库，规则就是随机分配，我们可以部署8台缓存服务器，每台服务器大概含有500W条数据，并且进行主从复制。

可想而知，如果我们使用Hash的方式，每一张图片在进行分库的时候都可以定位到特定的服务器。假设我们查找的是”a.png”，由于有4台服务器（排除从库），因此公式为hash(a.png) % 4 = 2 ，可知定位到了第2号服务器，这样的话就不会遍历所有的服务器，大大提升了性能！

上述的方式虽然提升了性能，我们不再需要对整个Redis服务器进行遍历！但是，使用上述Hash算法进行缓存时，**会出现一些缺陷，主要体现在服务器数量变动的时候，所有缓存的位置都要发生改变！** 假设：我们增加了一台缓存服务器，那么缓存服务器的数量就由4台变成了5台。那么原本hash(a.png) % 4 = 2 的公式就变成了hash(a.png) % 5 = ？ ， 可想而知这个结果肯定不是2的，这种情况带来的结果就是当服务器数量变动时，所有缓存的位置都要发生改变！换句话说，当服务器数量发生改变时，所有缓存在一定时间内是失效的，当应用无法从缓存中获取数据时，则会向后端数据库请求数据。同样的，假设4台缓存中突然有一台缓存服务器出现了故障，无法进行缓存，那么我们则需要将故障机器移除，但是如果移除了一台缓存服务器，那么缓存服务器数量从4台变为3台，也是会出现上述的问题！

**一致性Hash算法也是使用取模的方法，只是，刚才描述的取模法是对服务器的数量进行取模，而一致性Hash算法是对2^32取模。** 下一步将各个服务器使用Hash进行一个哈希，具体可以选择服务器的IP或主机名作为关键字进行哈希，这样每台机器就能确定其在**哈希环**上的位置。接下来使用如下算法定位数据访问到相应服务器：将数据key使用相同的函数Hash计算出哈希值，并确定此数据在环上的位置，从此位置沿环顺时针“行走”，第一台遇到的服务器就是其应该定位到的服务器！

**现假设Node C不幸宕机**，可以看到此时对象A、B、D不会受到影响，只有C对象被重定位到Node D。一般的，在一致性Hash算法中，如果一台服务器不可用，则受影响的数据仅仅是此服务器到其环空间中前一台服务器（即沿着逆时针方向行走遇到的第一台服务器）之间数据，其它不会受到影响。

下面考虑另外一种情况，**如果在系统中增加一台服务器Node X** 。此时对象Object A、B、D不受影响，只有对象C需要重定位到新的Node X ！一般的，在一致性Hash算法中，如果增加一台服务器，则受影响的数据仅仅是新服务器到其环空间中前一台服务器（即沿着逆时针方向行走遇到的第一台服务器）之间数据，其它数据也不会受到影响。

**优点**：
1. 增减机器时，只会造成一小部分的数据发生变化；

**缺点**：
1. 一致性Hash算法在服务节点太少时，容易因为节点分部不均匀而造成数据倾斜。

**好的一致性哈希算法应该满足的特性**
1. **平衡性** :平衡性是指哈希的结果能够尽可能分布到所有的缓冲中去，这样可以使得所有的缓冲空间都得到利用。很多哈希算法都能够满足这一条件。
2. **单调性** :单调性是指如果已经有一些内容通过哈希分派到了相应的缓冲中，又有新的缓冲区加入到系统中，那么哈希的结果应能够保证原有已分配的内容可以被映射到新的缓冲区中去，而不会被映射到旧的缓冲集合中的其他缓冲区。简单的哈希算法往往不能满足单调性的要求，如最简单的线性哈希：x = (ax + b) mod (P)，在上式中，P表示全部缓冲的大小。不难看出，当缓冲大小发生变化时(从P1到P2)，原来所有的哈希结果均会发生变化，从而不满足单调性的要求。哈希结果的变化意味着当缓冲空间发生变化时，所有的映射关系需要在系统内全部更新。而在P2P系统内，缓冲的变化等价于Peer加入或退出系统，这一情况在P2P系统中会频繁发生，因此会带来极大计算和传输负荷。单调性就是要求哈希算法能够应对这种情况。
3. **分散性** :在分布式环境中，终端有可能看不到所有的缓冲，而是只能看到其中的一部分。当终端希望通过哈希过程将内容映射到缓冲上时，由于不同终端所见的缓冲范围有可能不同，从而导致哈希的结果不一致，最终的结果是相同的内容被不同的终端映射到不同的缓冲区中。这种情况显然是应该避免的，因为它导致相同内容被存储到不同缓冲中去，降低了系统存储的效率。分散性的定义就是上述情况发生的严重程度。好的哈希算法应能够尽量避免不一致的情况发生，也就是尽量降低分散性。
4. **负载** :负载问题实际上是从另一个角度看待分散性问题。既然不同的终端可能将相同的内容映射到不同的缓冲区中，那么对于一个特定的缓冲区而言，也可能被不同的用户映射为不同的内容。与分散性一样，这种情况也是应当避免的，因此好的哈希算法应能够尽量降低缓冲的负荷。
5. **平滑性** :平滑性是指缓存服务器的数目平滑改变和缓存对象的平滑改变是一致的。

**参考**
1. [面试必备：什么是一致性Hash算法？](https://zhuanlan.zhihu.com/p/34985026)
2. [五分钟看懂一致性哈希算法](https://juejin.im/post/5ae1476ef265da0b8d419ef2)

## 并查集
**概念简介** :并查集，在一些有N个元素的集合应用问题中，我们通常是在开始时让每个元素构成一个单元素的集合，然后按一定顺序将属于同一组的元素所在的集合合并，其间要反复查找一个元素在哪个集合中。

**思想** 用集合里的某个元素代表这个几何，该元素成为集合的代表元，一个集合内的所有元素组织成以代表元为根的树形结构。

**操做** 
1. 合并: 将两个子集合并成同一个集合。
2. 查找: 确定元素属于哪一个子集。它可以被用来确定两个元素是否属于同一子集。
3. 路径压缩：寻找祖先时采用递归，但是一旦元素一多起来，或退化成一条链，每次GetFather都将会使用`O(N)`的复杂度，这显然不是我们想要的。对此，我们必须要进行路径压缩，即我们找到最久远的祖先时“顺便”把它的子孙直接连接到它上面。这就是路径压缩了。

**应用** 
1. 维护无向图的连通性，支持判断两个顶点是否在同一个连通块内，支持判断增加一条边是否会产生环。
2. 用在求解最小生成树的 kruskal 算法里。

**参考**
1. [并查集入门](https://zhuanlan.zhihu.com/p/33619824)

## 全局变量和static变量的区别.如果在两个.h文件中声明两个同名变量会怎么样？ 如果使用extern？ 如果没有使用？

**static作用**
1. 修饰类的静态变量；
2. 修饰函数的局部静态变量；
3. 修饰全局静态变量；
4. 修饰类的静态成员函数；
5. 修饰模块内函数，限定作用域范围仅在当前文件；

**extern是C/C++语言中表明函数和全局变量作用范围（可见性）的关键字** ，该关键字告诉编译器，其声明的函数和变量可以在本模块或其它模块中使用。

仅仅是一个变量的声明，其并不是在定义变量a，并未为a分配内存空间。变量a在所有模块中作为一种全局变量只能被定义一次，否则会出现连接错误。

通常，**在模块的头文件中对本模块提供给其它模块引用的函数和全局变量以关键字extern声明** 例如，如果模块B欲引用该模块A中定义的全局变量和函数时只需包含模块A的头文件即可。这样，模块B中调用模块A中的函数时，在编译阶段，模块B虽然找不到该函数，但是并不会报错；它会在连接阶段中从模块A编译生成的目标代码中找到此函数。

**与extern对应的关键字是static 被它修饰的全局变量和函数只能在本模块中使用** 因此，一个函数或变量只可能被本模块使用时，其不可能被extern “C”修饰。

--- 利用extern关键字先声明一下num变量，告诉编译器num这个变量是存在的，但是不是在这之前声明的，你到别的地方找找吧，果然，这样就可以顺利通过编译啦。如果extern这个关键字就这点功能，那么这个关键字就显得多余了，因为上边的程序可以通过将num变量在main函数的上边声明，使得在main函数中也可以使用。
extern这个关键字的真正的作用是引用不在同一个文件中的变量或者函数。

**函数**

**函数的声明和定义默认都是 extern 的, 即全局可见的. 所以在声明和定义的时候, 默认都是 extern的. **static修饰的 function 表明这个函数只对于当前文件中的其他函数是可见的, 其他文件中的函数不能够调用.

```C++
#include<stdio.h>

int func();

int main()
{
    func(); //1
    extern int num;
    printf("%d",num); //2
    return 0;
}

int num = 3;

int func()
{
    printf("%d\n",num);
}

extern "C"
{
    // 用来保持和C的兼容
}
```

## explicit 作用
用来阻止隐式类型转换发生；C++ 中只有一个参数的构造函数可能会进行隐式类型转换，在某些情况下可能会违背程序员的意愿。 explicit 阻止了这种隐式类型转换的发生。

## 判断链表有环，找到环开始的点
1. 双指针法，一个慢指针一次移动一个距离，一个快指针一次移动两个距离；
2. 我们在第一次相遇时，把慢指针留在原地，把快指针放回起点head处，然后把快指针变为慢指针，**两个指针一起以速度1前进，当它们相遇时** ，相遇点就是入环点4；

## IO复用 select poll epoll 区别 底层实现原理

**Epoll与Select区别以及epoll优点，为什么一般情况下epoll性能比select好，ET模式与LT模式**

**如何用epoll实现高并发，多线程，线程池，线程惊群问题**

**多个线程同时使用 epoll_wait 会怎样**

## 多阶哈希表
解决哈希表冲突的一种方法，多阶哈希表。多阶哈希表其实就是一个锯齿般的数组。

1. 每一行是一阶，上面的元素个数多，下面的元素个数依次减少. 每一行的元素个数都是素数. 每一阶数组的每一个节点用于存储数据的内容，其中，节点的前四个字节用来存储int类型的Key或者是hash_code.
 2. **创建多阶HASH的时候，用户通过参数来指定有多少阶，每一阶做最多有多少个元素** 那么每一阶应该选择多少个元素呢？ 这里采用了素数集中原理的算法来查找. 假如每阶最多有1000个元素，一共10阶，则算法选择十个比1000小的最大素数，从大到小排列，以此作为各阶的元素个数. 通过素数集中的算法得到的10个素数分别是： 997 991 983 977 971 967 953 947 941 937. 可见虽然是锯齿数组，各层之间的差别并不是很多.
3. 查找的过程，先将key在第一阶内取模，看是否是这个元素，如果这个位置为空，直接返回不存在; 如果是这个key，则返回这个位置. **如果这个位置有元素，但是又不是key，则说明hash冲突了，再去第二阶去寻找. 循环往复.**

**和开链法比较**
1. 冲突处理也很简单，开链法非常极端的情况下时间复杂度是 O(N)；
2. 在增容问题上，哈希桶却不占优势，因为它需要一个数据搬迁的过程
3. 多阶哈希初始化时很占空间；哈希桶是来一个插入一个，对空间的利用率很高，并不会浪费很多空间。而多阶哈希在创建时就需要开辟一大段空间，这对空间无形中是一种浪费。
4. 缺点，每次要做K次哈希处理， 如果K阶都被占用了，则可能不能插入；


**参考** 
1. [多阶哈希表](https://blog.csdn.net/Dawn_sf/article/details/79506520)


**参考**
1. [C语言正确使用extern关键字](https://blog.csdn.net/xingjiarong/article/details/47656339)

## TCB PCB 线程控制块 进程控制块
为了描述控制进程的运行，系统中存放进程的管理和控制信息的数据结构称为进程控制块（PCB Process Control Block），它是进程实体的一部分，是操作系统中最重要的记录性数据结构。它是进程管理和控制的最重要的数据结构，每一个进程均有一个PCB，在创建进程时，建立PCB，伴随进程运行的全过程，直到进程撤消而撤消。

在Unix或类Unix系统中，**进程是由进程控制块，进程执行的程序，进程执行时所用数据，进程运行使用的工作区组成** 。其中进程控制块是最重要的一部分。
PCB一般包括：
1. 程序ID（PID、进程句柄）：它是唯一的，一个进程都必须对应一个PID。PID一般是整形数字
2. 特征信息：一般分系统进程、用户进程、或者内核进程等
3. 进程状态：运行、就绪、阻塞，表示进程现的运行情况
4. 优先级：表示获得CPU控制权的优先级大小
5. 通信信息：进程之间的通信关系的反映，由于操作系统会提供通信信道
6. 现场保护区：保护阻塞的进程用
7. 资源需求、分配控制信息
8. 进程实体信息，指明程序路径和名称，进程数据在物理内存还是在交换分区（分页）中
9. 其他信息：工作单位，工作区，文件信息等

线程控制块（Thread Control Block，TCB）是与进程的控制块（PCB）相似的子控制块，只是TCB中所保存的线程状态比PCB中保存少而已（当然可以说这个定义是浅显或错误的）。

## 守护进程、僵尸进程、孤儿进程，守护进程的作用是什么？
- **僵尸进程** : 退出后，父进程没有调用 `wait,waitpid` 回收子进程的状态信息，那么子进程的进程描述符仍然保存在操作系统内。
- **孤儿进程** : 一个父进程退出后，子进程依然在运行，那么子进程会变成孤儿进程。孤儿进程会被init进程收养（进程号 1）。
- **守护进程** : 是一种在后台执行的电脑程序。此类程序会被以进程的形式初始化。通常，守护进程没有任何存在的父进程（即PPID=1），且在UNIX系统进程层级中直接位于init之下。

系统通常在启动时开启很多**服务** ，一同引导守护进程。守护进程为对网络请求，硬件活动等进行响应，或其他通过某些任务对其他应用程序的请求进行回应提供支持。**也能够完成很多系统服务，能够对硬件进行配置（如在某些Linux系统上的devfsd），运行计划任务（例如cron），以及运行其他任务。**

## 一个文件被删除了，没有被释放是什么原因呢？
可能是 硬链接，inode 的引用没有释放完毕。

## 弱类型、强类型、动态类型、静态类型语言的区别是什么？
基础概念
1. Program Errors:`trapped errors`导致程序终止执行;`untrapped errors`出错后继续执行，但可能出现任意行为
2. Forbidden Behaviours 语言设计时，可以定义一组forbidden behaviors. 它必须包括所有untrapped errors, 但可能包含trapped errors.
3. Well behaved 如果程序执行不可能出现forbidden behaviors, 则为well behaved。
4. Ill behaved 否则为ill behaved...

- **强类型** ：如果一种语言的所有程序都是well behaved——即不可能出现forbidden behaviors，则该语言为strongly typed。偏向于不容忍隐式类型转换。譬如说haskell的int就不能变成double
- **弱类型** ：否则为weakly typed。比如C语言的缓冲区溢出，属于trapped errors，即属于forbidden behaviors..故C是弱类型。偏向于容忍隐式类型转换。譬如说C语言的int可以变成double
- **静态类型 statically** : 如果在编译时拒绝ill behaved程序，则是statically typed;编译的时候就知道每一个变量的类型，因为类型错误而不能做的事情是语法错误。
- **动态类型dynamiclly** : 如果在运行时拒绝ill behaviors, 则是dynamiclly typed。编译的时候不知道每一个变量的类型，因为类型错误而不能做的事情是运行时错误。譬如说你不能对一个数字a写a[10]当数组用。

**举例**
- 无类型： 汇编
- 弱类型、静态类型 ： **C/C++**
- 弱类型、动态类型检查： Perl/PHP
- 强类型、静态类型检查 ：Java/C#
- 强类型、动态类型检查 ：Python, Scheme
- 静态显式类型 ：Java/C
- 静态隐式类型 ：Ocaml, Haskell

## 位图法
位图法就是bitmap的缩写，所谓bitmap，就是用每一位来存放某种状态，适用于大规模数据，但数据状态又不是很多的情况。通常是用来判断某个数据存不存在的。**位图的基本概念是用一个位（bit）来标记某个数据的存放状态，由于采用了位为单位来存放数据，所以节省了大量的空间** 。举个具体的例子，在Java中一般一个int数字要占用32位，如果能用一位就表示这个数，就可以缩减大量的存储空间。一般把这种方法称为位图法，即Bitmap。

**海量数据排序（不重复）**

从最简单的情况说起，如果要对90个小于100的不重复的正整数排序。用位图的思想就是先申请一块100bit的空间，第一遍遍历所有的数，将出现的数字在位图中对应的位置置为1；第二遍遍历位图，依次输出值为1的位对应的数字。先且不说这种情况出现的频率不是很高，就仅这种情况，还是有很多其他的排序算法有它们自己的优势（不用额外占用空间之类）。但更进一步，如果我们把数字范围放大，对1000,000,000中的900,000,000个不重复的正整数排序，由于需要的内存非常大，其他算法在不分治的情况下就很难再处理这个问题。而用位图法只需要1000000000/(8*1024*104)=119.2MB空间，对现在的计算机来说没有任何问题。

**数据压缩**

假设有这样一份数据，记录了全国1990-1999年出生的人的姓名和出生年月的键值对。假设正好有一千万人，那就要存储一千万个姓名和年份。如何运用Bitmap的思想来压缩数据呢。下面提供几种思路。

从人的角度来看，由于一共就只有10个年份，可以用4个bit将它们区分开。如0000表示1990年，1001表示1999年。那一个人的出生年份就可以用4个bit位来表示，进而一千万个年份就可以压缩为一千万个4位的bit组；从另一个角度来看这个问题，我们有10个年份，每个人要么是要么不是在这个年份出生。每个人对于年份来说就可以抽象为一个bit位，所以我们可以把一千万的年龄压缩为10个一千万位的bit组。这样压缩的力度不如按人的角度压缩的大，但从年份出发的问题会有一定的优势，如有哪些人是1990年出生的，只需遍历1990年对应的那个bit组就可以了。

可以看出来不管从哪个角度，bitmap的压缩都是建立在数据中存在大量的冗余数据的基础上的，如年份。而在上面的问题中，年份的分布是散乱的，那假如我们事先把数据进行了排序，把相同的出生年份的人排在一起，那数据就可以进一步压缩。这样一来就只要记录每个年份的人数，就可以根据下标来判断每个人的出生年份。

**判断整形数组是否重复**

遍历数组，一个一个放入bitmap，并且检查其是否在bitmap中出现过，如果没出现放入，否则即为重复的元素。

**找出没2.5亿个整数中，不重复的整数**

采用2-Bitmap（每个数分配2bit，00表示不存在，01表示出现一次，10表示多次，11无意义）。其实，这里可以使用两个普 通的Bitmap，即第一个Bitmap存储的是整数是否出现，如果再次出现，则在第二个Bitmap中设置即可。这样的话，就可以使用简单的1- Bitmap了


**参考**
1. [大数据常用技巧之位图法](https://blog.csdn.net/u013291394/article/details/50211181)


## Top K 问题
**10亿个IP，取出频次出现最多的TOP10个IP**

问题一：怎么在海量数据中找出重复次数最多的一个

算法思想：
方案1：先做hash，然后求模映射为小文件，求出每个小文件中重复次数最多的一个，并记录重复次数。

然后找出上一步求出的数据中重复次数最多的一个就是所求（如下）。

问题二：网站日志中记录了用户的IP，找出访问次数最多的IP。

算法思想：
IP地址最多有2^32=4G种取值可能，所以不能完全加载到内存中。
可以考虑分而治之的策略；

**map** 按照IP地址的hash(IP)%1024值，将海量日志存储到1024个小文件中，每个小文件最多包含4M个IP地址。

**reduce** 对于每个小文件，可以构建一个IP作为key，出现次数作为value的hash_map，并记录当前出现次数最多的1个IP地址。
有了1024个小文件中的出现次数最多的IP，我们就可以轻松得到总体上出现次数最多的IP

**参考**
1. [从一亿个ip找出出现次数最多的IP](https://blog.csdn.net/qq_23100787/article/details/80392135)

**千万条搜索结果里找频率最高的**

搜索引擎会通过日志文件把用户每次检索使用的所有检索串都记录下来，每个查询串的长度为1-255字节。假设目前有一千万个记录（这些查询串的重复度比较高，虽然总数是1千万，但如果除去重复后，不超过3百万个。一个查询串的重复度越高，说明查询它的用户越多，也就是越热门。），请你统计最热门的10个查询串，要求使用的内存不能超过1G。

　　典型的Top K算法，还是在这篇文章里头有所阐述。 文中，给出的最终算法是：
1. 第一步、先对这批海量数据预处理，在O（N）的时间内用Hash表完成排序；
2. 然后，第二步、借助堆这个数据结构，找出Top K，时间复杂度为N‘logK。 即，借助堆结构，我们可以在log量级的时间内查找和调整/移动。因此，维护一个K(该题目中是10)大小的小根堆，
3. 然后遍历300万的Query，分别和根元素进行对比所以，我们最终的时间复杂度是：O（N） + N'*O（logK），（N为1000万，N’为300万）。ok，更多，详情，请参考原文。

　　或者：采用trie树，关键字域存该查询串出现的次数，没有出现为0。最后用10个元素的最小推来对出现频率进行排序

**有一个1G大小的一个文件，里面每一行是一个词，词的大小不超过16字节，内存限制大小是1M。返回频数最高的100个词。**

方案：顺序读文件中，对于每个词x，取hash(x)%5000，然后按照该值存到5000个小文件（记为x0,x1,...x4999）中。这样每个文件大概是200k左右。

　　如果其中的有的文件超过了1M大小，还可以按照类似的方法继续往下分，直到分解得到的小文件的大小都不超过1M。 对每个小文件，统计每个文件中出现的词以及相应的频率（可以采用trie树/hash_map等），并取出出现频率最大的100个词（可以用含100个结点的最小堆），并把100个词及相应的频率存入文件，这样又得到了5000个文件。下一步就是把这5000个文件进行归并（类似与归并排序）的过程了。

**给定a、b两个文件，各存放50亿个url，每个url各占64字节，内存限制是4G，让你找出a、b文件共同的url？**

**方案1** : 可以估计每个文件安的大小为5G×64=320G，远远大于内存限制的4G。所以不可能将其完全加载到内存中处理。考虑采取分而治之的方法。

遍历文件a，对每个url求取hash(url)%1000，然后根据所取得的值将url分别存储到1000个小文件（记为a0,a1,...,a999）中。这样每个小文件的大约为300M。

遍历文件b，采取和a相同的方式将url分别存储到1000小文件（记为b0,b1,...,b999）。这样处理后，所有可能相同的url都在对应的小文件（a0vsb0,a1vsb1,...,a999vsb999）中，不对应的小文件不可能有相同的url。然后我们只要求出1000对小文件中相同的url即可。

求每对小文件中相同的url时，可以把其中一个小文件的url存储到hash_set中。然后遍历另一个小文件的每个url，看其是否在刚才构建的hash_set中，如果是，那么就是共同的url，存到文件里面就可以了。

**方案2** ：如果允许有一定的错误率，可以使用 ，4G内存大概可以表示340亿bit。将其中一个文件中的url使用Bloom filter映射为这340亿bit，然后挨个读取另外一个文件的url，检查是否与Bloom filter，如果是，那么该url应该是共同的url（注意会有一定的错误率）。

**100w个数中找出最大的100个数。**

**方案1** ：在前面的题中，我们已经提到了，用一个含100个元素的最小堆完成。复杂度为O(100w*lg100)。

**方案2** ：采用快速排序的思想，每次分割之后只考虑比轴大的一部分，知道比轴大的一部分在比100多的时候，采用传统排序算法排序，取前100个。复杂度为O(100w*100)。

**方案3** ：采用局部淘汰法。选取前100个元素，并排序，记为序列L。然后一次扫描剩余的元素x，与排好序的100个元素中最小的元素比，如果比这个最小的要大，那么把这个最小的元素删除，并把x利用插入排序的思想，插入到序列L中。依次循环，知道扫描了所有的元素。复杂度为O(100w*100)。

**方法总结**
1. 布隆过滤器；
2. 利用哈希函数对数据规模进行分割；
3. 位图法
4. 堆

**参考**
1. [十道海量数据处理面试题与十个方法总结](https://cloud.tencent.com/developer/article/1064552)

## 布隆过滤算法

## 线段树
它是一种数据结构，用来存储区间或线段，用来在 O(log n) 的时间内查找包含某个点的所有区间。

**线段树用数组的优缺点，用指针的优缺点**

## Ping 的过程
1. ping test.com 先向DNS查IP；
2. DNS返回IP；
3. 已知IP，在同一网段的话，使用ARP协议查找MAC物理地址，发送ARP请求；
4. 获得ARP答应；首先，交换机会收到这个报文后，交换机有学习MAC地址的功能，所以他会检索自己有没有保存主机B的MAC地址，如果有，就返回给主机A，如果没有，就会向所有端口发送ARP广播，其它主机收到后，发现不是在找自己，就纷纷丢弃了该报文，不去理会。直到主机B收到了报文后，就立即响应，我的MAC地址是多少，同时学到主机A的MAC地址，并按同样的ARP报文格式返回给主机A。
5. 再发送 ICMP 报文；
6. 接受报文；

**不在同一网段**
1. 如果主机A要ping主机C，那么主机A发现主机C的IP和自己不是同一网段，他就去找网关转发，但是他也不知道网关的MAC地址情况下呢？他就会向之前那个步骤一样**先发送一个ARP广播，找到网关的MAC地址** ，再发封装ICMP报文给网关路由器。
2. 当路由器收到主机A发过来的ICMP报文，发现自己的目的地址是其本身MAC地址，**根据目的的IP2.1.1.1，查路由表，发现2.1.1.1/24的路由表项，得到一个出口指针，去掉原来的MAC头部，加上自己的MAC地址向主机C转发** 。
3. 最后，在主机C已找到路由器2端口MAC地址，路由器2端口转发给路由器1端口，路由1端口学到主机A的MAC地址的情况下，**他们就不需要再做ARP解析** ，就将ICMP的回显请求回复过来

## 缓存算法
1. 先进先出（FIFO）
2. 最近最久未使用（LRU）
3. 最近很少使用（LFU）：与LRU不同，LFU是基于访问次数的
4. 最佳的（OPT）：是一种理论上最佳的页面置换算法。它的思想是，试图淘汰掉以后永远也用不到的页面，如果没有则淘汰最久以后再用到的页面。因为这种算法必须知道进程访问页面的序列，而这是无法实现的，因此仅有理论意义。

## 如果判断路况？
1. 现在很多人手机上都安装了导航软件，特别是高德地图。很多人已经养成了出门开车就先设置手机导航的习惯。我们在用导航软件，导航软件也在收集我们的行驶信息(包括GPS位置，行驶速度等)传给服务器，然后利用大数据技术分析路况信息。在某个区域内，同时传回的数据越多，导航的数据就越精确。假如说在某个地方堵车比较严重，这个区域内传回的数据显示汽车行驶速度过慢，数量过多，导航系统就会计算是否是堵车。
2. 交管部门合作，地感线圈、测速摄像头、电子摄像头传回来的数据实时反馈，然后它们再从交管部门获得这些信息，再更新到导航上。
3. 用户自己自愿提供的。现在导航上都有一个功能叫做上报功能，现在很多朋友都热爱分享，哪里堵车了，点击上报，然后系统就会根据实时数据分析，如果情况属实就会在导航上显示。
4. 目前路况的采集主要的模型就是浮动车模型，也就是**用GPS记录浮动车的速度和方向** ，然后根据道路匹配计算出路况。**目前主要的浮动车都是出租车公司提供** 。基于GPS的路况信息监测，这种方式主要就是依赖于出租车上的GPS。像广州的出租车上的GPS终端，每隔一定时间（10s~30s）就会向监测中心发送一次信息，这些信息包括车辆的位置信息、车速、行驶方向等等。当有足够多的出租车装上这种GPS终端后，就在整个城市中形成了一个动态、实时的路况信息监测网。    
5. 还有一种相对比较成本高的方式，就是定点上报，也就是在固定的地方有专门的上报人员或者设备来实时上报路况。

## 如何避免C++函数传参时的拷贝
1. 传入指针；
2. 传入引用；


## 避免C++函数返回值拷贝
1. 非局部对像可以使用return std::move(x)的方式去避免拷贝。

## 如何监控进程异常退出
1. 用程序轮询该进程的状态，设置监控频率，那一旦进程ID消失便知道进程死去；

## 如果进程没有退出，但是处于异常状态 比如死循环或者挂起

## 如何判断进程是由于死循环造成的100%cpu占用还是由于进行着一个及其耗资源的计算造成的100%cpu占用

## 如果让你设计一个云盘系统，你会怎么设计？

## HTTPS 非对称加密、对称加密
HTTPS其实是有两部分组成：HTTP + SSL / TLS，也就是在HTTP上又加了一层处理加密信息的模块。服务端和客户端的信息传输都会通过TLS进行加密，所以传输的数据都是加密后的数据。

**数字证书** :采用HTTPS协议的服务器必须要有一套数字证书，可以自己制作，也可以向组织申请。区别就是自己颁发的证书需要客户端验证通过，才可以继续访问

**传送证书** :这个证书其实就是公钥，只是包含了很多信息，如证书的颁发机构，过期时间等等。

**客户端解析证书(非对称加密)** :这部分工作是有客户端的TLS来完成的，首先会验证公钥是否有效，比如颁发机构，过期时间等等，如果发现异常，则会弹出一个警告框，提示证书存在问题。如果证书没有问题，那么就生成一个随机值。然后用证书对该随机值进行加密。就好像上面说的，把随机值用锁头锁起来，这样除非有钥匙，不然看不到被锁住的内容。

**传送加密信息** ：这部分传送的是用证书加密后的随机值，目的就是让服务端得到这个随机值，以后客户端和服务端的通信就可以通过这个随机值来进行加密解密了。

**服务端解密信息(转换为对称加密)** :服务端用私钥解密后，得到了客户端传过来的随机值(私钥)，然后把内容通过该值进行对称加密。所谓对称加密就是，将信息和私钥通过某种算法混合在一起，这样除非知道私钥，不然无法获取内容，而正好客户端和服务端都知道这个私钥，所以只要加密算法够彪悍，私钥够复杂，数据就够安全。

## 红黑树

**五个性质**
1. 节点是红色或黑色。
2. 根是黑色。
3. 所有叶子都是黑色（叶子是NIL节点）。
4. 每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
5. 从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点。

**红黑树和AVL树相比呢，优势在哪里？**

A：两者都是特殊的BST，相比AVL，红黑树不要求严格的1的高度差，对于插入操作，两个树类似，最多旋转两次，对于删除，红黑树最多旋转3次，而AVL树则是O（logN）

**那红黑树的高度差最多？**

A:最长路径和最短路径最多相差一倍。

## 迪克斯特拉算法



## 堆排序
堆是一个近似完全二叉树的结构，并同时满足堆积的性质：即子节点的键值或索引总是小于（或者大于）它的父节点。
堆指的是完全二叉树，分为最大堆最小堆。用数组表示时，很容易找到父子节点， 找到i节点的父节点 `parient(i) = i/2;`，左子节点 `left(i) = 2 * i;`， 右子节点 `right(i) = 2 * i + 1;`.
堆有一些基本过程：
- Max-Heapify 过程，时间复杂度 `O(logn)`，是维护最大堆性质的关键;
- Build-Max-Heap 过程，具有线性时间复杂度，功能是从无序的输入数组中构造一个最大堆;
- Heapsort 过程，时间复杂度`O(nlogn)`，功能是对一个数组进行原址排序;
- Max-Heap-Insert, Heap-Extract-Max, Heap-Increase-Key, Heap-Maximum 过程，时间复杂度`O(logn)`，利用堆数据结构实现一个优先队列;

```
PARIENT(i)
    return i/2

LEFT(i)
    return 2 * i

RIGHT(i)
    return 2 * i + 1

MAX-HEAPIFY(A, i)
    l = LEFT(i)
    r = RIGHT(i)
    largest = i
    if l <= A.heap-size and A[l] > a[i]:
        largest = l
    if r <= A.heap-size and A[r] > A[largest]:
        largest = r
    if largest != i
        exchage A[i] with A[largest]
        MAX-HEAPIFY(A, largest)

BUILD-MAX-HEAP(A)
    A.heap-size = A.length
    for i = [A.length/2] downto 1
        MAX-HEAPIFY(A, i)

HEAPSORT(A)
    BUILD-MAX-HEAP(A)
    for i = A.length downto 2
        exchange A[1] with A[i]
        A.heap-size = A.heap-size - 1
        MAX-HEAPIFY(A,i)
```

## 虚函数实现机制
1. 虚表
2. 类的虚指针

## 快速排序

**原理**
快排是一种分治排序的方法，是原址排序，最差时间复杂度 O(n^2)，平均时间复杂度O(nlogn)。

```
QUICKSORT(A, p, r)
    if p < r
        q = PARTITION(A, p, r)
        QUICKSORT(A, p, q-1)
        QUICKSORT(A, q+1, r)

PARTITION(A, p, r)
    x = A[r]
    i = p - 1
    for j= p to r-1
        if A[j] <= x
            i++
            exchange A[i] with A[j]
    exchange A[i+1] with A[r]
    return i+1
```

**如何优化快速排序**

1. 每次选择划分元素的时候，随机选择一个数
2. 更苛刻，每次随机选择三个数，然后用中值作为分隔元素

## 虚拟内存机制

**虚拟内存机制，二级页表，TLB快表，缺页，swap**

## volatile 作用
针对多线程程序，因为有寄存器和内存的存在，有可能当前类的值在寄存器中有缓存；万一内存中的值被其他线程修改了，却依旧在使用寄存器中的旧值会造成一些不一致问题。这个关键字要求每次用到该变量时都从内存中读。

## 什么是 traits， 作用

## 迭代器失效的问题
1. 删除元素；

## 有三个消息队列，随机的向三个队列插入元素(概率可能不同)，如何保证插入和查找的高效

(有两种思路，一种是加一个控制器，队列通知占用率，由控制器控制插入和查找，另一种是计算阻塞次数，再根据阻塞次数按比例控制该队列的插入频率和查找频率)

## 最长公共子序列

## TCP拥塞控制，滑动窗口协议，糊涂窗口

## TCP如何保证可靠性
1. 校验和
2. 序列号
3. 确认应答
4. 超时重传
5. 连接管理
6. 流量控制
7. 拥堵控制

## 编译器怎么确定虚函数地址在虚表里面的位置
## 虚表里面存了哪些东西
## 虚表指针存在对象的哪个位置
首位置，多继承有多个虚表

## C++11 新特性
### 右值引用
### 移动语义和移动构造函数
### std::move()
### 对 const T& 可以做std::move() 嘛

## 操作系统如何陷入内核态
## 网络的惊群问题

惊群效应（thundering herd）是指多进程（多线程）在同时阻塞等待同一个事件的时候（休眠状态），如果等待的这个事件发生，那么他就会唤醒等待的所有进程（或者线程），但是最终却只能有一个进程（线程）获得这个时间的“控制权”，对该事件进行处理，而其他进程（线程）获取“控制权”失败，只能重新进入休眠状态，这种现象和性能浪费就叫做惊群效应。

**带来的问题**

- **Linux 内核对用户进程（线程）频繁地做无效的调度、上下文切换等使系统性能大打折扣。** 上下文切换（context switch）过高会导致 CPU 像个搬运工，频繁地在寄存器和运行队列之间奔波，更多的时间花在了进程（线程）切换，而不是在真正工作的进程（线程）上面。直接的消耗包括 CPU 寄存器要保存和加载（例如程序计数器）、系统调度器的代码需要执行。间接的消耗在于多核 cache 之间的共享数据。
- **为了确保只有一个进程（线程）得到资源，需要对资源操作进行加锁保护，加大了系统的开销。** 目前一些常见的服务器软件有的是通过锁机制解决的，比如 Nginx（它的锁机制是默认开启的，可以关闭）；还有些认为惊群对系统性能影响不大，没有去处理，比如 Lighttpd。


**参考**
1. [什么是惊群，如何有效避免惊群?](https://www.zhihu.com/question/22756773/answer/545048210)


## TCP的粘包问题有哪些解决方案

TCP是个“流”协议，所谓流，就是没有界限的一串数据。大家可以想想河里的流水，是连成一片的，其间并没有分界线。TCP底层并不了解上层业务数据的具体含义，它会根据TCP缓冲区的实际情况进行包的划分，所以在业务上认为，一个完整的包可能会被TCP拆分成多个包进行发送，也有可能把多个小的包封装成一个大的数据包发送，这就是所谓的TCP粘包和拆包问题。

**发生原因**
1. 应用程序write写入的字节大小大于套接口发送缓冲区大小；
2. 进行MSS大小的TCP分段
3. 以太网帧的payload大于MTU进行IP分片

**解决方案**

由于底层的TCP无法理解上层的业务数据，所以在底层是无法保证数据包不被拆分和重组的，这个问题只能通过上层的应用协议栈设计来解决，根据业界的主流协议的解决方案，可以归纳如下。
1. 消息定长，例如每个报文的大小为固定长度200字节，如果不够，空位补空格；
2. 在包尾增加回车换行符进行分割，例如FTP协议；
3. 将消息分为消息头和消息体，消息头中包含表示消息总长度（或者消息体长度）的字段，通常设计思路为消息头的第一个字段使用int32来表示消息的总长度；
4. 更复杂的应用层协议。

## malloc和new的区别
**C++中有了malloc / free , 为什么还需要 new / delete**

1.	malloc与free是C++/C语言的标准库函数，new/delete是C++的运算符。它们都可用于申请动态内存和释放内存。
2.	对于非内部数据类型的对象而言，光用malloc/free无法满足动态对象的要求。对象在创建的同时要自动执行构造函数，对象在消亡之前要自动执行析构函数。因此C++语言需要一个能完成动态内存分配和初始化工作的运算符new，以一个能完成清理与释放内存工作的运算符delete。
3.	new能够自动计算需要分配的内存空间，而malloc需要手工计算字节数：
```
int * p1=new int[2];
int * p2=(int*)malloc(sizeof(int) *2);
```
4.	new的返回值不需要强制类型转换，因为new内置了sizeof()、类型转换和类型安全检查；而malloc返回void类型的指针，它本身并不识别内存是什么类型，它只关心内存的总字节数，因此需要强制类型转换。
5.	new 是安全的，会进行类型检查 
```
//int * p1= new float[2];编译时报错
```
6.	new一般由两部分组成，分别是new操作和构造
7.	malloc/free需要库函数<stdlib.h>支持
8.	内存释放：如果申请内存后不进行内存释放，就会出现内存泄露问题，所以new/delete、malloc/free必须配对使用。而且delete和free被调用后，内存不会立即收回，指针也不会指向空，而是仅仅告诉操作系统，这一块内存被释放了，可以用作其他用途。由于没有对这块内存进行写操作，所以内存中的变量数值并没有发生改变，出现野指针的情况，因此delete和free后，需要将指针指向置空。