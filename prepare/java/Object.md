# Object

## 方法

### 构造函数

### registerNatives()

为了使JVM发现本机功能，他们被一定的方式命名。例如，对于java.lang.Object.registerNatives，对应的C函数命名为Java_java_lang_Object_registerNatives。

通过使用registerNatives（或者更确切地说，JNI函数RegisterNatives），可以命名任何你想要你的C函数。(非重点)

### clone()

clone()函数的用途是用来另存一个当前存在的对象。只有实现了Cloneable接口才可以调用该方法，否则抛出CloneNotSupportedException异常。（注意：回答这里时可能会引出设计模式的提问）

### getClass()

final方法，用于获得运行时的类型。该方法返回的是此Object对象的类对象/运行时类对象Class。效果与Object.class相同。（注意：回答这里时可能会引出类加载，反射等知识点的提问）

### equals()

equals用来比较两个对象的内容是否相等。默认情况下(继承自Object类)，equals和==是一样的，除非被覆写(override)了。（注意：这里可能引出更常问的“equals与==的区别”及hashmap实现原理的提问）

### hashCode()

该方法用来返回其所在对象的物理地址（哈希码值），常会和equals方法同时重写，确保相等的两个对象拥有相等的hashCode。（同样，可能引出hashmap实现原理的提问）

### toString()

toString()方法返回该对象的字符串表示，这个方法没什么可说的。

### wait()

导致当前的线程等待，直到其他线程调用此对象的 notify() 方法或 notifyAll() 方法。（引出线程通信及“wait和sleep的区别”的提问）

### wait(long timeout)

导致当前的线程等待，直到其他线程调用此对象的 notify() 方法或 notifyAll() 方法，或者超过指定的时间量。（引出线程通信及“wait和sleep的区别”的提问）

### wait(long timeout, int nanos)

导致当前的线程等待，直到其他线程调用此对象的 notify() 方法或 notifyAll() 方法，或者其他某个线程中断当前线程，或者已超过某个实际时间量。（引出线程通信及“wait和sleep的区别”的提问）

### notify()

唤醒在此对象监视器上等待的单个线程。（引出线程通信的提问）

### notifyAll()

唤醒在此对象监视器上等待的所有线程。（引出线程通信的提问）

### finalize()

当垃圾回收器确定不存在对该对象的更多引用时，由对象的垃圾回收器调用此方法。（非重点，但小心引出垃圾回收的提问）

## Reference

1. [【08期】说说Object类下面有几种方法呢？](https://zhuanlan.zhihu.com/p/90464621)
