# 整理下 cpp 中原生的字符串函数

## 常用函数

1. 正序迭代器 iterator begin()、end()
2. 逆序迭代器 reverse_iterator rbegin()、rend()
3. 字符串是否为空 empty()
4. 字符串长度 size()、length()
5. 系统能够存储的最长的长度 max_size()
6. 当前容量 capacity()， 调整 reserve(size)，收缩 capacity shrink_to_fit
7. 清除内容 clear()
8. 插入字符 insert
9. 移除字符 erase 参数是迭代器
10. 追加字符 push_back append operator +=
11. 移除尾部字符 pop_back
12. 比较两个字符串 compare
13. 以什么开头或结尾 starts_with ends_with
14. 替换字符串指定部分 replace
15. 返回子串 substr
16. 复制字符串 copy
17. 调整储存的字符数量 resize
18. 交换内容 swap
19. 查找内容 find rfind
20. 数值转换 stoi stol stoll stoul stoull stof stod stold
21. 数值转换为字符串 to_string

## Reference

1. [cppreference](https://zh.cppreference.com/w/cpp/string)
