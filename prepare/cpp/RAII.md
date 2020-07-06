# RAII(Resource Acquisition Is Initialization) 资源获取就是初始化

是一种风格，资源获取就是初始化，在对象的生命周期对资源进行管理，构造时获取资源，析构时释放资源。

```cpp
void push()
{
    for(; counter.load() < task; counter.fetch_add(1))
    {
        std::unique_lock<mutex> lock(mutex_lock);
        stk.push(counter.load());
        condition.notify_all();
        printf("%s %d push data %d \n", __FUNCTION__, __LINE__, counter.load());
    }
}
```
