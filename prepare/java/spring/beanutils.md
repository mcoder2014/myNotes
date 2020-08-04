# BeanUtils

在我们实际项目开发过程中，我们经常需要将不同的两个对象实例进行属性复制，从而基于源对象的属性信息进行后续操作，而不改变源对象的属性信息,比如DTO数据传输对象和数据对象DO，我们需要将DO对象进行属性复制到DTO，但是对象格式又不一样，所以我们需要编写映射代码将对象中的属性值从一种类型转换成另一种类型。

这种转换最原始的方式就是手动编写大量的 get/set代码，当然这是我们开发过程不愿意去做的，因为它确实显得很繁琐。为了解决这一痛点，就诞生了一些方便的类库，常用的有 apache的 BeanUtils,spring的 BeanUtils, Dozer,Orika等拷贝工具。这篇文章主要介绍 Apache的BeanUtils 与 Spring 的BeanUtils，其他框架后续文章再做介绍

## Spring BeanUtils

```java
private static void copyProperties(Object source, Object target, @Nullable Class<?> editable,
   @Nullable String... ignoreProperties) throws BeansException {

  Assert.notNull(source, "Source must not be null");
  Assert.notNull(target, "Target must not be null");

  Class<?> actualEditable = target.getClass();
  if (editable != null) {
   if (!editable.isInstance(target)) {
    throw new IllegalArgumentException("Target class [" + target.getClass().getName() +
      "] not assignable to Editable class [" + editable.getName() + "]");
   }
   actualEditable = editable;
  }
  PropertyDescriptor[] targetPds = getPropertyDescriptors(actualEditable);
  List<String> ignoreList = (ignoreProperties != null ? Arrays.asList(ignoreProperties) : null);

  for (PropertyDescriptor targetPd : targetPds) {
   Method writeMethod = targetPd.getWriteMethod();
   if (writeMethod != null && (ignoreList == null || !ignoreList.contains(targetPd.getName()))) {
    PropertyDescriptor sourcePd = getPropertyDescriptor(source.getClass(), targetPd.getName());
    if (sourcePd != null) {
     Method readMethod = sourcePd.getReadMethod();
     if (readMethod != null &&
       ClassUtils.isAssignable(writeMethod.getParameterTypes()[0], readMethod.getReturnType())) {
      try {
       if (!Modifier.isPublic(readMethod.getDeclaringClass().getModifiers())) {
        readMethod.setAccessible(true);
       }
       Object value = readMethod.invoke(source);
       if (!Modifier.isPublic(writeMethod.getDeclaringClass().getModifiers())) {
        writeMethod.setAccessible(true);
       }
       writeMethod.invoke(target, value);
      }
      catch (Throwable ex) {
       throw new FatalBeanException(
         "Could not copy property '" + targetPd.getName() + "' from source to target", ex);
      }
     }
    }
   }
  }
 }
```

spring下的BeanUtils也是使用 copyProperties方法进行拷贝，只不过它的实现方式非常简单，就是对两个对象中相同名字的属性进行简单的get/set，仅检查属性的可访问性。成员变量赋值是基于目标对象的成员列表，并且会跳过ignore的以及在源对象中不存在，所以这个方法是安全的，不会因为两个对象之间的结构差异导致错误，但是必须保证同名的两个成员变量类型相同.

## Apache BeanUtils

```java
private static void copyProperties(Object source, Object target, @Nullable Class<?> editable,
   @Nullable String... ignoreProperties) throws BeansException {

  Assert.notNull(source, "Source must not be null");
  Assert.notNull(target, "Target must not be null");

  Class<?> actualEditable = target.getClass();
  if (editable != null) {
   if (!editable.isInstance(target)) {
    throw new IllegalArgumentException("Target class [" + target.getClass().getName() +
      "] not assignable to Editable class [" + editable.getName() + "]");
   }
   actualEditable = editable;
  }
  PropertyDescriptor[] targetPds = getPropertyDescriptors(actualEditable);
  List<String> ignoreList = (ignoreProperties != null ? Arrays.asList(ignoreProperties) : null);

  for (PropertyDescriptor targetPd : targetPds) {
   Method writeMethod = targetPd.getWriteMethod();
   if (writeMethod != null && (ignoreList == null || !ignoreList.contains(targetPd.getName()))) {
    PropertyDescriptor sourcePd = getPropertyDescriptor(source.getClass(), targetPd.getName());
    if (sourcePd != null) {
     Method readMethod = sourcePd.getReadMethod();
     if (readMethod != null &&
       ClassUtils.isAssignable(writeMethod.getParameterTypes()[0], readMethod.getReturnType())) {
      try {
       if (!Modifier.isPublic(readMethod.getDeclaringClass().getModifiers())) {
        readMethod.setAccessible(true);
       }
       Object value = readMethod.invoke(source);
       if (!Modifier.isPublic(writeMethod.getDeclaringClass().getModifiers())) {
        writeMethod.setAccessible(true);
       }
       writeMethod.invoke(target, value);
      }
      catch (Throwable ex) {
       throw new FatalBeanException(
         "Could not copy property '" + targetPd.getName() + "' from source to target", ex);
      }
     }
    }
   }
  }
 }
```

commons-beantutils 对于对象拷贝加了很多的检验，包括类型的转换，甚至还会检验对象所属的类的可访问性,可谓相当复杂，这也造就了它的差劲的性能

## Reference

1. [两难！到底用 Spring BeanUtils 还是 Apache BeanUtils？](https://mp.weixin.qq.com/s?__biz=MzIyNzc1ODQ0MQ==&mid=2247487705&idx=2&sn=d345f158f0395498bcfd4b44e0be0c3d&chksm=e85d08dfdf2a81c99f68c7ac1f7815ae589d0c46a3d4b5d0d769f77b22d7c386fafc0bdd9474&scene=126&sessionid=1596510471&key=d4010cb623e65047eb0136e74a2fc3eaeb5fb62eb7a42eae75ba6db544287cc8bdefd1c05be54f5ebe85bc029a1826e61a02287b3f668d95782561a6c06a3b7e513679d56e9546546c4bbb56d92d46af&ascene=1&uin=MjM1Mzc3NDI2Mw%3D%3D&devicetype=Windows+10+x64&version=62090529&lang=zh_CN&exportkey=AbuyjvVOaGjnKFFFrvhLYaw%3D&pass_ticket=3ugGQaS1VPPM0e2ZroNyMA8RZS5ue4PVxOr3HtPZXcjW2Yeuqin8%2Bb7wsT8Zj2oa)
