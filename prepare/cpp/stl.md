# STL

## STL 六大部件

* 容器 container
* 算法 algorithm
* 迭代器 iterator
* 仿函数 functor
* 适配器 adapater
* 配接器 allocator

容器(contaioner)：

包含了各种数据结构。例如动态数组(vector)，链表(list)，双端队列(deque)，集合(set)，映射(map)等，作用是在一块空间内存放数据。从实现的角度看，STL容器是一种类模板(class template)。

算法(algorithm)：

各种常用的算法，如sort，search，copy，erase，max，min等，作用是实现对数据的操作。从实现的角度看，STL算法是一种函数模板(function template)。

迭代器(iterator)：

包含了各种容器存取操作。例如operator*，operator->，operator++，operator- -等指针操作。
作用是 容器 与 算法 之间的胶合剂。算法通过迭代器存取容器的内容。
从实现的角度看，迭代器是一种将指针操作重载的类模板(class template)。
迭代器共有五种类型已经它们的衍生变化。
所有的容器都附带自己的专属迭代器，因为只有容器设计者才知道如何遍历自己的元素。
原生指针(native pointer)也是一种迭代器。

仿函数(functor)：

行为类似函数，可作为算法的某种策略(policy)。
从实现的角度看，仿函数是一种重载了operator()的类(class)或类模板(class template)。
一般 函数指针(指向函数的指针)可视为狭义的仿函数。

适配器(adapter)：

一种用来修饰容器(container)或仿函数(functor)或迭代器(iterator)接口的东西。
改变 容器 接口的称为 容器适配器(container adapter)。
改变 仿函数 接口的称为 仿函数适配器(functor adapter)。
改变 迭代器 接口的称为 迭代器适配器(iterator adapter)。

配接器(allocator)：

负责空间的配置和管理。
从实现的角度来看，配置器是一种实现了 动态 空间配置，空间管理，空间释放的类模板(class template).

## Reference

1. [侯捷 C++ STL体系结构与内核](https://www.bilibili.com/video/BV1db411q7B8?from=search&seid=9685031180855371704)
