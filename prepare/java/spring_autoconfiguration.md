# Spring 自动配置

## 常规操作

1. 引入 spring jar 包；
2. 引入 mybatis jar 包；
3. 引入整合时的 jar 包；
4. 写代码进行 bean 注册；
   1. 注册 SqlSessionFactory
   2. 指定 mybatis-config.xml 配置文件路径
   3. 指定 mapper.xml 文件路径
   4. 指定源码包路径并扫描所有 @Mapper 注解接口

## 自动配置

这里面也就自动配置jar包稍微特殊一点，它里面包含一些带有“条件注解”的Bean注册。所以这些代码需要在SpringBoot中运行。

autoconfigure jar 包中的约定文件 spring.factories，位于jar 包的 META_INF 目录下。具体内容是一个key/value类型的内容，key是固定的，就是SpringBoot自动配置的注解EnableAutoConfiguration的全名。value就是第三方提供的自动配置类MybatisAutoConfiguration的全名。这其实就是一个挂接，通过这种方式，第三方提供的自动配置就可以被SpringBoot执行了，然后Bean就会被注册了。

## Reference

1. [自动配置](https://mp.weixin.qq.com/s/_DH7a0zONmeANxgiFucTnA)
