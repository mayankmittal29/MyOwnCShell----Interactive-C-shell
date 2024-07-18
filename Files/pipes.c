#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
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
    struct node *front;
    struct node *rear;
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
void pastevents_execute(char *position, struct list *head, char *homedirshell, char *prevdir, struct log *top, struct log *acti);
void seek(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir);
void search(char *current_dir, char *searchingword, char *flag, char *homedirofshell, char *prevdir, char *pathstring);
void foreground(char *commandsarray[1024], char *homedirofshell, int no_of_commands, char *prevdir, char *set_of_commands2, struct list *head, struct log *top, struct log *acti);
void proclore(char *commandsarray[1024], int start, int end, char *homedirofshell);
void manpage(char *commandsarray[1024]);
int leftarrowfn(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top, struct log *acti);
int rightarrowfn(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top, struct log *acti);
int appendfn(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top, struct log *acti);
void leftright(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top, struct log *acti);
void activities(struct log *acti);
void signalsend(char *commandsarray[1024], int start, int end, char *homedirofshell, struct log *top);
void leftrightright(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top, struct log *acti);
void fg(char *commandarray[1024], struct log *node);
void bg(char *commandarray[1024], struct log *node);
void neonate(char *commandarray[1024]);
void pipesfn(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top, struct log *acti)
{
    char setofcommands2[4096];
    strcpy(setofcommands2, setofcommands);
    char *commandsarray[1024];
    for (int i = 0; i < 1024; i++)
    {
        commandsarray[i] = (char *)malloc(sizeof(char) * 500);
    }
    char *delimiters = "|";
    char *token = strtok(setofcommands, delimiters);
    int num_commands = 0;
    while (token != NULL && num_commands < 1024)
    {
        strcpy(commandsarray[num_commands], token);
        num_commands++;
        token = strtok(NULL, delimiters);
    }
    int pipes[2];
    int f = 0;
    int t = 0;
    int a = dup(0);
    int b = dup(1);
    for (int g = 0; g < num_commands; g++)
    {
        char ab[4096];
        strcpy(ab, commandsarray[g]); // ab -> echo hi
        char *commandsarray4[1024];   // echo and hi
        for (int i = 0; i < 1024; i++)
        {
            commandsarray4[i] = (char *)malloc(sizeof(char) * 500);
        }
        char *delimiters4 = " |\t|\n";
        char *token4 = strtok(commandsarray[g], delimiters4);
        int no_of_commands4 = 0;
        while (token4 != NULL)
        {
            strcpy(commandsarray4[no_of_commands4], token4);
            no_of_commands4++;
            token4 = strtok(NULL, delimiters4);
        }
        commandsarray4[no_of_commands4] = NULL;
        // printf("%s\n", commandsarray4[0]);
        int leftarrow = 0;
        int rightarrow = 0;
        int append = 0;
        for (int h = 0; h < no_of_commands4; h++)
        {
            if (strcmp(commandsarray4[h], "<") == 0)
            {
                leftarrow++;
            }
            if (strcmp(commandsarray4[h], ">") == 0)
            {
                rightarrow++;
            }
            if (strcmp(commandsarray4[h], ">>") == 0)
            {
                append++;
            }
            if (strcmp(commandsarray4[h], "pastevents") == 0)
            {
                f = 1;
            }
        }
        // printf("%d %d %d\n", leftarrow, rightarrow, append);
        if (g < num_commands - 1)
        {
            if (pipe(pipes) == -1)
            {
                perror("Pipe creation failed");
                exit(EXIT_FAILURE);
            }
        }
        // if ((g == 0) && (leftarrow == 1))
        // {
        //     int dec = leftarrowfn(commandsarray[g], homedirofshell, prevdir, head, top, acti);
        //     dup2(dec,STDIN_FILENO);
        //     close(dec);
        //     dup2(pipes[1],STDOUT_FILENO);
        //     close(pipes[1]);
        //     t = pipes[0];
        //     continue;
        // }
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            // if (g == 0)
            // {
            //     dup2(0, 0);
            // }
            if (g > 0)
            {
                dup2(t, STDIN_FILENO);
                close(t);
            }
            if (g < num_commands - 1)
            {
                dup2(pipes[1], STDOUT_FILENO);
                close(pipes[1]);
            }
            else if (g == num_commands - 1)
            {
                if ((leftarrow == 0) && (rightarrow == 0))
                {
                    dup2(STDOUT_FILENO, STDOUT_FILENO);
                }
                else if (rightarrow == 1)
                {
                    int dec = rightarrowfn(ab, homedirofshell, prevdir, head, top, acti);
                    dup2(dec, STDOUT_FILENO);
                    close(dec);
                }
                else if (append == 1)
                {
                    int dec = appendfn(ab, homedirofshell, prevdir, head, top, acti);
                    dup2(dec, STDOUT_FILENO);
                    close(dec);
                }
            }
            if ((leftarrow == 0) && (rightarrow == 0))
            {
                if (strcmp(commandsarray4[0], "warp") == 0)
                {
                    warp(commandsarray4, homedirofshell, 0, no_of_commands4, prevdir);
                }
                else if (strcmp(commandsarray4[0], "peek") == 0)
                {
                    peek(commandsarray4, homedirofshell, 0, no_of_commands4, prevdir);
                }
                else if ((strcmp(commandsarray4[0], "pastevents") == 0) && (no_of_commands4 == 1))
                {
                    pastevents(head);
                }
                else if ((strcmp(commandsarray4[0], "pastevents") == 0) && (no_of_commands4 == 2))
                {
                    pastevents_purge(head);
                }
                else if ((strcmp(commandsarray4[0], "pastevents") == 0) && (no_of_commands4 == 3))
                {
                    pastevents_execute(commandsarray4[2], head, homedirofshell, prevdir, top, acti);
                }
                else if (strcmp(commandsarray4[0], "seek") == 0)
                {
                    seek(commandsarray4, homedirofshell, 0, no_of_commands4, prevdir);
                }
                else if (strcmp(commandsarray4[0], "proclore") == 0)
                {
                    proclore(commandsarray4, 0, no_of_commands4, homedirofshell);
                }
                else if (strcmp(commandsarray4[0], "iMan") == 0)
                {
                    manpage(commandsarray4);
                }
                else if (strcmp(commandsarray4[0], "activities") == 0)
                {
                    activities(acti);
                }
                else if (strcmp(commandsarray4[0], "ping") == 0)
                {
                    signalsend(commandsarray4, 0, no_of_commands4, homedirofshell, top);
                }
                else if (strcmp(commandsarray4[0], "fg") == 0)
                {
                    fg(commandsarray4, acti);
                }
                else if (strcmp(commandsarray4[0], "bg") == 0)
                {
                    bg(commandsarray4, acti);
                }
                else if (strcmp(commandsarray4[0], "neonate") == 0)
                {
                    neonate(commandsarray4);
                }
                else
                {
                    execvp(commandsarray4[0], commandsarray4);
                    perror("Execvp failed");
                    exit(EXIT_FAILURE);
                }
            }
            // else if ((leftarrow == 1) && (rightarrow == 0)) // only left arrow
            // {
            //     leftarrowfn(commandsarray[g], homedirofshell, prevdir, head, top, acti);
            // }
            // else if ((leftarrow == 0) && (rightarrow == 1)) // right arrow only
            // {
            //     int c = rightarrowfn(commandsarray[g], homedirofshell, prevdir, head, top, acti);
            // }
            // else if ((leftarrow == 0) && (rightarrow == 2)) // append only
            // {
            //     appendfn(commandsarray[g], homedirofshell, prevdir, head, top, acti);
            // }
            // else if ((leftarrow == 1) && (rightarrow == 1)) // both left and right arrow
            // {
            //     leftright(commandsarray[g], homedirofshell, prevdir, head, top, acti);
            // }
            // else if ((leftarrow == 1) && (rightarrow == 2)) // both left and right arrow
            // {
            //     leftrightright(commandsarray[g], homedirofshell, prevdir, head, top, acti);
            // }
        }
        else
        {
            wait(NULL);
            close(pipes[1]);
            t = pipes[0];
        }
    }
    dup2(a, 0);
    dup2(b, 1);
    close(a);
    close(b);
    if (f == 0)
    {
        head->front = newnode(setofcommands2, head, homedirofshell);
    }
}
