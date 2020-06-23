# Aop

## 主要注解

1. `@Before` Before advice: Advice that executes before a join point, but which does not have the ability to prevent execution flow proceeding to the join point (unless it throws an exception).
2. `@AfterReturning` After returning advice: Advice to be executed after a join point completes normally: for example, if a method returns without throwing an exception.
3. `@AfterThrowing` After throwing advice: Advice to be executed if a method exits by throwing an exception.
4. `@After` After advice: Advice to be executed regardless of the means by which a join point exits (normal or exceptional return).
5. `@Around` Around advice: Advice that surrounds a join point such as a method invocation. This is the most powerful kind of advice. Around advice can perform custom behavior before and after the method invocation. It is also responsible for choosing whether to proceed to the join point or to shortcut the advised method execution by returning its own return value or throwing an exception.

## `@Transactional`

线程内可见，其他线程没办法看到没有提交的事务结果。

## Reference

1. [howtodoinjava.com/spring-aop](https://howtodoinjava.com/spring-aop/spring-aop-aspectj-example-tutorial-using-annotation-config/)