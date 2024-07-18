#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
struct log
{
    struct lognode *front;
    struct lognode *rear;
    int count;
};
struct lognode
{
    int pid;
    struct lognode *next;
    char name[4096];
};
void bg(char *commandarray[1024], struct log *acti)
{
    int pid = atoi(commandarray[1]);
    if (kill(pid, SIGCONT) == -1)
    {
        printf("No process found\n");
    }
    return;
}