# socket 连接建立的过程

## 面向 TCP 的 socket

### 面型 TCP 的服务端执行流程

1. `socket()`
2. `bind()`
3. `listen()`
4. `accpet()`
5. `recv()`
6. `write()`
7. `close()`

### 面向 TCP 的客户端执行流程

1. `socket()`
2. `connect()`
3. `write()`
4. `read()`
5. `close()`

## 面向 UDP 的 socket

因为 UDP 是无连接的，所以不需要建立连接。

### 面向 UDP 的服务端执行流程

1. `socket()`
2. `bind()`
3. `recvfrom()`
4. `sendto()`
5. `close()`

### 面向 UDP 的客户端执行流程

1. `socket()`
2. `sendto()`
3. `recvfrom()`
4. `close()`

## Reference

1. [APUE 3.rd](#APUE)
