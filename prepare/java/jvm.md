# JVM 的一些话题

Java Virtual machine (JVM) is the virtual machine that runs the Java bytecodes. You get this bytecode by compiling the .java files into .class files. .class files contain the bytecodes understood by the JVM.

In the real world, JVM is a specification that provides a runtime environment in which Java bytecode can be executed. Different vendors provide different implementations of this specification. For example, this wiki page lists down different JVM implementations.

Most popular implementation of JVM is Hotspot which is owned and provided by Oracle Corporation. (Previously by Sun Microsystems, Inc.).

JVM delivers the optimal performance for Java applications using many advanced techniques, incorporating a state-of-the-art memory model, garbage collector, and adaptive optimizer.

JVM comes in two different flavors – client and server. Although the Server and the Client VMs are similar, the Server VM has been specially tuned to maximize peak operating speed. It is intended for executing long-running server applications, which need the fastest possible operating speed more than a fast start-up time or smaller runtime memory footprint. Developers can choose which system they want by specifying -client or -server.

The JVM is called virtual because it provides a machine interface that does not depend on the underlying operating system and machine hardware architecture. This independence from hardware and the operating system is a cornerstone of the write-once-run-anywhere value of Java programs.

## JRE JDK JVM 的关系


# Reference
1. [jdk-jre-jvm](https://howtodoinjava.com/java/basics/jdk-jre-jvm/)