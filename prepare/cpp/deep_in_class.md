# C++ 对象模型

## struct class union 对齐问题

### 结构体对齐规则

1. 对于结构体的各个成员，第一个成员的偏移量是0，**排列在后面的成员其当前偏移量必须是当前成员类型的整数倍**；
2. 结构体内所有数据成员各自内存对齐后，结构体本身还要进行一次内存对齐，保证**整个结构体占用内存大小是结构体内最大数据成员的最小整数倍**；
3. 如程序中有`#pragma pack(n)预编译指令`，则所有成员对齐以n字节为准(即偏移量是n的整数倍)，不再考虑当前类型以及最大结构体内类型。

### union 内存对齐

1. 找到占用字节最多的成员；
2. union的字节数必须是占用字节最多的成员的字节的倍数，而且需要能够容纳其他的成员.

### demo

#### Struct 对齐例子

```cpp
struct CAT_s
{
    int ld;
    char Color;
    unsigned short Age;
    char *Name;
    void(*Jump)(void);
}Garfield;
```

按照上面的3大规则直接来进行分析：

1. 使用32位编译，int占4， char 占1， unsigned short 占2，char* 占4，函数指针占4个，由于是32位编译是4字节对齐，所以该结构体占16个字节。（说明：按几字节对齐，是根据结构体的最长类型决定的，这里是int是最长的字节，所以按4字节对齐）；
2. 使用64位编译 ，int占4， char 占1， unsigned short 占2，char* 占8，函数指针占8个，由于是64位编译是8字节对齐，（说明：按几字节对齐，是根据结构体的最长类型决定的，这里是函数指针是最长的字节，所以按8字节对齐）所以该结构体占24个字节。

#### union对齐例子

``` cpp
//x64
typedef union 
    long i;
    int k[5];
    char c;
}D
```

要计算union的大小,首先要找到占用字节最多的成员,本例中是long,占用8个字节,int k[5]中都是int类型,仍然是占用4个字节的，然后union的字节数必须是占用字节最多的成员的字节的倍数,而且需要能够容纳其他的成员,为了要容纳k(20个字节),就必须要保证是8的倍数的同时还要大于20个字节,所以是24个字节。

## 内存对齐的作用

1. 平台移植问题：因为有的硬件做不到访问任意地址的数据，必须对齐才可以访问；
2. 性能问题：数据结构应该尽可能在自然边界上对齐，对于为对齐的内存数据，处理器访问更慢些。