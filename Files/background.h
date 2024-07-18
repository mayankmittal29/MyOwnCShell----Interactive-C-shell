#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
void background(char *commands[1024], int no_of_commands, char *set_of_commands2, struct log *top,struct log* acti);
void prompt(char *homedirofshell);