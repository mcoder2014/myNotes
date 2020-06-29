# ConcurrentHashMap 实现的原理

HashMap线程不安全，而Hashtable是线程安全，但是它使用了synchronized进行方法同步，插入、读取数据都使用了synchronized，当插入数据的时候不能进行读取（相当于把整个Hashtable都锁住了，全表锁），当多线程并发的情况下，都要竞争同一把锁，导致效率极其低下。而在JDK1.5后为了改进Hashtable的痛点，ConcurrentHashMap应运而生。

## ConcurrentHashMap 的设计思想

ConcurrentHashMap 采用了**分段锁**策略，主干是个 Segment 数组。Segment继承了ReentrantLock，所以它就是一种可重入锁（ReentrantLock)。在ConcurrentHashMap，一个Segment就是一个子哈希表，Segment里维护了一个HashEntry数组，并发环境下，对于不同Segment的数据进行操作是不用考虑锁竞争的。（就按默认的ConcurrentLeve为16来讲，理论上就允许16个线程并发执行）

```java
final Segment<K,V>[] segments;
```

HashEntry是目前提到最小的逻辑处理单元了。一个ConcurrentHashMap维护一个Segment数组，一个Segment维护一个HashEntry数组。**ConcurrentHashMap 对同一个 Segment 的操作需要考虑线程同步，对于不同的 Segment 不需要考虑线程同步问题。**

## 参考

1. [ConcurrentHashMap 原理解析（JDK1.8）](https://www.jianshu.com/p/d10256f0ebea)
