# Redis 事务

MULTI 、 EXEC 、 DISCARD 和 WATCH 是 Redis 事务相关的命令。事务可以一次执行多个命令， 并且带有以下两个重要的保证：

* 事务是一个单独的隔离操作：事务中的所有命令都会序列化、按顺序地执行。事务在执行的过程中，不会被其他客户端发送来的命令请求所打断。
* 事务是一个原子操作：事务中的命令要么全部被执行，要么全部都不执行。

EXEC 命令负责触发并执行事务中的所有命令：

* 如果客户端在使用 MULTI 开启了一个事务之后，却因为断线而没有成功执行 EXEC ，那么事务中的所有命令都不会被执行。
* 另一方面，如果客户端成功在开启事务之后执行 EXEC ，那么事务中的所有命令都会被执行。

当使用 AOF 方式做持久化的时候， Redis 会使用单个 write(2) 命令将事务写入到磁盘中。然而，如果 Redis 服务器因为某些原因被管理员杀死，或者遇上某种硬件故障，那么可能只有部分事务命令会被成功写入到磁盘中。如果 Redis 在重新启动时发现 AOF 文件出了这样的问题，那么它会退出，并汇报一个错误。

## 用法

MULTI 命令开始一个事务。MULTI 执行后，客户端继续执行任意多条命令，命令不会立即执行，而是放在一个队列里。当 EXEC命令调用时，队列中的所有命令执行。当DISCARD命令调用时，客户端可以清空事务队列，放弃执行事务。

## 事务遇到错误

* 执行 EXEC 前，入队的命令有语法错误：对于发生在 EXEC 执行之前的错误，**客户端以前的做法是检查命令入队所得的返回值：如果命令入队时返回 QUEUED ，那么入队成功；否则，就是入队失败。**如果有命令在入队时失败，那么大部分客户端都会停止并取消这个事务。
* 执行 EXEC 后，队列中有命令调用失败：至于那些在 EXEC 命令执行之后所产生的错误， 并没有对它们进行特别处理： 即使事务中有某个/某些命令在执行时产生了错误， 事务中的其他命令仍然会继续执行。

## Redis 不支持 Rollback

* Redis 命令只会因为错误的语法而失败（并且这些问题不能在入队时发现），或是命令用在了错误类型的键上面：这也就是说，**从实用性的角度来说，失败的命令是由编程错误造成的，而这些错误应该在开发的过程中被发现，而不应该出现在生产环境中**。
* **因为不需要对回滚进行支持，所以 Redis 的内部可以保持简单且快速。**

## WATCH 命令

WATCH 命令可以为 Redis 事务提供 check-and-set （CAS）行为。

被 WATCH 的键会被监视，并会发觉这些键是否被改动过了。 如果有至少一个被监视的键在 EXEC 执行之前被修改了， 那么整个事务都会被取消， EXEC 返回nil-reply来表示事务已经失败。

WATCH 使得 EXEC 命令需要有条件地执行： 事务只能在所有被监视键都没有被修改的前提下执行， 如果这个前提不能满足的话，事务就不会被执行。

## Redis 脚本

从定义上来说，Redis 中的脚本也是事务，所以任何事务中可以完成的事，在脚本中也可以完成。

## Reference

1. [Redis 事务](http://www.redis.cn/topics/transactions.html)