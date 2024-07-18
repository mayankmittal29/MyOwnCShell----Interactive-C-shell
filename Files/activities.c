#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
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
void activities(struct log *top)
{
    struct lognode *current = top->front;
    // printf("%s\n", top->front->name);
    // printf("%d\n", top->count);
    if (top->count == 0)
    {
        return;
    }
    else
    {
        while (current != NULL)
        {
            // printf("5\n");
            // printf("%s\n", current->name);
            char procDirPath[4096];
            snprintf(procDirPath, sizeof(procDirPath), "/proc/%d", current->pid);
            struct stat dirStat;
            if ((stat(procDirPath, &dirStat) == -1) && (!S_ISDIR(dirStat.st_mode)))
            {
                // printf("9\n");
                printf("%d : %s - Terminated\n", current->pid, current->name);
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
                    current == NULL;
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
                char path[8192];
                snprintf(path, sizeof(path), "/proc/%d/status", current->pid);
                FILE *statusFile = fopen(path, "r");
                if (!statusFile)
                {
                    perror("Error opening status file");
                    return;
                }
                char line[4096];
                while (fgets(line, sizeof(line), statusFile))
                {
                    if (strncmp(line, "State:", 6) == 0)
                    {
                        char state[32];
                        sscanf(line, "State: %s", state);
                        if (strcmp(state, "T") == 0)
                        {
                            printf("%d : %s - Stopped\n", current->pid, current->name);
                        }
                        else if (strcmp(state, "S") == 0)
                        {
                            printf("%d : %s - Running\n", current->pid, current->name);
                        }
                        break;
                    }
                }
                fclose(statusFile);
                current = current->next;
            }
        }
    }
    return;
}