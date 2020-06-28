# C++11 特性

## 移动语义和移动构造函数

## std::move()

## 对 const T& 可以做std::move() 嘛

## 左值右值

C++( 包括 C) 中所有的表达式和变量要么是左值，要么是右值。通俗的左值的定义就是非临时对象，那些可以在多条语句中使用的对象。所有的变量都满足这个定义，在多条代码中都可以使用，都是左值。右值是指临时的对象，它们只在当前的语句中有效。[IBM 右值引用与转移语义](https://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/index.html)

有一种甄别表达式是否左值的方法，是检查能否获得该表达式的地址；如果可以取得，基本上可以断定是左值表达式；如果不能取得则通常是右值。

C++ 中所有值都属于 左值、右值两者之一；若细分的话，右值可以分为：纯右值、将亡值。

## 右值引用类型

我们可以理解右值为临时对象，像有些函数返回的对象是临时对象，该句执行完毕就会释放临时对象空间，因此留下右值的引用在以前并没有用。

C++11 是提出了右值引用，可以延长临时对象的生存周期，其创建方法为`type && vb = xx;`对应的左值引用的生命符号为`&`。

```C++
#include <iostream>
#include <string>

int main()
{
    std::string s1 = "Test";
//  std::string&& r1 = s1;           // 错误：不能绑定到左值

    const std::string& r2 = s1 + s1; // okay：到 const 的左值引用延长生存期
//  r2 += "Test";                    // 错误：不能通过到 const 的引用修改

    std::string&& r3 = s1 + s1;      // okay：右值引用延长生存期
    r3 += "Test";                    // okay：能通过到非 const 的引用修改
    std::cout << r3 << '\n';
}
```

更重要的是，当函数同时具有右值引用和左值引用的重载时，右值引用重载绑定到右值（包含纯右值和亡值），而左值引用重载绑定到左值：

```C++
#include <iostream>
#include <utility>

void f(int& x) {
    std::cout << "lvalue reference overload f(" << x << ")\n";
}

void f(const int& x) {
    std::cout << "lvalue reference to const overload f(" << x << ")\n";
}

void f(int&& x) {
    std::cout << "rvalue reference overload f(" << x << ")\n";
}

int main() {
    int i = 1;
    const int ci = 2;
    f(i);  // 调用 f(int&)
    f(ci); // 调用 f(const int&)
    f(3);  // 调用 f(int&&)
           // 若不提供 f(int&&) 重载则会调用 f(const int&)
    f(std::move(i)); // 调用 f(int&&)

    // 右值引用变量在用于表达式时是左值
    int&& x = 1;
    f(x);            // calls f(int& x)
    f(std::move(x)); // calls f(int&& x)
}
```

## 移动语义(Move Sementics)与精准传递(Perfect Forwarding)

移动语义是通过盗取将亡值的变量内存空间，首先确保该部分空间之后不会使用，然后将该空间占为己有，看起来像是一个拷贝操作。
移动语义位于头文件`#include<algorithm>`，函数名为`std::move`。

```C++
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <thread>
#include <chrono>

void f(int n)
{
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "thread " << n << " ended" << '\n';
}

int main()
{
    std::vector<std::thread> v;
    v.emplace_back(f, 1);
    v.emplace_back(f, 2);
    v.emplace_back(f, 3);
    std::list<std::thread> l;
    // copy() 无法编译，因为 std::thread 不可复制

    std::move(v.begin(), v.end(), std::back_inserter(l));
    for (auto& t : l) t.join();
}
```

## 自动类型推导

`auto`和`decltype` 关键词是新增的关键词，我们知道C++是强类型语言，但使用这两个关键词，可以不用手写完整类型，而是让编译器自行推导真实类型。

`auto`用法非常简单，示例如下：

```C++
#include <iostream>
#include <utility>

template<class T, class U>
auto add(T t, U u) { return t + u; } // 返回类型是 operator+(T, U) 的类型

// 在其所调用的函数返回引用的情况下
// 函数调用的完美转发必须用 decltype(auto)
template<class F, class... Args>
decltype(auto) PerfectForward(F fun, Args&&... args)
{
    return fun(std::forward<Args>(args)...);
}

template<auto n> // C++17 auto 形参声明
auto f() -> std::pair<decltype(n), decltype(n)> // auto 不能从花括号初始化器列表推导
{
    return {n, n};
}

int main()
{
    auto a = 1 + 2;            // a 的类型是 int
    auto b = add(1, 1.2);      // b 的类型是 double
    static_assert(std::is_same_v<decltype(a), int>);
    static_assert(std::is_same_v<decltype(b), double>);

    auto c0 = a;             // c0 的类型是 int，保有 a 的副本
    decltype(auto) c1 = a;   // c1 的类型是 int，保有 a 的副本
    decltype(auto) c2 = (a); // c2 的类型是 int&，为 a 的别名
    std::cout << "a, before modification through c2 = " << a << '\n';
    ++c2;
    std::cout << "a, after modification through c2 = " << a << '\n';

    auto [v, w] = f<0>(); // 结构化绑定声明

    auto d = {1, 2}; // OK：d 的类型是 std::initializer_list<int>
    auto n = {5};    // OK：n 的类型是 std::initializer_list<int>
//  auto e{1, 2};    // C++17 起错误，之前为 std::initializer_list<int>
    auto m{5};       // OK：C++17 起 m 的类型为 int，之前为 initializer_list<int>
//  decltype(auto) z = { 1, 2 } // 错误：{1, 2} 不是表达式

    // auto 常用于无名类型，例如 lambda 表达式的类型
    auto lambda = [](int x) { return x + 3; };

//  auto int x; // 于 C++98 合法，C++11 起错误
//  auto x;     // 于 C 合法，于 C++ 错误
}
```

`decltype` 的用处则是检查实体的声明类型，或者表达式的类型和值的类型。用法如下：`decltype(实体/表达式)`。可以使用另一个的实体的类型来定义新的变量。

```C++
#include <iostream>

struct A { double x; };
const A* a;

decltype(a->x) y;       // y 的类型是 double（其声明类型）
decltype((a->x)) z = y; // z 的类型是 const double&（左值表达式）

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) // 返回类型依赖于模板形参
{                                     // C++14 开始可以推导返回类型
    return t+u;
}

int main()
{
    int i = 33;
    decltype(i) j = i * 2;

    std::cout << "i = " << i << ", "
              << "j = " << j << '\n';

    auto f = [](int a, int b) -> int
    {
        return a * b;
    };

    decltype(f) g = f; // lambda 的类型是独有且无名的
    i = f(2, 2);
    j = g(3, 3);

    std::cout << "i = " << i << ", "
              << "j = " << j << '\n';
}
```

### 函数返回值后置

可以通过这种写法，将函数的返回值申明放在函数声明的最后；`auto function_name( 形参 ) (属性，如 override等) (异常说明，可选) -> 返回值类型`。
老实说，这种写法让我觉得自己写的不是C++，估计大部分情况我不回去使用这个特性吧。。。

```C++
// 返回指向 f0 的指针的函数
auto fp11() -> void(*)(const std::string&)
{
    return f0;
}
```

### 强制类型转换

C++11起已经不建议使用C语言样式的强制类型转换，推荐使用`static_cast、const_cast、reinterpret_cast、dynamic_cast`等方法的类型转换。

| 关键词 | 说明 |
| - | - |
| `static_cast` (常用) | 用于良性转换，一般不会导致意外发生，风险很低。 |
| `const_cast`| 用于 const 与非 const、volatile 与非 volatile 之间的转换。|
| `reinterpret_cast` | 高度危险的转换，这种转换仅仅是对二进制位的重新解释，不会借助已有的转换规则对数据进行调整，但是可以实现最灵活的 C++ 类型转换。 |
| `dynamic_cast` | 借助 RTTI，用于类型安全的向下转型（Downcasting）。 |

[C++四种类型转换运算符：static_cast、dynamic_cast、const_cast和reinterpret_cast](http://c.biancheng.net/cpp/biancheng/view/3297.html)

## 智能指针

见独立文档

## 一些新的关键词用法

### nullptr

据说通常C++头文件中NULL都是定义为`#define NULL 0`，因此本质上`NULL`的类型是`int`，使用`NULL`来表示空指针是非常不合适的行为，于是C++11重新定义了一个不是`int`类型且适用于空指针的关键词。
> 关键词 nullptr 代表指针字面量。它是 std::nullptr_t 类型的纯右值。存在从 nullptr 到任何指针类型及任何成员指针类型的隐式转换。同样的转换对于任何空指针常量也存在，空指针常量包括 std::nullptr_t 的值，以及宏 NULL。[nullptr，指针字面量](https://zh.cppreference.com/w/cpp/language/nullptr)

### 特殊成员函数

1. 默认构造函数
2. 复制构造函数
3. 移动构造函数 (C++11 起)
4. 复制赋值运算符
5. 移动赋值运算符 (C++11 起)
6. 析构函数

### default

我们知道`default`本身是`switch`语句的关键词，C++11中又扩展了新的用法，可以用来告诉编译器生成默认的成员函数（默认构造函数等）。
特殊成员函数以及比较运算符 (C++20 起)是仅有能被预置的函数，即使用 = default 替代函数体进行定义（细节见其相应页面）

例如：默认构造函数可以使用 `类名 ( ) = default ; (C++11 起)` 方式声明，然后可以不用在 `*.cpp`文件中写函数体实现，这个函数会使用编译器默认生成。

### delete 弃置函数

delete的新用法--弃置函数，相比于让对象中的构造函数为私有，现在有了删除该函数的方法。
> 如果取代函数体而使用特殊语法 `= delete ;`，则该函数被定义为弃置的（deleted）。任何弃置函数的使用都是非良构的（程序无法编译）。这包含调用，包括显式（以函数调用运算符）及隐式（对弃置的重载运算符、特殊成员函数、分配函数等的调用），构成指向弃置函数的指针或成员指针，甚或是在不求值表达式中使用弃置函数。但是，允许隐式 ODR 式使用 刚好被弃置的非纯虚成员函数。

```C++
struct sometype
{
    void* operator new(std::size_t) = delete;
    void* operator new[](std::size_t) = delete;
};
sometype* p = new sometype; // 错误：尝试调用弃置的 sometype::operator new
```

### override

这个关键词翻译为改写，当指定一个虚函数覆盖另一个虚函数时使用，[Effective Modern C++](https://item.jd.com/12348026.html)一书中建议在该情况时一定加上该关键词，这样可以让编译器帮助我们检查我们是否正确定义了覆盖的函数（如果不正确定义则会编译报错）。

这部分代码将不会正确编译，因为加了 override 后，编译器会为我们寻找继承的基类中对应的虚函数，而这里就可以发现我们函数声明上的一些错误。而如果不加override，这里会成功编译，但绝对不是我们想要的编译结果。

```C++
/*
 * Key idea:
 *
 *   The below code won't compile, but, when written this way, compilers will
 *   kvetch about all the overriding-related problems.
 */

class Base {
public:
  virtual void mf1() const;
  virtual void mf2(int x);
  virtual void mf3() &;
  void mf4() const;
};

// Uncomment this, compile and see the compiler errors.
//class Derived: public Base {
//public:
//  virtual void mf1() override;
//  virtual void mf2(unsigned int x) override;
//  virtual void mf3() && override;
//  void mf4() const override;
//};
```

可以只有override修饰的函数声明正确才能够成功编译。

```C++
/*
 * Key idea:
 *
 *   This the code-example that uses override and is correct.
 */

class Base {
public:
  virtual void mf1() const;
  virtual void mf2(int x);
  virtual void mf3() &;
  virtual void mf4() const;
};

class Derived: public Base {
public:
  virtual void mf1() const override;
  virtual void mf2(int x) override;
  virtual void mf3() & override;
  void mf4() const override;         // adding "virtual" is OK,
};                                   // but not necessary
```

### final

声明某一个虚函数不得被覆盖。

### ( )、{ }初始化

有更多的方法初始化一个对象，比如[花括号初始化列表](https://zh.cppreference.com/w/cpp/language/list_initialization)实例如下：

```C++
/*
 * Key idea:
 *
 *   The treatment of braced initializers is the only way in which auto type
 *   deduction and template type deduction differ.
 */

#include <initializer_list>

template<typename T>  // template with parameter
void f(T param) {}    // declaration equivalent to
                      // x's declaration

template<typename T>
void f2(std::initializer_list<T> initList) {}

int main()
{
  {
    int x1 = 27;
    int x2(27);
    int x3 = {27};
    int x4{27};
  }

  {
    auto x1 = 27;    // type is int, value is 27
    auto x2(27);     // ditto
    auto x3 = {27};  // type is std::initializer_list<int>,
                     // value is {27}
    auto x4{27};     // ditto

    //auto x5 = {1, 2, 3.0};  // error! can't deduce T for
    //                        // std::initializer_list<T>
  }

  {
    auto x = { 11, 23, 9 };  // x's type is
                             // std::initializer_list<int>

    //f({ 11, 23, 9 });        // error! can't deduce type for T

    f2({ 11, 23, 9 });        // T deduced as int, and initList's
                              // type is std::initializer_list<int>
  }
}
```

### using 别名

除了 `typedef`关键词，还可以使用`using`关键词创建别名，[Effective Modern C++](https://item.jd.com/12348026.html)一书更推荐使用别名声明。

```C++
/*
 * Key Idea:
 *
 *   Using alias declarations is easier to read than function pointers.
 */

#include <string>

// FP is a synonym for a pointer to a function taking an int and
// a const std::string& and returning nothing
typedef void (*FP)(int, const std::string&);    // typedef

// same meaning as above
using FP = void (*)(int, const std::string&);   // alias
                                                // declaration

```

### 限定作用域的 枚举类型

通过在枚举类型定义中加一个关键词，可以限制枚举类型的作用域。`enum test`-> `enum class test`；

```C++
/*
 * Key Idea:
 *
 *   In C++11, the names of scoped enums do not belong to the scope containing
 *   the enum.
 */

enum class Color { black, white, red };  // black, white, red
                                         // are scoped to Color

auto white = false;              // fine, no other
                                 // "white" in scope

//Color c1 = white;                 // error! no enumerator named
                                 // "white" is in this scope

Color c2 = Color::white;          // fine

auto c3 = Color::white;           // also fine (and in accord
                                 // with Item4's advice)
```

### 基于范围的for循环

C++也可以像python语言那样使用基于范围的for循环了，是一个进步吧，集各家之所长。
基于范围的for循环语法是`for(范围声明:范围表达式)`。其中，范围声明：一个具名变量的声明，其类型是由 范围表达式 所表示的序列的元素的类型，或该类型的引用，通常用 auto 说明符进行自动类型推导；范围表达式：任何可以表示一个合适的序列（数组，或定义了 begin 和 end 成员函数或自由函数的对象，见下文）的表达式，或一个花括号初始化器列表，基本上std中几个常见容器，如：vector、list等都是支持基于范围的for循环的。

```C++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {0, 1, 2, 3, 4, 5};

    for (const int& i : v) // 以 const 引用访问
        std::cout << i << ' ';
    std::cout << '\n';

    for (auto i : v) // 以值访问，i 的类型是 int
        std::cout << i << ' ';
    std::cout << '\n';

    for (auto& i : v) // 以引用访问，i 的类型是 int&
        std::cout << i << ' ';
    std::cout << '\n';

    for (int n : {0, 1, 2, 3, 4, 5}) // 初始化器可以是花括号初始化器列表
        std::cout << n << ' ';
    std::cout << '\n';

    int a[] = {0, 1, 2, 3, 4, 5};
    for (int n : a) // 初始化器可以是数组
        std::cout << n << ' ';
    std::cout << '\n';

    for (int n : a)  
        std::cout << 1 << ' '; // 不必使用循环变量
    std::cout << '\n';

}
```

## lambda 表达式

lambda 表达式即是无名函数，很像java中的临时函数（集各家之所长，比各家难用……）
lambda的语法如下：

```C++
[ 俘获 ] <模板形参>(可选)(C++20) ( 形参 ) 说明符(可选) 异常说明 attr -> ret requires(可选)(C++20) { 函数体 }
[ 俘获 ] ( 形参 ) -> ret { 函数体 }
[ 俘获 ] ( 形参 ) { 函数体 }
[ 俘获 ] { 函数体 }
```

lambda 表达式细节更多，有可能单独写一个博客进行解释说明，如果大家有兴趣的话，可以先看看[zh.cppreference.com](https://zh.cppreference.com/w/cpp/language/lambda)这篇说明。

## Reference

1. [Effective Modern C++](https://item.jd.com/12348026.html)
2. [C++11/14高级编程](https://item.jd.com/11953925.html)
3. [IBM 右值引用与转移语义](https://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/index.html)
4. [cppreference.com 引用声明](https://zh.cppreference.com/w/cpp/language/reference)
5. [cppreference.com auto](https://zh.cppreference.com/w/cpp/language/auto)
6. [C++四种类型转换运算符：static_cast、dynamic_cast、const_cast和reinterpret_cast](http://c.biancheng.net/cpp/biancheng/view/3297.html)
7. [cppreference.com nullptr，指针字面量](https://zh.cppreference.com/w/cpp/language/nullptr)
8. [cppreference.com 特殊成员函数](https://zh.cppreference.com/w/cpp/language/member_functions#.E7.89.B9.E6.AE.8A.E6.88.90.E5.91.98.E5.87.BD.E6.95.B0)
9. [cppreference.com 弃置函数](https://zh.cppreference.com/w/cpp/language/function#.E5.BC.83.E7.BD.AE.E5.87.BD.E6.95.B0)
10. [花括号初始化列表](https://zh.cppreference.com/w/cpp/language/list_initialization)
11. [基于范围的for循环](https://zh.cppreference.com/w/cpp/language/range-for)
12. [lambda 表达式](https://zh.cppreference.com/w/cpp/language/lambda)
