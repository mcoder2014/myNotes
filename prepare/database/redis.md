# redis

## 使用

常见的用法

### 键相关

command | explain
| - | - |
TYPE KEY_NAME | 查询一个键的类型
DEL KEY_NAME | 删除一个键
Expire KEY_NAME TIME_IN_SECONDS | 给一个键设置过期时间
PEXPIREAT KEY_NAME TIME_IN_MILLISECONDS_IN_UNIX_TIMESTAMP | 设置毫秒计时的过期时间
PERSIST KEY_NAME | 取消过期时间限制
TTL KEY_NAME | 返回键的剩余过期时间
RENAME OLD_KEY_NAME NEW_KEY_NAME | 修改一个键的键名
RENAMENX OLD_KEY_NAME NEW_KEY_NAME | 在新的键不存在的情况下修改键的名字
EXISTS KEY_NAME | 查询是否存在这个键
KEYS PATTERN | 查询符合 Pattern 的键

### 字符串

command | explain
| - | - |
SET KEY_NAME VALUE | 设置一个字符串
GET KEY_NAME | 获得对应的值
SETNX KEY_NAME VALUE | 只有当键不存在的时候设置一个值
STRLEN KEY_NAME | 获得值的长度
SETEX KEY_NAME TIMEOUT VALUE | 设置一个带有过期时间的键

### 列表

command | explain
| - | - |
LINDEX KEY_NAME INDEX_POSITION | 通过索引获得列表中的某个元素
LSET KEY_NAME INDEX VALUE | 通过索引设置元素值
LPUSH KEY_NAME VALUE1.. VALUEN | 在链表头部插入元素
RPUSH KEY_NAME VALUE1..VALUEN | 从列表尾部添加元素
LRANGE KEY_NAME START END | 返回指定区间内的元素
LREM KEY_NAME COUNT VALUE | 移除列表元素（与值相等的元素）
LLEN KEY_NAME  | 返回列表长度
LTRIM KEY_NAME START STOP | 修改，保留范围内元素，其他的元素都删掉
LLEN KEY_NAME | 移除并获取列表的第一个元素
LPUSHX KEY_NAME VALUE1.. VALUEN | 将一个或多个值插入到已存在的列表头部
LINSERT KEY_NAME BEFORE EXISTING_VALUE NEW_VALUE | Redis Linsert 命令用于在列表的元素前或者后插入元素。 当指定元素不存在于列表中时，不执行任何操作。 当列表不存在时，被视为空列表，不执行任何操作。 如果 key 不是列表类型，返回一个错误。
RPOP KEY_NAME | 移除最右元素返回

### 哈希

command | explain
|-|-|
HSET KEY_NAME FIELD VALUE | 为哈希表中的字段设置 value
HSETNX KEY_NAME FIELD VALUE | 字段不存在时设置哈希值
HMSET KEY_NAME FIELD1 VALUE1 ...FIELDN VALUEN  | 设置多个元素
HMGET KEY_NAME FIELD1...FIELDN | 获得多个元素值
HGETALL KEY_NAME | 获得所有字段和值
HVALS KEY_NAME FIELD VALUE | Redis Hvals 命令返回哈希表所有字段的值。
HKEYS KEY_NAME FIELD_NAME INCR_BY_NUMBER | 获得哈希表中的所有字段名
HEXISTS KEY_NAME FIELD_NAME | 判断是否存在元素
HLEN KEY_NAME | 获得哈希表大小
HDEL KEY_NAME FIELD1.. FIELDN | 移除哈希表元素

### 集合

command | explain
|-|-|
SADD key member1 [member2] | 向集合添加一个或多个成员
SCARD key | 获取集合的成员数
SDIFF key1 [key2] | 返回给定所有集合的差集
SDIFFSTORE destination key1 [key2] | 返回给定所有集合的差集并存储在 destination 中
SINTER key1 [key2] | 返回给定所有集合的交集
SINTERSTORE destination key1 [key2] | 返回给定所有集合的交集并存储在 destination 中
SISMEMBER key member | 判断 member 元素是否是集合 key 的成员
SMEMBERS key | 返回集合中的所有成员
SMOVE source destination member | 将 member 元素从 source 集合移动到 destination 集合
SPOP key | 移除并返回集合中的一个随机元素
SRANDMEMBER key [count] | 返回集合中一个或多个随机数
SREM key member1 [member2] | 移除集合中一个或多个成员
SUNION key1 [key2] | 返回所有给定集合的并集
SUNIONSTORE destination key1 [key2] | 所有给定集合的并集存储在 destination 集合中
SSCAN key cursor [MATCH pattern] [COUNT count] | 迭代集合中的元素

### 有序集合

command | explain
|-|-|
ZADD key score1 member1 [score2 member2] | 向有序集合添加一个或多个成员，或者更新已存在成员的分数
ZCARD key | 获取有序集合的成员数
ZCOUNT key min max | 计算在有序集合中指定区间分数的成员数
ZINCRBY key increment member | 有序集合中对指定成员的分数加上增量 increment
ZINTERSTORE destination numkeys key [key ...] | 计算给定的一个或多个有序集的交集并将结果集存储在新的有序集合 key 中
ZLEXCOUNT key min max | 在有序集合中计算指定字典区间内成员数量
ZRANGE key start stop [WITHSCORES] | 通过索引区间返回有序集合成指定区间内的成员
ZRANGEBYLEX key min max [LIMIT offset count] | 通过字典区间返回有序集合的成员
ZRANGEBYSCORE key min max [WITHSCORES] [LIMIT] | 通过分数返回有序集合指定区间内的成员
ZRANK key member | 返回有序集合中指定成员的索引
ZREM key member [member ...] | 移除有序集合中的一个或多个成员
ZREMRANGEBYLEX key min max | 移除有序集合中给定的字典区间的所有成员
ZREMRANGEBYRANK key start stop | 移除有序集合中给定的排名区间的所有成员
ZREMRANGEBYSCORE key min max | 移除有序集合中给定的分数区间的所有成员
ZREVRANGE key start stop [WITHSCORES] | 返回有序集中指定区间内的成员，通过索引，分数从高到底
ZREVRANGEBYSCORE key max min [WITHSCORES] | 返回有序集中指定分数区间内的成员，分数从高到低排序
ZREVRANK key member | 返回有序集合中指定成员的排名，有序集成员按分数值递减(从大到小)排序
ZSCORE key member | 返回有序集中，成员的分数值
ZUNIONSTORE destination numkeys key [key ...] | 计算给定的一个或多个有序集的并集，并存储在新的 key 中
ZSCAN key cursor [MATCH pattern] [COUNT count] | 迭代有序集合中的元素（包括元素成员和元素分值）

## 分区

分区是分割数据到多个Redis实例的处理过程，因此每个实例只保存key的一个子集。

### 分区的优势

通过利用多台计算机内存的和值，允许我们构造更大的数据库。
通过多核和多台计算机，允许我们扩展计算能力；通过多台计算机和网络适配器，允许我们扩展网络带宽。

### 分区的不足

redis的一些特性在分区方面表现的不是很好：

* 涉及多个key的操作通常是不被支持的。举例来说，当两个set映射到不同的redis实例上时，你就不能对这两个set执行交集操作。
* 涉及多个key的redis事务不能使用。
* 当使用分区时，数据处理较为复杂，比如你需要处理多个rdb/aof文件，并且从多个实例和主机备份持久化文件。
* 增加或删除容量也比较复杂。redis集群大多数支持在运行时增加、删除节点的透明数据平衡的能力，但是类似于客户端分区、代理等其他系统则不支持这项特性。然而，一种叫做presharding的技术对此是有帮助的。

### 分区类型

Redis 有两种类型分区。 假设有4个Redis实例 R0，R1，R2，R3，和类似user:1，user:2这样的表示用户的多个key，对既定的key有多种不同方式来选择这个key存放在哪个实例中。也就是说，有不同的系统来映射某个key到某个Redis服务。

### 范围分区

最简单的分区方式是按范围分区，就是映射一定范围的对象到特定的Redis实例。

比如，ID从0到10000的用户会保存到实例R0，ID从10001到 20000的用户会保存到R1，以此类推。

这种方式是可行的，并且在实际中使用，不足就是要有一个区间范围到实例的映射表。这个表要被管理，同时还需要各 种对象的映射表，通常对Redis来说并非是好的方法。

### 哈希分区

另外一种分区方法是hash分区。这对任何key都适用，也无需是object_name:这种形式，像下面描述的一样简单：

用一个hash函数将key转换为一个数字，比如使用crc32 hash函数。对key foobar执行crc32(foobar)会输出类似93024922的整数。
对这个整数取模，将其转化为0-3之间的数字，就可以将这个整数映射到4个Redis实例中的一个了。93024922 % 4 = 2，就是说key foobar应该被存到R2实例中。注意：取模操作是取除的余数，通常在多种编程语言中用%操作符实现。

## Reference

1. [Redis 中文网](https://www.redis.net.cn/)
