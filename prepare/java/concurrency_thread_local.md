# ThreadLocal

实现的关键在于 ThreadLoacl 中 有一个内部类 ThreadLocalMap。

每个线程 Thread 中存在一个成员变量 ThreadLocalMap，ThreadLocalMap 中的 key 对应 ThreadLocal ，Map 可以存储多个 key 即(ThreadLocal)。另外 Value 就对应着在 ThreadLocal 中存储的 Value 。

因此总结出：每个 Thread 中都具备一个 ThreadLocalMap ，而 ThreadLocalMap 可以存储以 ThreadLocal 为 key 的键值对。这里解释了为什么每个线程访问同一个 ThreadLocal ，得到的确是不同的数值。

## 使用效果

两个线程对同一个 ThreadLocal 变量操作互不影响，设计理念是共享变私有，把共享的变量变成线程私有的变量。
