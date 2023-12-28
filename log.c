#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prompt.h"
#include <time.h>
struct log
{
    struct lognode *front;
    struct lognode *rear;
    int count;
};
struct lognode
{
    int pid;
    char name[4096];
    struct lognode *next;
};
void logofbackground(struct log *top)
{
    // printf("5\n");
    if (top->count == 0)
    {
        return;
    }
    else
    {
        struct lognode *current = top->front;
        while (current != NULL)
        {
            int status;
            pid_t result = waitpid(current->pid, &status, WNOHANG);
            if (result == -1)
            {
                perror("waitpid");
            }
            else if (result > 0)
            {
                // Child process has terminated
                if (WIFSIGNALED(status))
                {
                    printf("Child process with PID %d exited abnormally due to signal %d\n", current->pid, WTERMSIG(status));
                }
                else if (WIFEXITED(status))
                {
                    printf("Child process with PID %d exited normally with status %d\n", current->pid, WEXITSTATUS(status));
                }
                if (current == top->front)
                {
                    struct lognode *a = current;
                    current = current->next;
                    free(a);
                    top->front = current;
                    top->count--;
                    if (top->front == NULL)
                    {
                        top->rear = NULL;
                    }
                }
                else if (current == top->rear)
                {
                    struct lognode *start = top->front;
                    while (start->next != current)
                    {
                        start = start->next;
                    }
                    start->next = NULL;
                    free(current);
                    current==NULL;
                    top->rear = start;
                    top->count--;
                }
                else
                {
                    struct lognode *curr = current->next;
                    struct lognode *start = top->front;
                    while (start->next != current)
                    {
                        start = start->next;
                    }
                    start->next = curr;
                    struct lognode *temp = current;
                    current = current->next;
                    free(temp);
                    top->count--;
                    // printf("%d\n", top->count);
                }
            }
            else
            {
                // Process is still running
                current=current->next;
            }
        }
    }
    return;
}