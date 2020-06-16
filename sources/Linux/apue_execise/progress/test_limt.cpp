#include <sys/resource.h>
#include <stdio.h>
#include <iostream>

using namespace std;

static void pr_limits(char *, int);

int main(void)
{

#ifdef RLIMIT_AS
    pr_limits("RLIMIT_AS", RLIMIT_AS);
#endif

#ifdef RLIMIT_MEMLOCK
    pr_limits("RLIMIT_MEMLOCK", RLIMIT_MEMLOCK);
#endif

#ifdef RLIMIT_MSGQUEUE
    pr_limits("RLIMIT_MSGQUEUE", RLIMIT_MSGQUEUE);
#endif

#ifdef RLIMIT_NICE
    pr_limits("RLIMIT_NICE", RLIMIT_NICE);
#endif

#ifdef RLIMIT_NPROC
    pr_limits("RLIMIT_NPROC", RLIMIT_NPROC);
#endif

#ifdef RLIMIT_SIGPENDING
    pr_limits("RLIMIT_SIGPENDING", RLIMIT_SIGPENDING);
#endif

    return 0;
}

static void pr_limits(char *name, int resource)
{
    struct rlimit limit;
    uint64_t lim;

    if(getrlimit(resource, &limit) < 0)
        cerr << "getrlimit error for " << name << endl;
    printf("%-14s", name);

    if(limit.rlim_cur == RLIM_INFINITY)
    {
        printf("(infinite)");
    } else {
        lim = limit.rlim_cur;
        printf("%10lld", lim);
    }
    putchar((int)'\n');
}