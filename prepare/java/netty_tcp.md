# Netty TCP 粘包

## 对于粘包和拆包问题，常见的解决方案有四种

1. 客户端在发送数据包的时候，**每个包都固定长度**，比如1024个字节大小，如果客户端发送的数据长度不足1024个字节，则通过补充空格的方式补全到指定长度；
2. 客户端在每个**包的末尾使用固定的分隔符，例如\r\n**，如果一个包被拆分了，则等待下一个包发送过来之后找到其中的\r\n，然后对其拆分后的头部部分与前一个包的剩余部分进行合并，这样就得到了一个完整的包；
3. 将**消息分为头部和消息体，在头部中保存有当前整个消息的长度**，只有在读取到足够长度的消息之后才算是读到了一个完整的消息；
4. 通过**自定义协议**进行粘包和拆包的处理。

## Netty 解决方法

### FixedLengthFrameDecoder

对于使用固定长度的粘包和拆包场景，可以使用FixedLengthFrameDecoder，该解码一器会每次读取固定长度的消息，如果当前读取到的消息不足指定长度，那么就会等待下一个消息到达后进行补足。其使用也比较简单，只需要在构造函数中指定每个消息的长度即可。

### LineBasedFrameDecoder与DelimiterBasedFrameDecoder

对于通过分隔符进行粘包和拆包问题的处理，Netty提供了两个编解码的类，LineBasedFrameDecoder和DelimiterBasedFrameDecoder。这里LineBasedFrameDecoder的作用主要是通过换行符，即\n或者\r\n对数据进行处理；而DelimiterBasedFrameDecoder的作用则是通过用户指定的分隔符对数据进行粘包和拆包处理。同样的，这两个类都是解码一器类，而对于数据的编码，也即在每个数据包最后添加换行符或者指定分割符的部分需要用户自行进行处理。

### LengthFieldBasedFrameDecoder与LengthFieldPrepender

这里LengthFieldBasedFrameDecoder与LengthFieldPrepender需要配合起来使用，其实本质上来讲，这两者一个是解码，一个是编码的关系。它们处理粘拆包的主要思想是在生成的数据包中添加一个长度字段，用于记录当前数据包的长度。LengthFieldBasedFrameDecoder会按照参数指定的包长度偏移量数据对接收到的数据进行解码，从而得到目标消息体数据；而LengthFieldPrepender则会在响应的数据前面添加指定的字节数据，这个字节数据中保存了当前消息体的整体字节数据长度。

## Reference

1. [Netty 解决粘包和拆包问题的四种方案](https://mp.weixin.qq.com/s?__biz=MzAxODcyNjEzNQ==&mid=2247498185&idx=3&sn=3350f46f9391857bfb2dcf6f6cbb8de7&chksm=9bd35451aca4dd47147ccc57a792a0cc59bdb157d59ef79b31026f94697619b1671825a67e3d&scene=126&sessionid=1596510495&key=6270cffc7a2fb38af8d25a737159f21a44f4532622e2a5887b71634afd29f0218d61eff2d175a9f30f903eb8701fc5762610ed0843dfcfe3a0d213312d8753ee41b77bbbcdde1c57147502023fbccaef&ascene=1&uin=MjM1Mzc3NDI2Mw%3D%3D&devicetype=Windows+10+x64&version=62090529&lang=zh_CN&exportkey=Ae3dDwHqIdsMrHsMQ5%2Bhia0%3D&pass_ticket=3ugGQaS1VPPM0e2ZroNyMA8RZS5ue4PVxOr3HtPZXcjW2Yeuqin8%2Bb7wsT8Zj2oa)
