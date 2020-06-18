# 栈
栈的特点是先进后出“Last in, First out”，栈数据结构的 insert 通常叫做 push ，delete 操作通常叫做 pop。

## 用数组实现栈数据结构
```
STACK-EMPTY(S)
    if S.top == 0
        return TRUE
    else return FALSE

PUSH(S, x)
    S.top = S.top + 1
    S[S.top] = x

POP(S)
    if STACK-EMPTY(S)
        error "underflow"
    else S.top = S.top-1
        return S[S.top + 1]
```