# http 和 https

## http

### 格式

#### 请求头

```text
请求方法<空格>URL<空格>协议版本
头部字段:值
头部字段:值
...
头部字段:值
<空行>
Body

实例
GET /hello.txt HTTP/1.1
User-Agent: curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3
Host: www.example.com
Accept-Language: en, mi
```

#### 响应头

```text
状态行
消息报头
空行
响应正文


HTTP/1.1 200 OK
Date: Mon, 27 Jul 2009 12:28:53 GMT
Server: Apache
Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT
ETag: "34aa387-d-1568eb00"
Accept-Ranges: bytes
Content-Length: 51
Vary: Accept-Encoding
Content-Type: text/plain
```

### 常见头部字段

### 方法

1. **Get**  请求指定的页面信息，并返回实体主体。
2. **Post**  向指定资源提交数据进行处理请求（例如提交表单或者上传文件）。数据被包含在请求体中。POST 请求可能会导致新的资源的建立和/或已有资源的修改。
3. **Put**  从客户端向服务器传送的数据取代指定的文档的内容。
4. **Delete**  请求服务器删除指定的页面。
5. **Head**  类似于 GET 请求，只不过返回的响应中没有具体的内容，用于获取报头
6. **Connect**  HTTP/1.1 协议中预留给能够将连接改为管道方式的代理服务器。
7. **Options**  允许客户端查看服务器的性能。
8. **Trace**  回显服务器收到的请求，主要用于测试或诊断。
9. **Patch**  是对 PUT 方法的补充，用来对已知资源进行局部更新 。

#### post get 区别

1. Get是从服务器上获取数据，Post是向服务器传送数据。
2. Get是把参数数据队列加到提交表单的Action属性所指向的URL中，值和表单内各个字段一一对应，在URL中可以看到。
3. Get传送的数据量小，不能大于2KB；Post传送的数据量较大，一般被默认为不受限制。
4. 根据HTTP规范，GET用于信息获取，而且应该是安全的和幂等的。

### HTTP 报头字段

- Content-Type 指示网络文件的类型或者网页的编码

    ```HTTP
    Content-Type: text/html; charset=utf-8
    Content-Type: multipart/form-data; boundary=something
    ```

- Accept 能够接受的回应内容类型 `Accept: text/plain`
- Accept-Charset 能够接受的字符集 `Accept-Charset: utf-8`
- Accept-Encoding 能够接受的编码格式 `Accept-Encoding: gzip, deflate`
- Accept-Language 能够接受的自然语言列表 `Accept-Language: en-US`
- Authorization 认证信息 `Authorization: Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==`
- Cache-Control 设置 cache 机制 `Cache-Control: no-cache`
- Connection 设置连接类型 `Connection: keep-alive Connection: Upgrade`
- Content-Length 请求体长度 `Content-Length: 348`
- Host 服务器域名,自超文件传输协议版本1.1（HTTP/1.1）开始便是必需字段。 `Host: en.wikipedia.org`
- Origin 跨域资源访问 `Origin: http://www.example-social-network.com`
- User-Agent 用户的浏览器身份标识 `User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:12.0) Gecko/20100101 Firefox/21.0`
- Upgrade 请求服务器升级协议 `Upgrade: HTTP/2.0, SHTTP/1.3, IRC/6.9, RTA/x11`

### 响应码

- 1** 服务器收到请求，需要请求者继续执行操作
  - 100 continue 客户端继续请求
  - 101 switching proptcols 切换协议
- 2** 成功
  - 200 OK 请求成功。 Get post
  - 201 Created 已创建，成功请求并创建了新的资源
  - 202 Accepted 已接收，但未完成处理
- 3** 重定向
  - 301 永久重定向
  - 302 临时移动
- 4** 客户端错误
  - 401 客户需要身份认证
  - 403 无访问权限
  - 404 页面不存在
- 5** 服务端错误
  - 500 服务器内部错误

### 幂等性

幂等性就是用户对于同一操作发起的一次请求或者多次请求的结果是一致的，不会因为多次点击而产生了副作用。

幂等性是分布式系统设计中十分重要的概念，具有这一性质的接口在设计时总是秉持这样的一种理念：**调用接口发生异常并且重复尝试时，总是会造成系统所无法承受的损失，所以必须阻止这种现象的发生。**

#### 幂等性常见思路

1. MVCC 乐观锁：版本号不一致的操作无法执行
2. 去重
3. Token 机制：token 使用一次后失效

## https

### HTTPS 非对称加密、对称加密

HTTPS其实是有两部分组成：HTTP + SSL / TLS，也就是在HTTP上又加了一层处理加密信息的模块。服务端和客户端的信息传输都会通过TLS进行加密，所以传输的数据都是加密后的数据。

**数字证书** :采用HTTPS协议的服务器必须要有一套数字证书，可以自己制作，也可以向组织申请。区别就是自己颁发的证书需要客户端验证通过，才可以继续访问

**传送证书** :这个证书其实就是公钥，只是包含了很多信息，如证书的颁发机构，过期时间等等。

**客户端解析证书(非对称加密)** :这部分工作是有客户端的TLS来完成的，首先会验证公钥是否有效，比如颁发机构，过期时间等等，如果发现异常，则会弹出一个警告框，提示证书存在问题。如果证书没有问题，那么就生成一个随机值。然后用证书对该随机值进行加密。就好像上面说的，把随机值用锁头锁起来，这样除非有钥匙，不然看不到被锁住的内容。

**传送加密信息** ：这部分传送的是用证书加密后的随机值，目的就是让服务端得到这个随机值，以后客户端和服务端的通信就可以通过这个随机值来进行加密解密了。

**服务端解密信息(转换为对称加密)** :服务端用私钥解密后，得到了客户端传过来的随机值(私钥)，然后把内容通过该值进行对称加密。所谓对称加密就是，将信息和私钥通过某种算法混合在一起，这样除非知道私钥，不然无法获取内容，而正好客户端和服务端都知道这个私钥，所以只要加密算法够彪悍，私钥够复杂，数据就够安全。

## 浏览器访问一个网页的过程

简要的过程：

1. DNS 解析:将域名解析成 IP 地址
2. TCP 连接：TCP 三次握手
3. 发送 HTTP 请求
4. 服务器处理请求并返回 HTTP 报文
5. 浏览器解析渲染页面
6. 断开连接：TCP 四次挥手

### 浏览器如何通过域名去查询 URL 对应的 IP 呢

1. 浏览器缓存：浏览器会按照一定的频率缓存 DNS 记录。
2. 操作系统缓存：如果浏览器缓存中找不到需要的 DNS 记录，那就去操作系统中找。
3. 路由缓存：路由器也有 DNS 缓存。
4. ISP 的 DNS 服务器：ISP 是互联网服务提供商(Internet Service Provider)的简称，ISP 有专门的 DNS 服务器应对 DNS 查询请求。
5. 根服务器：ISP 的 DNS 服务器还找不到的话，它就会向根服务器发出请求，进行递归查询（DNS 服务器先问根域名服务器.com 域名服务器的 IP 地址，然后再问.baidu 域名服务器，依次类推）

## Reference

1. [wikipake](https://zh.wikipedia.org/wiki/HTTP%E5%A4%B4%E5%AD%97%E6%AE%B5#%E5%AD%97%E6%AE%B5%E5%90%8D)
