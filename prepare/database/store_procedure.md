# 存储过程 store procedure

## 存储过程

在 mysql 中，存储过程不具有原子性，oracle 中是原子的。 比较好的解决方案，在存储过程中使用事务。

```SQL
CREATE PROCEDURE test_proc_ins(
IN i_id INT,
IN i_name VARCHAR(100)
)
BEGIN
start transaction; --整个存储过程指定为一个事务
           INSERT INTO testproc VALUES (i_id, i_name);
           INSERT INTO testproc VALUES (i_id+1, i_name); -- 这里把id+1，避免主键冲突
commit; -- 语句1。必须主动提交
END;
```
