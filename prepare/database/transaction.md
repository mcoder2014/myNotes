# 事务
## 事务特性
ACID:
1. 原子性
2. 一致性
3. 隔离性
4. 持久性

## 事务四个级别
1. 未提交读 (脏读、不可重复读、幻读)
2. 提交读   (不可重复读、幻读)
3. 可重复读 (幻读)
4. 序列化   (x)

mysql 默认的事务级别 可重复度

## 事务命令
```SQL
START TRANSACTION or BEGIN TRANSACTION   # 开始事务
COMMIT  # 提交
ROLLBACK    # 回滚
SAVEPOINT   # 保存点，可以 ROLLBACK 的还原点
SET TRANSACTION # 命名事务
```

**事务例子**
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

# MVCC