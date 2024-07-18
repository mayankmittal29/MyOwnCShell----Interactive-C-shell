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
void pastevents_execute(char *position, struct list *head, char *homedirshell, char *prevdir, struct log *top,struct log* acti);
void seek(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir);
void search(char *current_dir, char *searchingword, char *flag, char *homedirofshell, char *prevdir, char *pathstring);
void foreground(char *commandsarray[1024], char *homedirofshell, int no_of_commands, char *prevdir, char *set_of_commands2, struct list *head, struct log *top,struct log* acti);
void proclore(char *commandsarray[1024], int start, int end, char *homedirofshell);
void manpage(char *commandsarray[1024]);
void activities(struct log* acti);
void neonate(char* commandarray[1024]);
void signalsend(char *commandsarray[1024], int start, int end, char *homedirofshell,struct log* top);
int leftarrowfn(char *setofcommands, char *homedirofshell, char *prevdir, struct list *head, struct log *top,struct log* acti)
{
    char setofcommands2[4096];
    strcpy(setofcommands2, setofcommands);
    char *commandsarray4[1024];
    for (int i = 0; i < 1024; i++)
    {
        commandsarray4[i] = (char *)malloc(sizeof(char) * 500);
    }
    char *delimiters4 = " |\t|\n";
    char *token4 = strtok(setofcommands, delimiters4);
    int no_of_commands4 = 0;
    while (token4 != NULL)
    {
        strcpy(commandsarray4[no_of_commands4], token4);
        no_of_commands4++;
        token4 = strtok(NULL, delimiters4);
    }
    char filename[4096];
    char **command = (char **)malloc(sizeof(char *) * 1024); // Store the command tokens before <
    for (int c = 0; c < 1024; c++)
    {
        command[c] = (char *)malloc(sizeof(char) * 200);
    }
    int command_index = 0;
    for (int s = 0; s < no_of_commands4; s++)
    {
        if (strcmp(commandsarray4[s], "<") == 0)
        {
            break;
        }
        strcpy(command[command_index], commandsarray4[s]);
        command_index++;
    }
    command[command_index] = NULL; // Null-terminate the command array
    strcpy(filename, commandsarray4[command_index + 1]);
    int file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        // Child process
        dup2(file_descriptor, STDIN_FILENO);
        close(file_descriptor);
        if (strcmp(command[0], "warp") == 0)
        {
            warp(command, homedirofshell, 0, command_index, prevdir);
            head->front = newnode(setofcommands2, head, homedirofshell);
        }
        else if (strcmp(command[0], "peek") == 0)
        {
            peek(command, homedirofshell, 0, command_index, prevdir);
            head->front = newnode(setofcommands2, head, homedirofshell);
        }
        else if ((strcmp(command[0], "pastevents") == 0) && (command_index == 1))
        {
            pastevents(head);
        }
        else if ((strcmp(command[0], "pastevents") == 0) && (command_index == 2))
        {
            pastevents_purge(head);
        }
        else if ((strcmp(command[0], "pastevents") == 0) && (command_index == 3))
        {
            pastevents_execute(command[2], head, homedirofshell, prevdir, top,acti);
        }
        else if (strcmp(command[0], "seek") == 0)
        {
            seek(command, homedirofshell, 0, command_index, prevdir);
            head->front = newnode(setofcommands2, head, homedirofshell);
        }
        else if (strcmp(command[0], "proclore") == 0)
        {
            proclore(command, 0, command_index, homedirofshell);
            head->front = newnode(setofcommands2, head, homedirofshell);
        }
        else if (strcmp(command[0], "iMan") == 0)
        {
            manpage(command);
            head->front = newnode(setofcommands2, head, homedirofshell);
        }
        else if (strcmp(command[0], "activities") == 0)
        {
            activities(acti);
            head->front = newnode(setofcommands2, head, homedirofshell);
        }
        else if (strcmp(command[0], "ping") == 0)
        {
            signalsend(command,0,command_index,homedirofshell,top);
            head->front = newnode(setofcommands2, head, homedirofshell);
        }
        else if (strcmp(command[0], "neonate") == 0)
        {
            neonate(command);
            head->front = newnode(setofcommands2, head, homedirofshell);
        }
        else
        {
            execvp(command[0], command);
            head->front = newnode(setofcommands2, head, homedirofshell);
            perror("Execvp failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // Parent process
        wait(NULL); // Wait for the child process to finish
    }
    return file_descriptor;
}