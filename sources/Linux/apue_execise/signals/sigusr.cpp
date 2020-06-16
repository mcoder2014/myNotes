#include <iostream>
#include <stdio.h>
#include <apue.h>

static void	sig_usr(int);	/* one handler for both signals */
static void sig_term(int signo);

int
main(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		printf("can't catch SIGUSR1\n");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		printf("can't catch SIGUSR2\n");
    if (signal(SIGTERM, sig_term) == SIG_ERR)
        printf("can't catch SIGTERM\n");
	for ( ; ; )
		pause();
}

static void
sig_term(int signo)
{
    if(signo == SIGTERM)
    {
        printf("Oh! You are a bad guy to kill me!\n");
        printf("I want to count from 1 to 100!\n");

        for(int i = 1; i <= 100; i++ )
            printf("%d\t", i);
        printf("\n");
        printf("Now! I'm dead!\n");
        exit(0);
    }
}

static void
sig_usr(int signo)		/* argument is signal number */
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		printf("received signal %d\n", signo);
}

