# 线程安全的 hash map 设计

仿照 ConcurrentHashMap 的思路，分段加锁，可以提高性能，减少临界冲突。
