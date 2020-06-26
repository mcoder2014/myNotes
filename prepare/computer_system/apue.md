# 一些接口的名称

## 进程控制

```C++
// 退出程序
void exit(int status);  // 正常终止程序，并可调用清理函数
void _Exit(int status); // 立即进入内核
void _exit(int status); // 立即进入内核

int atexit(void (*func) (void));    // 按照登记顺序绑定清理函数，调用顺序相反

// 分配内存空间
void *malloc(size_t size);  // 分配指定字节数的存储区
void *calloc(size_t nobj, size_t size);     // 为指定长度的对象分配存储区并初始化为0
void *realloc(void *ptr, size_t newsize);   // 增加或减少以前分配区的长度

void free(void *ptr);       // 释放 alloc 系列函数申请的空间

// 环境变量
char *getenv(const char *name); // 查找环境变量name=value,返回value
int putenv(char *str);  // 将name=value 放到环境变量中去
int setenv(const char* name, const char* value, int rewrite);   // 设置name为value
int unsetenv(const char *name);     // 删除 name的环境变量

// 创建子进程
pid_t fork(void);   // 创建子进程
pid_t vfork(void);  // 创建一个即将调用 exec 系列函数的子进程

// 获得相关id
pid_t getpid(void);     // 自己进程 id
pid_t getppid(void);    // 父进程 id
uid_t getuid(void);     // 实际用户 id
uid_t geteuid(void);    // 有效用户 id   (程序所有者)
gid_t getgid(void);     // 实际组 id
gid_t getegid(void);    // 有效组 id

// 等待子进程
pid_t wait(int *statloc);   // 等到任意子进程终止状态, 阻塞
pid_t waitpid(pid_t pid, int *statloc, int options);    // 等待指定子进程终止，可以不阻塞

// exec 函数
int execl(const char *pathname, const char *arg0, ... /*(char *) 0 */);
int execv(const char *pathname, char * const argv[]);
int execle(const char *pathname, const char *arg0, ... /* (char *) 0, char *const envp[] */);
int execve(const char *pathname, char * const argv[], char *const envp[]);
int execlp(const char *pathname, const char *arg0, ... /*(char *) 0 */);
int execvp(const char *pathname, char * const argv[]);
int fexecve(int fd, char *const argv[], char *const envp[]);

// 更改用户id 组id
int setuid(uid_t uid);
int setgid(gid_t gid);

// 交换实际用户id 和有效id
int setreuid(uid_t ruid, uid_t euid);
int setregid(gid_t rgid, gid_t egid);

// 更改有效id和有效组id
int seteuid(uid_t uid);
int setegid(gid_t gid);

// 调用系统命令
int system(const char *cmdstring);

// ID获得用户名
char *getlogin(void);

// 信号函数接口
void (*signal(int signo, void (*func)(int)))(int);
int kill(pid_t pid, int signo); // 给指定进程发信号
int raise(int signo);   // 给本进程发信号

unsigned int alarm(unsigned int seconds);   // 定时器, 产生SIGALRM

// 信号集
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signo);
int sigdelset(sigset_t *set, int signo);
int sigismember(const sigset_t *set, int signo);
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);    // 检测和更改信号屏蔽字

void abort(void);   // 给自身发送 SIGABRT 信号
unsigned int sleep(unsigned int seconds);   // 睡眠 秒级精度
int nanosleep(const struct timespec *reqtp, struct timespec *remtp);    // 纳秒级精度

// 多线程
int pthread_equal(pthread_t tid1, pthread_t tid2);  // 两个 pthred_t 是否相等
pthread_t pthread_self(void);
// 创建线程
int pthread_create( pthread_t *restrict tidp,
                    const pthread_attr_t * restrict attr,
                    void *(*start_rtn)(void *),
                    void *restrict arg);
void pthread_exit(void *rval_ptr);  // 退出线程
void pthread_join(pthread_t thread, void **rval_ptr);   // 阻塞线程，等待线程返回
int pthread_cancel(pthread_t tid);  // 请求取消某个线程

// 设置线程退出时调用的清理程序
void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);

// 互斥量 mutex
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

int pthread_mutex_lock(pthread_mutex_t *mutex);     // 不能成功加锁会阻塞
int pthread_mutex_trylock(pthread_mutex_t *mutex);  // 加锁失败不阻塞
int pthread_mutex_unlock(pthread_mutex_t *mutex);   // 解锁

int pthread_mutex_timedlock(pthread_mutex_t * restrict mutex,
                            const struct timespec *restrict tsptr); // 时延锁

// 读写锁 rwlock
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
                        const pthread_rwlockattr_t *restrict attr);
int pthread_rwlock_destroy(pthread_rwlock_t *restrict rwlock);

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_tryrwlock(pthread_rwlock_t *rwlock);

int pthread_rwlock_timedrdlock(pthread_rwlock_t *rwlock,
                                const struct timespec *restrict tsptr);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *rwlock,
                                const struct timespec *restrict tsptr);

// 条件变量 cond
int pthread_cond_init(pthred_cond_t *restrict cond,
                        const pthread_condattr_t *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex *restrict mutex);
int pthread_cond_timedwait(pthread_cond_t *cond,
                            pthread_mutex *restrict mutex,
                            const struct timespec *restrict tsptr);
int pthread_cond_signal(pthread_cond_t * cond);
int pthread_cond_broadcast(pthread_cond_t *cond);

// 自旋锁 spin
int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
int pthread_spin_destroy(pthread_spinlock_t *lock);
int pthread_spin_lock(pthread_spinlock_t *lock);
int pthread_spin_trylock(pthread_spinlock_t *lock);
int pthread_spin_unlock(pthread_spinlock_t *lock);

// 进程间通信 IPC
int pipe(int fd[2]);    // 管道 fd[0] 读 fd[1] 写
FILE *popen(consst char* cmdstring, cosnt char *type);
int pclose(FILE *fd);

// FIFO
int mkfifo(const char *path, mode_t mode);
int mkfifoat(int fd, const char* path, mode_t, mode);

// XSI IPC
key_t ftok(const char *path, int id);

// 消息队列 msg
int msgget(key_t key, int flag);
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
int msgsnd(int msqid, const void *ptr, size_t nbytes, int flag);
ssize_t msgrcv(int msqid, void *ptr, size_t nbytes, long type, int flag);

// 信号量 sem
int semget(key_t key, int nsems, int flag);
int semctl(int semid, int semnum, int cmd, ... /* union semun arg */);
int senop(int semid, strcut sembuf semoparray[], size_t nops);

// shm
int shmget(key_t key, size_t size, ing flag);
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
void *shmat(int shmid, const void *addr, int flag);
int shmdt(const void *addr);

// POSIX 信号量 semaphore
sem_t *sem_open(const char *name, int oflag, ...
                /*mode_t mode, unsigned int value*/);
int sem_close(sem_t *sem);
int sem_unlink(const char *name);
int sem_trywait(sem_t *sem);
int sem_wait(sem_t *sem);
int sem_timedwait(sem_t *restrict sem,
                const strcut timespec *restrict tsptr);
int sem_post(sem_t *sem);
int sem_init(sem_t* sem, int pshared, unsigned int value);
int sem_destroy(sem_t *sem);
int sem_getvalue(sem_t *restrict sem, int *restrict valp);

// socket
int socket(int domain, int type, int protocol);
int shutdown(int sockfd, int how);
int bind(int sockfd, const struct *attr, socklen_t len);
int listen(int sockfd, int backlog);
int connect(int sockfd, const struct sockaddr *addr, socklen_t len);
int accept(int sockfd, struct sockaddr *restrict addr,
           socklen_t* restrict len);
ssize_t send(int sockfd, const void *bud, size_t nbytes, int flags);
ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags);

```
