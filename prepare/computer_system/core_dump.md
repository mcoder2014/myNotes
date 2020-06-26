# core dump 文件

## 什么是 core dump 文件

在Linux下程序不寻常退出时，内核会在当前工作目录下生成一个core文件（是一个内存映像，同时加上调试信息）。使用gdb来查看core文件，可以指示出导致程序出错的代码所在文件和行数。

ulimit 中有 core 文件的限制。
