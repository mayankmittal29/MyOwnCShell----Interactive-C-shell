#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prompt.h"
#include <time.h>
struct node
{
    char command[4096];
    struct node *next;
};
struct list
{
    int count;
    struct node *front;
    struct node *rear;
};
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
void warp(char *commandsarray[1024], char *cwd, int start, int end, char *prevdir);
void peek(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir);
void pastevents(struct list *head);
void pastevents_purge(struct list *head);
struct node *newnode(char *command, struct list *head, char *homedirofshell);
void pastevents_execute(char *position, struct list *head, char *homedirshell, char *prevdir, struct log *top,struct log* acti);
void seek(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir);
void search(char *current_dir, char *searchingword, char *flag, char *homedirofshell, char *prevdir, char *pathstring);
void foreground(char *commandsarray[1024], char *homedirofshell, int no_of_commands, char *prevdir, char *set_of_commands2, struct list *head, struct log *top,struct log* acti);
void proclore(char *commandsarray[1024], int start, int end, char *homedirofshell);
void manpage(char *commandsarray[1024]);
void printinfo(int pid, char *homedirofshell);
void background(char *commands[1024], int no_of_commands, char *set_of_commands2, struct log *top,struct log* acti);
void logofbackground(struct log *top);
void leftarrowfn(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top,struct log* acti);
void rightarrowfn(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top,struct log* acti);
void appendfn(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top,struct log* acti);
void leftright(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top,struct log* acti);
void pipesfn(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top,struct log* acti);
void activities(struct log *acti);
void leftrightright(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top,struct log* acti);
void manpage(char *commandsarray[1024]);
void signalsend(char *commandsarray[1024], int start, int end, char *homedirofshell, struct log *top);
void fg(char* commandarray[1024],struct log* node);
void bg(char* commandarray[1024],struct log* node);
void neonate(char* commandarray[1024]);
