# 事务 Transaction

## 事务特性

ACID:

1. 原子性
2. 一致性
3. 隔离性
4. 持久性

### 事务四个级别

1. RU 未提交读 (脏读、不可重复读、幻读)
2. RC 提交读   (不可重复读、幻读)
3. RR 可重复读 (幻读)
4. S 序列化   (x)

mysql 默认的事务级别 可重复度

### 事务命令

```SQL
START TRANSACTION or BEGIN TRANSACTION   # 开始事务
COMMIT  # 提交
ROLLBACK    # 回滚
SAVEPOINT   # 保存点，可以 ROLLBACK 的还原点
SET TRANSACTION # 命名事务
```

### 事务 SQL 例子

```SQL
# 提交一个事务
BEGIN;
UPDATE accounts SET balance = balance - 100 WHERE id = 1;
UPDATE accounts SET balance = balance + 100 WHERE id = 2;
COMMIT;

# 回滚一个事务
BEGIN;
UPDATE accounts SET balance = balance - 100 WHERE id = 1;
UPDATE accounts SET balance = balance + 100 WHERE id = 2;
ROLLBACK;

# 设置事务级别
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
```

### 事务日志

事务日志可以帮助提高事务的效率。使用事务日志，存储引擎在修改表的数据时只需要修改其内存拷贝，再把该修改行为记录到持久在硬盘上的事务日志中，而不用每次都将修改的数据本身持久到磁盘。事务日志采用的是追加的方式，因此写日志的操作是磁盘上一小块区域内的顺序I/O，而不像随机I/O需要在磁盘的多个地方移动磁头，所以采用事务日志的方式相对来说要快得多。事务日志持久以后，内存中被修改的数据在后台可以慢慢地刷回到磁盘。目前大多数存储引擎都是这样实现的，我们通常称之为预写式日志（Write-Ahead Logging），修改数据需要写两次磁盘。
如果数据的修改已经记录到事务日志并持久化，但数据本身还没有写回磁盘，此时系统崩溃，存储引擎在重启时能够自动恢复这部分修改的数据。

MySQL Innodb中跟数据持久性、一致性有关的日志，有以下几种：

- **Bin Log**:是mysql服务层产生的日志，常用来进行数据恢复、数据库复制，常见的mysql主从架构，就是采用slave同步master的binlog实现的
- **Redo Log**:记录了数据操作在物理层面的修改，mysql中使用了大量缓存，修改操作时会直接修改内存，而不是立刻修改磁盘，事务进行中时会不断的产生redo log，在事务提交时进行一次flush操作，保存到磁盘中。当数据库或主机失效重启时，会根据redo log进行数据的恢复，如果redo log中有事务提交，则进行事务提交修改数据。
- **Undo Log**: 除了记录redo log外，当进行数据修改时还会记录undo log，undo log用于数据的撤回操作，它记录了修改的反向操作，比如，插入对应删除，修改对应修改为原来的数据，通过undo log可以实现事务回滚，并且可以根据undo log回溯到某个特定的版本的数据，实现MVCC。

## MVCC

Multi Version Concurrency Control 多版本并发控制，与 MVCC 相对的是基于锁的并发控制。

MVCC 的最大优势：读不加锁，读写不冲突。数据库默认隔离级别：RR（Repeatable Read，可重复读），MVCC主要适用于Mysql的已提交读、可重复读隔离级别

### MVCC 的实现

MVCC是通过在每行记录后面保存两个隐藏的列来实现的。这两个列，一个保存了行的创建时间，一个保存行的过期时间（或删除时间）。当然存储的并不是实际的时间值，而是系统版本号（system version number)。每开始一个新的事务，系统版本号都会自动递增。事务开始时刻的系统版本号会作为事务的版本号，用来和查询到的每行记录的版本号进行比较。

- SELECT: 只查询版本早于当前事务版本的数据行；行的删除版本要么未定义，要么大于当前事务版本号；
- INSERT: 为新插入的每一行保存当前的系统版本号作为行版本号；
- DELETE: 为删除的每一行保存当前系统版本号作为行删除标识；
- UPDATE: InnoDB为插入一行新记录，保存当前系统版本号作为行版本号，同时保存当前系统版本号到原来的行作为行删除标识。

保存这两个额外系统版本号，使大多数读操作都可以不用加锁。这样设计使得读数据操作很简单，性能很好，并且也能保证只会读取到符合标准的行，不足之处是每行记录都需要额外的存储空间，需要做更多的行检查工作，以及一些额外的维护工作

## Reference

1. [浆水面韭菜花](https://www.jianshu.com/p/f692d4f8a53e)
