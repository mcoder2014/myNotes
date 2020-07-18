# 面向对象设计的原则

## 首先的五个原则

### 单一职责原则 SRP

SRP The Single Responsibility Principle

认为对象应该仅具有一种单一功能的概念。

### 开闭原则 OCP

OCP The Open Closed Principle

认为“软件体应该是对于扩展开放的，但是对于修改封闭的”的概念。

### 里氏替换原则 LSP

LSP The Liskov Substitution Principle

认为“程序中的对象应该是可以在不改变程序正确性的前提下被它的子类所替换的”的概念。

### 接口隔离原则 ISP

ISP The Interface Segregation Principle

认为“多个特定客户端接口要好于一个宽泛用途的接口”的概念。

### 依赖倒置原则 DIP

DIP The Dependency Inversion Principle

认为一个方法应该遵从“依赖于抽象而不是一个实例”的概念。依赖注入是该原则的一种实现方式。

## 关于包的三个原则

The next six principles are about packages. In this context a package is a binary deliverable like a .jar file, or a dll as opposed to a namespace like a java package or a C++ namespace.

The first three package principles are about package cohesion, they tell us what to put inside packages:

### 重用发布等价原则 REP

REP The Release Reuse Equivalency Principle

The granule of reuse is the granule of release.

### 共同封闭原则 CCP

CCP The Common Closure Principle

Classes that change together are packaged together.

### 共同重用原则 CRP

CRP The Common Reuse Principle

Classes that are used together are packaged together.

## 关于包组合的原则

The last three principles are about the couplings between packages, and talk about metrics that evaluate the package structure of a system.

### 无环依赖原则 ADP

ADP The Acyclic Dependencies Principle

The dependency graph of packages must have no cycles.

### 稳定依赖原则 SDP

SDP The Stable Dependencies Principle

Depend in the direction of stability.

### 稳定抽象原则 SAP

SAP The Stable Abstractions Principle

Abstractness increases with stability.

## Reference

1.[Bob Martin](http://butunclebob.com/ArticleS.UncleBob.PrinciplesOfOod)
