#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
struct node
{
    char command[4096];
    struct node *next;
};
struct list
{
    int count;
    struct node *front; // holds oldest
    struct node *rear;  // holds newest
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
    struct lognode* next;
    char name[4096];
};
void warp(char *commandsarray[1024], char *cwd, int start, int end, char *prevdir);
void peek(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir);
void pastevents(struct list *head);
void pastevents_purge(struct list *head);
struct node* newnode(char *command, struct list *head,char* homedirofshell);
void pastevents_execute(char* position,struct list* head,char* homedirshell,char* prevdir,struct log* top,struct log* acti);
void seek(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir);
void search(char * current_dir,char* searchingword,char* flag,char* homedirofshell,char* prevdir,char* pathstring);
void proclore(char *commandsarray[1024], int start, int end,char* homedirofshell);
void manpage(char *commandsarray[1024]);
void activities(struct log* top);
void signalsend(char *commandsarray[1024], int start, int end,char* homedirofshell,struct log* top);
void fg(char* commandarray[1024],struct log* acti);
void bg(char* commandarray[1024],struct log* acti);
void neonate(char* commandarray[1024]);