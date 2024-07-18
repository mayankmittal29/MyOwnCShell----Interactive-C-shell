#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
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
void fg(char *commandsarray[1024], struct log *acti)
{
    int pid = atoi(commandsarray[1]);
    // struct lognode *curr = acti->front;
    // int flag = 0;
    // while (curr != NULL)
    // {
    //     if (curr->pid == pid)
    //     {
    //         flag = 1;
    //         break;
    //     }
    //     curr = curr->next;
    // }
    // if (flag)
    // {
    //     int status;
    //     if (waitpid(pid, &status, WUNTRACED) == -1)
    //     {
    //         perror("Error");
    //         fprintf(stderr, "Failed to bring process with PID: %d to foreground.\n", pid);
    //         return;
    //     }
    //     // Check the process state
    //     if (WIFSTOPPED(status))
    //     {
    //         int start = clock(); // Record the start time

    //         // Process is stopped, bring it to the foreground and change state to Running
    //         if (tcsetpgrp(STDIN_FILENO, pid) == -1)
    //         {
    //             perror("Error");
    //             fprintf(stderr, "Failed to set process group.\n");
    //             return;
    //         }
    //         kill(pid, SIGCONT); // Resume the stopped process
    //         printf("Bringing process [%d] to foreground and changing its state to Running.\n", pid);

    //         int end = clock(); // Record the end time
    //         double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    //         // Check if the process ran for more than 2 seconds
    //         if (cpu_time_used > 2.0)
    //         {
    //             printf("Process [%d] ran for %.2f seconds.\n", pid, cpu_time_used);
    //         }
    //     }
    //     else if (WIFEXITED(status))
    //     {
    //         printf("Process [%d] has exited.\n", pid);
    //     }
    // }
    // else
    // {
    //     printf("No such process found.\n");
    // }
    // return;

    // struct lognode *current = acti->front;
    // // printf("%s\n", top->front->name);
    // // printf("%d\n", top->count);
    // if (acti->count == 0)
    // {
    //     printf("No process found\n");
    //     return;
    // }
    // else
    // {
    //     int fl = 0;
    //     while (current != NULL)
    //     {
    //         // printf("5\n");
    //         // printf("%s\n", current->name);
    //         if (current->pid == pid)
    //         {
    //             fl = 1;
    //             char procDirPath[4096];
    //             snprintf(procDirPath, sizeof(procDirPath), "/proc/%d", current->pid);
    //             struct stat dirStat;
    //             if ((stat(procDirPath, &dirStat) == -1) && (!S_ISDIR(dirStat.st_mode)))
    //             {
    //                 // printf("9\n");
    //                 printf("%d : %s - Already Terminated\n", current->pid, current->name);
    //                 // if (current == acti->front)
    //                 // {
    //                 //     struct lognode *a = current;
    //                 //     current = current->next;
    //                 //     free(a);
    //                 //     top->front = current;
    //                 //     top->count--;
    //                 //     if (top->front == NULL)
    //                 //     {
    //                 //         top->rear = NULL;
    //                 //     }
    //                 // }
    //                 // else if (current == top->rear)
    //                 // {
    //                 //     struct lognode *start = top->front;
    //                 //     while (start->next != current)
    //                 //     {
    //                 //         start = start->next;
    //                 //     }
    //                 //     start->next = NULL;
    //                 //     free(current);
    //                 //     current == NULL;
    //                 //     top->rear = start;
    //                 //     top->count--;
    //                 // }
    //                 // else
    //                 // {
    //                 //     struct lognode *curr = current->next;
    //                 //     struct lognode *start = top->front;
    //                 //     while (start->next != current)
    //                 //     {
    //                 //         start = start->next;
    //                 //     }
    //                 //     start->next = curr;
    //                 //     struct lognode *temp = current;
    //                 //     current = current->next;
    //                 //     free(temp);
    //                 //     top->count--;
    //                 //     // printf("%d\n", top->count);
    //                 // }
    //                 break;
    //             }
    //             else
    //             {
    //                 char path[8192];
    //                 snprintf(path, sizeof(path), "/proc/%d/status", current->pid);
    //                 FILE *statusFile = fopen(path, "r");
    //                 if (!statusFile)
    //                 {
    //                     perror("Error opening status file");
    //                     return;
    //                 }
    //                 char line[4096];
    //                 while (fgets(line, sizeof(line), statusFile))
    //                 {
    //                     if (strncmp(line, "State:", 6) == 0)
    //                     {
    //                         char state[32];
    //                         sscanf(line, "State: %s", state);
    //                         if (strcmp(state, "T") == 0)
    //                         {
    //                             char path[4096];
    //                             snprintf(path, sizeof(path), "/proc/%d/stat", pid);

    //                             // Open the stat file
    //                             int fd = open(path, O_RDONLY);
    //                             if (fd == -1)
    //                             {
    //                                 perror("Error opening stat file");
    //                                 exit(EXIT_FAILURE);
    //                             }

    //                             // Read the contents of the stat file
    //                             char statContents[4096];
    //                             ssize_t bytesRead = read(fd, statContents, sizeof(statContents) - 1);
    //                             if (bytesRead == -1)
    //                             {
    //                                 perror("Error reading stat file");
    //                                 close(fd);
    //                                 exit(EXIT_FAILURE);
    //                             }

    //                             // Null-terminate the string
    //                             statContents[bytesRead] = '\0';

    //                             // Close the file descriptor
    //                             close(fd);

    //                             // Tokenize the stat file contents
    //                             char *token = strtok(statContents, " ");
    //                             unsigned long long int startTime = 0;

    //                             // Find the token corresponding to starttime
    //                             int tokenNumber = 1; // Token number for starttime
    //                             while (token != NULL)
    //                             {
    //                                 if (tokenNumber == 22)
    //                                 {
    //                                     startTime = strtoull(token, NULL, 10);
    //                                     break;
    //                                 }
    //                                 token = strtok(NULL, " ");
    //                                 tokenNumber++;
    //                             }
    //                             // printf("%lld\n",startTime/1000);
    //                             // printf("%d : %s - Stopped\n", current->pid, current->name);
    //                             // double start = time(NULL); // Record the start time

    //                             // // Process is stopped, bring it to the foreground and change state to Running
    //                             // if (tcsetpgrp(STDIN_FILENO, pid) == -1)
    //                             // {
    //                             //     perror("Error");
    //                             //     fprintf(stderr, "Failed to set process group.\n");
    //                             //     return;
    //                             // }
    //                             // kill(pid, SIGCONT); // Resume the stopped process
    //                             // printf("Bringing process [%d] to foreground and changing its state to Running.\n", pid);

    //                             // double end = time(NULL); // Record the end time

    //                             // // Check if the process ran for more than 2 seconds
    //                             // if (end - start > 2)
    //                             // {
    //                             //     printf("Process [%d] - %s ran for %.2f seconds.\n", pid, current->name, end - start);
    //                             // }
    //                             char *store[] = {"sh", "-c", current->name, NULL};
    //                             pid_t pid = fork();
    //                             if (pid < 0)
    //                             {
    //                                 perror("Fork failed");
    //                             }
    //                             else if (pid == 0)
    //                             {
    //                                 // Child process
    //                                 execvp("sh", store);
    //                                 perror("Execvp failed");
    //                                 exit(1);
    //                             }
    //                             else
    //                             {
    //                                 // Parent process
    //                                 time_t starttime = time(NULL); // Record start time
    //                                 int status;
    //                                 waitpid(pid, &status, 0);
    //                                 time_t endtime = time(NULL); // Record start time
    //                                 if ((WIFEXITED(status)) && (endtime - starttime-(startTime/1000000) > 2))
    //                                 {
    //                                     printf("%s : %.0lld seconds\n", current->name, endtime - starttime-(startTime/1000000));
    //                                 }
    //                             }
    //                         }
    //                         else if (strcmp(state, "S") == 0)
    //                         {
    //                             printf("%d : %s - Running\n", current->pid, current->name);
    //                         }
    //                         break;
    //                     }
    //                 }
    //                 fclose(statusFile);
    //             }
    //         }
    //         current = current->next;
    //     }
    //     if (fl == 0)
    //     {
    //         printf("No process found\n");
    //     }
    // }
    int fl = 0;
    struct lognode *current = acti->front;
    while (current != NULL)
    {
        if (current->pid == pid)
        {
            fl = 1;
            if (current == acti->front)
            {
                struct lognode *a = current;
                current = current->next;
                free(a);
                acti->front = current;
                acti->count--;
                if (acti->front == NULL)
                {
                    acti->rear = NULL;
                }
            }
            else if (current == acti->rear)
            {
                struct lognode *start = acti->front;
                while (start->next != current)
                {
                    start = start->next;
                }
                start->next = NULL;
                free(current);
                current == NULL;
                acti->rear = start;
                acti->count--;
            }
            else
            {
                struct lognode *curr = current->next;
                struct lognode *start = acti->front;
                while (start->next != current)
                {
                    start = start->next;
                }
                start->next = curr;
                struct lognode *temp = current;
                current = current->next;
                free(temp);
                acti->count--;
                // printf("%d\n", top->count);
            }
            break;
        }
        current = current->next;
    }
    // if (fl == 0)
    // {
    //     printf("No process found\n");
    //     return;
    // }
    // pid_t pd = fork();
    // if (pd == -1)
    // {
    //     printf("fork failed\n");
    // }
    // else if (pd == 0)
    // {

    // if (kill(pid, SIGCONT) == -1)
    // {
    //     printf("No process found\n");
    // }
    // // }
    // // else
    // // {
    // int status;
    // waitpid(pid, &status, 0);
    // // }
    // pid_t g = fork();
    // if (g == -1)
    // {
    //     printf("Fork failed\n");
    // }
    // else if (g == 0)
    // {
        // if (tcsetpgrp(STDIN_FILENO, pid) == -1)
        // {
        //     perror("Error");
        //     fprintf(stderr, "Failed to set process group.\n");
        //     return;
        // }
        // Send a SIGCONT signal to resume the process if it's stopped
        if (kill(pid, SIGCONT) == -1)
        {
            perror("Error");
            fprintf(stderr, "Failed to send SIGCONT signal.\n");
            return;
        }
        int status;
        waitpid(pid,&status,0);
        // // Wait for the process to finish
        // int status;
        // if (waitpid(pid, &status, WUNTRACED) == -1)
        // {
        //     perror("Error");
        //     fprintf(stderr, "Failed to wait for the process.\n");
        //     return;
        // }
        // tcsetpgrp(STDIN_FILENO, getpgrp());
    // }
    // else
    // {
    //     waitpid(pid,0,0);
    // }
    return;
}