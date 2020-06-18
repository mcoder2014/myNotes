# 队列
队列的 insert 操作通常叫做 enqueue，delete 操作通常叫做 dequeue，队列的特点是先进先出，“First in, first out”。

## 用数组实现队列
- 一个大小为 n 的队列可以表示 n-1 个元素的队列，队列有 head 和 tail 属性，元素为`Q.head, Q.head+1, ... ,Q.tail-1`。
- 判断队列为空：Q.head == Q.tail, 初始化时，Q.head = Q.tail = 0；当我们对一个为空的队列执行 dequeue 操作成为下溢（underflows）。
- 判断队列已满，`Q.head == Q.tail + 1`；如果尝试向一个已经满了的队列加入元素，成为溢出（overflows）

```
// 忽略了对队列溢出检查的伪代码

ENQUEUE(Q, x)
    Q[Q.tail] = x
    if Q.tail == Q.length
        Q.tail = 1
    else
        Q.tail = Q.tail + 1


DEQUEUE(Q)
    x = Q[Q.head]
    if Q.head == Q.length
        Q.head = 1
    else
        Q.head = Q.head + 1
    return x

```