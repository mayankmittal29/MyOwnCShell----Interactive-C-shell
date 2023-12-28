#include "background.h"
void change(int pid, struct log *top, char *commandname,struct log* acti)
{
    // int status;
    // int execstatus;
    // while (waitpid(pid, &status, WNOHANG) > 0)
    // {
    // int a = waitpid(pid, &status, WNOHANG);
    // if (a > 0)
    // {
    // execstatus = WIFEXITED(status);
    if (top->front == NULL)
    {
        struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
        temp->pid = pid;
        strcpy(temp->name, commandname);
        // temp->status = execstatus;
        temp->next = NULL;
        top->front = temp;
        top->rear = temp;
        top->count++;
    }
    else
    {
        struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
        temp->pid = pid;
        strcpy(temp->name, commandname);
        temp->next = NULL;
        top->rear->next = temp;
        top->rear = temp;
        top->count++;
    }
    if (acti->front == NULL)
    {
        struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
        temp->pid = pid;
        strcpy(temp->name, commandname);
        // temp->status = execstatus;
        temp->next = NULL;
        acti->front = temp;
        acti->rear = temp;
        acti->count++;
    }
    else
    {
        struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
        temp->pid = pid;
        strcpy(temp->name, commandname);
        temp->next = NULL;
        acti->rear->next = temp;
        acti->rear = temp;
        acti->count++;
    }
    return;
}

void background(char *commands[1024], int no_of_commands, char *set_of_command2, struct log *top,struct log* acti)
{
    for (int i = 0; i < no_of_commands; i++)
    {
        // signal(SIGCHLD, sigchld_handler); // Register SIGCHLD handler
        int a = 0;
        // char *store[] = {"sh", "-c", commands[i], NULL};
        char store[4096];
        strcpy(store,commands[i]);
        char *commandsd[1024];
        for (int i = 0; i < 1024; i++)
        {
            commandsd[i] = (char *)malloc(sizeof(char) * 500);
        }
        char *delimiters4 = " |\t|\n";
        char *token4 = strtok(commands[i], delimiters4);
        int no = 0;
        while (token4 != NULL)
        {
            strcpy(commandsd[no], token4);
            no++;
            token4 = strtok(NULL, delimiters4);
        }
        commandsd[no] = NULL;
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("Fork failed");
        }
        else if (pid == 0)
        {
            // Child process
            setpgid(0,0);
            execvp(commandsd[0], commandsd);
            perror("Execvp failed");
            exit(1);
        }
        else
        {
            // Parent process
            printf("%d\n", pid);
            a = pid;
            change(a, top, store,acti);
        }
    }
    return;
}