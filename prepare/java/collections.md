# java 中的集合

## List interface

### ArrayList, CopyOnWriteArrayList, LinkedList, Stack, Vector

### ArrayList 内部实现

ArrayList 内部实现是一个可以调整大小的数组，特点如下：

1. 有序
2. 基于 index
3. 动态调整大小
4. 非线程安全
5. 允许存在重复元素

```Java
public class ArrayList<E> extends AbstractList<E>
        implements List<E>, RandomAccess,
                   Cloneable, java.io.Serializable
{
    transient Object[] elementData;     //backing array
    private int size;                   //array or list size

    //more code
}
```

### CopyOnWriteArrayList 写时复制队列

- 实现 List RandomAccess 接口
- update 操作比较费时，因为可能会复制
- 线程安全
- 允许重复元素
- 性能比 ArrayList 弱些

## Set interface

### ConcurrentSkipListSet, CopyOnWriteArraySet, EnumSet, HashSet, LinkedHashSet and TreeSet

### HashSet

1. 不允许重复元素;
2. 允许存在一个 null 元素;
3. 无序集合;
4. O(1)时间复杂度的基本操作: add, remove, contains, size;
5. 不是线程安全的;
6. Searlizable cloneable;

### LinkedHashSet

1. 有序集合;
2. O(1) 时间复杂度的基本操作;
3. 不是线程安全的;

### TreeSet

1. 实现了 NavigableSet 接口;
2. 不允许 null 元素;
3. O(1) 时间复杂度的基本操作;
4. 不允许插入无法比较大小的类型，因为他是有序的;
5. 不是线程安全的;

## Map interface

### ConcurrentHashMap, ConcurrentSkipListMap, EnumMap, HashMap, Hashtable, IdentityHashMap, LinkedHashMap, Properties, TreeMap, WeakHashMap

### HashMap

[HashMap 夺命二十一问](https://mp.weixin.qq.com/s?__biz=MzI5NTYwNDQxNA==&mid=2247488074&idx=2&sn=195d131805ab67eafad67825aa49eeba&chksm=ec504b9bdb27c28d3a735df5adc6eb6260c30a5070c701a6db951ee6fa6233c2ed400aa1025e&scene=126&sessionid=1598416735&key=de6c5d3f2e6b365e6c875b3555179e4fda472e5c19747ef07b82adade46a36bee57ad2bb07e4f6acb7e6998035a63c9b7fea37a470e20bfa58de8a7ee6ac71eeed4943babc87df986f53164bd3d61342e3351659a96397c6fd91b93b707f734fac6630d0b8fdf6c1948e7626a1a500a72cd06c0f261c9113ea66d823a64a0ba5&ascene=1&uin=MjM1Mzc3NDI2Mw%3D%3D&devicetype=Windows+10+x64&version=62090529&lang=zh_CN&exportkey=AW262tx8ry2ZE8z%2BP66Rf1Y%3D&pass_ticket=6ms91QUYt9GyrVfOM6g3flhy7rmdrHh8Ez8%2ByTpwt94UCX79vJHVWp3O1mUkAK42)

HashMap 基于哈希函数，每个 object 都有哈希 code，两个相等的 objects 一定能产生相同的 hash code，特点：

1. 不能包含重复的 key
2. 允许包含多个 null value，但仅允许一个 null key
3. 无序容器
4. 非线程安全
5. 存储的是引用，不能存 int，可以存 Integer
6. 实现了 Cloneable Serializable 接口

HashMap 在内部声明了 Entry，所有的 Entry 存储在`transient Entry[] table`表中。

```Java
static class Entry<K ,V> implements Map.Entry<K, V>
{
    final K key;
    V value;
    Entry<K ,V> next;
    final int hash;

    ...//More code goes here
}
```

### Hashtable

Hashtable 使用哈希桶来保存 k v 对，使用 key 的 hash code ，决定将 pair 放在哪个桶里。冲突时，使用一个拉链法。

1. 与 HashMap 相似，但 Hashtable 线程安全；
2. 不能放 null key 或者 value；
3. 不接受重复的 key；
4. It stores key-value pairs in hash table data structure which internally maintains an array of list. Each list may be referred as a bucket. In case of collisions, pairs are stored in this list.
5. 枚举变量在 Hashtable 中不够快。

### LinkedHashMap

1. LinkedHashMap 存储元素是有序的；
2. 不接受重复的 key；
3. 接收1个 null key，可以接受多个 null value；
4. 通过添加元素到内部的双向链表维护 KV 对的顺序。

可以用来实现 LRU 算法，因为有个函数叫做 `boolean removeEldestEntry(Map.Entry eldest)`，可以移除最早元素。

### TreeMap

TreeMap 基于**红黑树**实现，存储 kv 对的顺序。

1. kv；
2. 不接受重复元素;
3. 不接受 null 的 key，但可以有 null 的value;
4. 按照自然排序存储 keys;
5. containsKey, get, put and remove 操作的时间复杂度为 `O(log(n))`;
6. 非线程安全;
7. 采用红黑树实现，在内存管理上比较好。

## Stack interface

## Queue interface

### ArrayBlockingQueue, ArrayDeque, ConcurrentLinkedDeque, ConcurrentLinkedQueue, DelayQueue, LinkedBlockingDeque, LinkedBlockingQueue, LinkedList, LinkedTransferQueue, PriorityBlockingQueue, PriorityQueue and SynchronousQueue

### PriorityQueue 优先队列

- 优先队列是一个动态增长的队列；
- 不允许 null 元素；
- 优先队列中的元素必须实现 comparable 接口；
- 默认按照自然顺序排序；
- 可以使用 Comparator 调整优先队列的排序；
- 队首是最小的元素， poll 函数返回队首元素；
- 如果多个元素有同样的优先级，随机返回一个元素；
- 不是线程安全的；
- O(log(n)) 时间复杂度的基本操作 add poll

### PriorityBlockingQueue 优先阻塞队列

优先阻塞队列是一个并发的阻塞队列数据结构，基于优先级实现。

- 动态增长；
- 支持阻塞操作；
- 不允许 null 元素；
- 元素必须实现 comparable 接口；
- 默认按照自然顺序排序；
- 队首是最小元素；
- 线程安全；

### ArrayBlockingQueue

- 有边界的数组；
- 先进先出的队列；
- 队尾插入，队首出队；
- 一旦创建完成后，大小不能修改；
- 阻塞操作；
- 不允许 null 元素；
- 线程安全；

### LinkedTransferQueue

- 无边界，动态增长
- 先进先出
- 队尾插入、队首出
- 不支持 null 元素
- 线程安全
- size() 不是常数操作

## Deque interface

### ArrayDeque, ConcurrentLinkedDeque, LinkedBlockingDeque and LinkedList

## 辅助工具

### Comparable interface

Comparable 接口用来基于自然序排序 array 或者 list，需要元素 实现 Comparable 接口，实现 compareTo 方法。

```Java
public interface Comparable<T>
{
    public int compareTo(T o);
}
```

排序函数：

- `Collections.sort()`
- `Arrays.sort()`
- `Collections.reverseOrder()`

#### comparable 例子

```Java
import java.time.LocalDate;

public class Employee implements Comparable<Employee> {

    private Long id;
    private String name;
    private LocalDate dob;

    @Override
    public int compareTo(Employee o)
    {
        return this.getId().compareTo( o.getId() );
    }
}
```

### Comparator

Java Comparator 接口排序可能不按照自然排序。

1. 排序 array list，但是不用自然顺序；
2. 排序没有实现 comparable 接口的对象；
3. 排序同一个 array list 的元素的不同的域；

排序方法:

- Collections.sort(list, Comparator)
- Arrays.sort(array, Comparator)

group by 排序：

```java
//Order by name and then by age
Comparator.comparing(Employee::getName)
            .thenComparing(Employee::getDob);

//Order by name -> date of birth -> id
Comparator.comparing(Employee::getName)
            .thenComparing(Employee::getDob)
            .thenComparing(Employee::getId);
```

### Collection Sorting

#### Array 排序

```java
// 升序排序

import java.util.Arrays;

public class JavaSortExample
{
    public static void main(String[] args)
    {
        //Unsorted array
        Integer[] numbers = new Integer[] { 15, 11, 9, 55, 47, 18, 520, 1123, 366, 420 };
        //Sort the array
        Arrays.sort(numbers);
        //Print array to confirm
        System.out.println(Arrays.toString(numbers));

        // 降序排序

        //Unsorted array
        Integer[] numbers = new Integer[] { 15, 11, 9, 55, 47, 18, 520, 1123, 366, 420 };

        //Sort the array in reverse order
        Arrays.sort(numbers, Collections.reverseOrder());

        //Print array to confirm
        System.out.println(Arrays.toString(numbers));

        // 范围内排序
        //Unsorted array
        Integer[] numbers = new Integer[] { 15, 11, 9, 55, 47, 18, 1123, 520, 366, 420 };

        //Sort the array
        Arrays.sort(numbers, 2, 6);

        //Print array to confirm
        System.out.println(Arrays.toString(numbers));

        // JAVA 8 并行排序
        Arrays.parallelSort(numbers);

        Arrays.parallelSort(numbers, 2, 6);

        Arrays.parallelSort(numbers, Collections.reverseOrder());
    }
}
```

#### 队列排序

```java

// 自然顺序排序
//Unsorted list
Integer[] numbers = new Integer[] { 15, 11, 9, 55, 47, 18, 1123, 520, 366, 420 };
List<Integer> numbersList = Arrays.asList(numbers);

//Sort the list
Collections.sort(numbersList);

//Print list to confirm
System.out.println(numbersList);

// 降序排序
//Unsorted list
Integer[] numbers = new Integer[] { 15, 11, 9, 55, 47, 18, 1123, 520, 366, 420 };
List<Integer> numbersList = Arrays.asList(numbers);

//Sort the list
Collections.sort(numbersList, Collections.reverseOrder());

//Print list to confirm
System.out.println(numbersList);
```

#### Set 排序

转换成 list 之后再排序

```java
//Unsorted list
HashSet<Integer> numbersSet = new LinkedHashSet<>(
        Arrays.asList(15, 11, 9, 55, 47, 18, 1123, 520, 366, 420) );

List<Integer> numbersList = new ArrayList<Integer>(numbersSet) ;        //set -> list

//Sort the list
Collections.sort(numbersList);

numbersSet = new LinkedHashSet<>(numbersList);          //list -> set

//Print set to confirm
System.out.println(numbersSet);
```

## java Collection 面试问题

## Reference

1. [java-collections](https://howtodoinjava.com/java-collections/)
2. [Top 40 Java collection interview questions and answers](https://howtodoinjava.com/interview-questions/useful-java-collection-interview-questions/)
3. [【30期】说一下HashMap的实现原理？](https://zhuanlan.zhihu.com/p/107280444)
4. [【29期】Java集合框架 10 连问，你有被问过吗？](https://zhuanlan.zhihu.com/p/95219932)
