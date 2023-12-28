#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
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
// int isForegroundRunning = 0;
// void handleCtrlC(int signal)
// {
//     if (isForegroundRunning)
//     {
//         printf("Foreground process interrupted by Ctrl-C (SIGINT)\n");
//     }
//     else
//     {
//         printf("No foreground process is running to interrupt.\n");
//     }
// }
// void handleCtrlD(int signal)
// {
//     printf("Ctrl-D pressed. Logging out.\n");
//     exit(0); 
// }
// void handleCtrlZ(int signal)
// {
//     if (isForegroundRunning)
//     {
//         printf("Foreground process stopped by Ctrl-Z (SIGTSTP)\n");
//     }
//     else
//     {
//         printf("No foreground process is running to stop.\n");
//     }
// }
void signalsend(char *commandsarray[1024], int start, int end, char *homedirofshell, struct log *head)
{
    // signal(SIGINT, handleCtrlC);
    // signal(SIGQUIT, handleCtrlD); 
    // signal(SIGTSTP, handleCtrlZ);

    // Simulate a foreground process running
    // isForegroundRunning = 1;

    int pid = atoi(commandsarray[1]);
    int signal_number = atoi(commandsarray[2]);
    struct lognode *curr = head->front;
    int flag = 0;
    while (curr != NULL)
    {
        if (curr->pid == pid)
        {
            flag = 1;
            break;
        }
        curr = curr->next;
    }
    if (flag)
    {
        if (signal_number < 0 || signal_number > 31)
        {
            fprintf(stderr, "Invalid signal number. Signal number should be in the range 0-31.\n");
            return;
        }
        int actual_signal = signal_number % 32;
        if (kill(pid, actual_signal) == -1)
        {
            perror("Error");
            fprintf(stderr, "Failed to send signal %d to process with PID: %d\n", actual_signal, pid);
            return;
        }
        printf("Sent signal %d to process with PID: %d\n", actual_signal, pid);
    }
    else
    {
        printf("No such process found\n");
    }
    return;
}