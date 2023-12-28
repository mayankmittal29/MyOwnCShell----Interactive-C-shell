#include "headers.h"
struct list *head;
struct log *top;
struct log *acti;
int isForegroundRunning = 0;
int isBackgroundRunning = 0;
int foregroundprocessid = 0;
char homedirofshell[4096];
char display[13869];
int flagdis;
void handleCtrlC(int signal)
{
    if (isForegroundRunning)
    {
        printf("Foreground process interrupted by Ctrl-C (SIGINT)\n");
        isForegroundRunning = 0;
    }
}
int eof_detected = 0;
void handleCtrlD(int signal)
{
    // Handle CTRL-D (EOF) here
    eof_detected = 1;
}
void handleCtrlZ(int signal)
{
    // if (isForegroundRunning)
    // {
    //     printf("Foreground process stopped by Ctrl-Z (SIGTSTP)\n");
    //     isForegroundRunning = 0;
    //     isBackgroundRunning = 1;
    // }
    kill(foregroundprocessid, SIGSTOP);
    kill(foregroundprocessid, SIGTSTP);
    printf("\n");
}
int main()
{
    flagdis = 0;
    int by = 0;
    char prevdir[4096];
    getcwd(homedirofshell, sizeof(homedirofshell));
    strcpy(prevdir, homedirofshell);
    head = (struct list *)malloc(sizeof(struct list));
    head->count = 0;
    head->front = NULL;
    head->rear = NULL;
    top = (struct log *)malloc(sizeof(struct log));
    top->front = NULL;
    top->rear = NULL;
    top->count = 0;
    acti = (struct log *)malloc(sizeof(struct log));
    acti->front = NULL;
    acti->rear = NULL;
    acti->count = 0;
    int pd = getpid();
    signal(SIGINT, handleCtrlC);
    // signal(SIGQUIT, handleCtrlD);
    signal(SIGTSTP, handleCtrlZ);
    while (!eof_detected)
    {
        isForegroundRunning = 0;
        prompt(homedirofshell, display, &flagdis);
        strcpy(display, "\0");
        char set_of_commands[4096];
        // printf("5\n");
        if (fgets(set_of_commands, 4096, stdin) == NULL)
        {
            eof_detected = 1;
            break;
        }
        logofbackground(top);
        set_of_commands[strcspn(set_of_commands, "\n")] = '\0';
        char set_of_commands2[4096];
        strcpy(set_of_commands2, set_of_commands);
        // copy all to pastevents execute
        int count = 0;
        int k = 0;
        int d = 0;
        int s = 0;
        for (int g = 0; set_of_commands[g] != '\0'; g++)
        {
            if (set_of_commands[g] == ';')
            {
                k = 1;
            }
            if (set_of_commands[g] == '&')
            {
                d = 1;
            }
        }
        int leftarrow = 0;
        int rightarrow = 0;
        int pipes = 0;
        for (int h = 0; set_of_commands[h] != '\0'; h++)
        {
            if (set_of_commands[h] == '<')
            {
                leftarrow++;
            }
            else if (set_of_commands[h] == '>')
            {
                rightarrow++;
            }
            else if (set_of_commands[h] == '|')
            {
                pipes++;
            }
        }
        if ((k == 0) && (d == 0)) // not in combination
        {
            if ((leftarrow == 0) && (rightarrow == 0) && (pipes == 0))
            {
                char *commandsarray[1024];
                for (int i = 0; i < 1024; i++)
                {
                    commandsarray[i] = (char *)malloc(sizeof(char) * 500);
                }
                char *delimiters = " |\t|\n";
                char *token = strtok(set_of_commands, delimiters);
                int no_of_commands = 0;
                while (token != NULL)
                {
                    strcpy(commandsarray[no_of_commands], token);
                    no_of_commands++;
                    token = strtok(NULL, delimiters);
                }
                // pid_t ch = fork();
                // if (ch == -1)
                // {
                //     printf("Fork failed\n");
                // }
                // else if (ch == 0)
                // {
                if (strcmp(commandsarray[0], "warp") == 0)
                {
                    isForegroundRunning = 1;
                    // char *abc = (char *)malloc(sizeof(char) * 400);
                    warp(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
                    // chdir(abc);
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                }
                else if (strcmp(commandsarray[0], "peek") == 0)
                {
                    isForegroundRunning = 1;
                    peek(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                }
                else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 1))
                {
                    isForegroundRunning = 1;
                    pastevents(head);
                }
                else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 2))
                {
                    isForegroundRunning = 1;
                    pastevents_purge(head);
                }
                else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 3))
                {
                    isForegroundRunning = 1;
                    pastevents_execute(commandsarray[2], head, homedirofshell, prevdir, top, acti);
                }
                else if (strcmp(commandsarray[0], "seek") == 0)
                {
                    isForegroundRunning = 1;
                    seek(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                }
                else if (strcmp(commandsarray[0], "proclore") == 0)
                {
                    isForegroundRunning = 1;
                    proclore(commandsarray, 0, no_of_commands, homedirofshell);
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                }
                else if (strcmp(commandsarray[0], "iMan") == 0)
                {
                    isForegroundRunning = 1;
                    manpage(commandsarray);
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                }
                else if (strcmp(commandsarray[0], "activities") == 0)
                {
                    isForegroundRunning = 1;
                    activities(acti);
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                }
                else if (strcmp(commandsarray[0], "ping") == 0)
                {
                    isForegroundRunning = 1;
                    signalsend(commandsarray, 0, no_of_commands, homedirofshell, acti);
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                }
                else if (strcmp(commandsarray[0], "fg") == 0)
                {
                    isForegroundRunning = 1;
                    fg(commandsarray, acti);
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                }
                else if (strcmp(commandsarray[0], "bg") == 0)
                {
                    isForegroundRunning = 1;
                    bg(commandsarray, acti);
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                }
                else if (strcmp(commandsarray[0], "neonate") == 0)
                {
                    isForegroundRunning = 1;
                    neonate(commandsarray);
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                }
                else
                {
                    isForegroundRunning = 1;
                    head->front = newnode(set_of_commands2, head, homedirofshell);
                    char *store[] = {"sh", "-c", set_of_commands2, NULL};
                    pid_t pid = fork();
                    if (pid < 0)
                    {
                        perror("Fork failed");
                    }
                    else if (pid == 0)
                    {
                        // Child process
                        // foregroundprocessid=
                        execvp("sh", store);
                        perror("Execvp failed");
                        exit(1);
                    }
                    else
                    {
                        foregroundprocessid = pid;
                        // Parent process
                        time_t starttime = time(NULL); // Record start time
                        int status;
                        // waitpid(pid, &status, 0);
                        int d;
                        waitpid(pid, &d, WUNTRACED);
                        if (WIFSTOPPED(d))
                        {
                            // if (top->front == NULL)
                            // {
                            //     struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
                            //     temp->pid = foregroundprocessid;
                            //     strcpy(temp->name, set_of_commands2);
                            //     // temp->status = execstatus;
                            //     temp->next = NULL;
                            //     top->front = temp;
                            //     top->rear = temp;
                            //     top->count++;
                            // }
                            // else
                            // {
                            //     struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
                            //     temp->pid = foregroundprocessid;
                            //     strcpy(temp->name, set_of_commands2);
                            //     temp->next = NULL;
                            //     top->rear->next = temp;
                            //     top->rear = temp;
                            //     top->count++;
                            // }
                            if (acti->front == NULL)
                            {
                                struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
                                temp->pid = foregroundprocessid;
                                strcpy(temp->name, set_of_commands2);
                                // temp->status = execstatus;
                                temp->next = NULL;
                                acti->front = temp;
                                acti->rear = temp;
                                acti->count++;
                            }
                            else
                            {
                                struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
                                temp->pid = foregroundprocessid;
                                strcpy(temp->name, set_of_commands2);
                                temp->next = NULL;
                                acti->rear->next = temp;
                                acti->rear = temp;
                                acti->count++;
                            }
                            printf("7\n");
                            printf("%s %d\n", acti->front->name, acti->front->pid);
                            continue;
                        }
                        time_t endtime = time(NULL); // Record start time
                        if ((WIFEXITED(status)) && (endtime - starttime > 2))
                        {
                            // printf("%s : %.0ld seconds\n", set_of_commands2, endtime - starttime);
                            // strcpy(display,set_of_commands2);
                            // strcat(display ," :");
                            snprintf(display, sizeof(display), "%s : %lds", set_of_commands2, endtime - starttime);
                            flagdis = 1;
                        }
                        // if(WIFEXITED(d)<0){

                        // }

                        // else
                        // {
                        //     printf("Foreground process %s exited abnormally\n", set_of_commands2);
                        // }
                    }
                }
                // }
                // else
                // {
                //     wait(NULL);
                // }
            }
            else if ((leftarrow == 1) && (rightarrow == 0) && (pipes == 0)) // only left arrow
            {
                leftarrowfn(set_of_commands, homedirofshell, prevdir, head, top, acti);
            }
            else if ((leftarrow == 0) && (rightarrow == 1) && (pipes == 0)) // right arrow only
            {
                rightarrowfn(set_of_commands, homedirofshell, prevdir, head, top, acti);
            }
            else if ((leftarrow == 0) && (rightarrow == 2) && (pipes == 0)) // append only
            {
                appendfn(set_of_commands, homedirofshell, prevdir, head, top, acti);
                eof_detected = 0;
            }
            else if ((leftarrow == 1) && (rightarrow == 1) && (pipes == 0)) // both left and right arrow
            {
                leftright(set_of_commands, homedirofshell, prevdir, head, top, acti);
            }
            else if ((leftarrow == 1) && (rightarrow == 2) && (pipes == 0)) // both left and right right arrow
            {
                leftrightright(set_of_commands, homedirofshell, prevdir, head, top, acti);
            }
            else if (pipes != 0) // | present
            {
                pipesfn(set_of_commands, homedirofshell, prevdir, head, top, acti);
            }
        }
        else if ((k == 1) && (d == 0)) // only ; and not &
        {
            char *commandsarray[1024];
            for (int i = 0; i < 1024; i++)
            {
                commandsarray[i] = (char *)malloc(sizeof(char) * 500);
            }
            char *delimiters = ";";
            char *token = strtok(set_of_commands, delimiters);
            int no_of_commands = 0;
            while (token != NULL)
            {
                strcpy(commandsarray[no_of_commands], token);
                no_of_commands++;
                token = strtok(NULL, delimiters);
            }
            int flag = 0;
            for (int g = 0; g < no_of_commands; g++)
            {
                char *commandsarrayset[1024];
                for (int i = 0; i < 1024; i++)
                {
                    commandsarrayset[i] = (char *)malloc(sizeof(char) * 500);
                }
                char *delimiters2 = " |\t|\n";
                char s[4096];
                strcpy(s, commandsarray[g]);
                char *token2 = strtok(commandsarray[g], delimiters2);
                int no_of_commands2 = 0;
                while (token2 != NULL)
                {
                    strcpy(commandsarrayset[no_of_commands2], token2);
                    no_of_commands2++;
                    token2 = strtok(NULL, delimiters2);
                }
                // pid_t cf = fork();
                // if (cf == -1)
                // {
                //     printf("Fork failed\n");
                // }
                // else if (cf == 0)
                // {
                if (strcmp(commandsarrayset[0], "warp") == 0)
                {
                    warp(commandsarrayset, homedirofshell, 0, no_of_commands2, prevdir);
                    // head->front = newnode(set_of_commands2, head);
                    // head->count++;
                }
                else if (strcmp(commandsarrayset[0], "peek") == 0)
                {
                    peek(commandsarrayset, homedirofshell, 0, no_of_commands2, prevdir);
                    // head->front = newnode(set_of_commands2, head);
                    // head->count++;
                }
                else if ((strcmp(commandsarrayset[0], "pastevents") == 0) && (no_of_commands2 == 1))
                {
                    flag = 1;
                    pastevents(head);
                }
                else if ((strcmp(commandsarrayset[0], "pastevents") == 0) && (no_of_commands2 == 2))
                {
                    flag = 1;
                    pastevents_purge(head);
                }
                else if ((strcmp(commandsarrayset[0], "pastevents") == 0) && (no_of_commands2 == 3))
                {
                    flag = 1;
                    pastevents_execute(commandsarrayset[2], head, homedirofshell, prevdir, top, acti);
                }
                else if (strcmp(commandsarrayset[0], "seek") == 0)
                {
                    seek(commandsarrayset, homedirofshell, 0, no_of_commands2, prevdir);
                }
                else if (strcmp(commandsarrayset[0], "proclore") == 0)
                {
                    proclore(commandsarrayset, 0, no_of_commands2, homedirofshell);
                }
                else if (strcmp(commandsarrayset[0], "iMan") == 0)
                {
                    manpage(commandsarrayset);
                }
                else if (strcmp(commandsarrayset[0], "activities") == 0)
                {
                    activities(acti);
                }
                else if (strcmp(commandsarrayset[0], "ping") == 0)
                {
                    signalsend(commandsarrayset, 0, no_of_commands2, homedirofshell, top);
                }
                else if (strcmp(commandsarrayset[0], "fg") == 0)
                {
                    fg(commandsarrayset, acti);
                }
                else if (strcmp(commandsarrayset[0], "bg") == 0)
                {
                    bg(commandsarrayset, acti);
                }
                else if (strcmp(commandsarrayset[0], "neonate") == 0)
                {
                    neonate(commandsarrayset);
                }
                else
                {
                    isForegroundRunning = 1;
                    char *store[4] = {"sh", "-c", s, NULL};
                    pid_t pid = fork();
                    if (pid < 0)
                    {
                        perror("Fork failed");
                    }
                    else if (pid == 0)
                    {
                        // Child process
                        execvp("sh", store);
                        perror("Execvp failed");
                        exit(1);
                    }
                    else
                    {
                        // Parent process
                        // time_t starttime = time(NULL); // Record start time
                        // int status;
                        // waitpid(pid, &status, 0);
                        // time_t endtime = time(NULL); // Record start time
                        // if ((WIFEXITED(status)) && (endtime - starttime > 2))
                        // {
                        //     printf("%s : %.0ld seconds\n", commandsarray[g], endtime - starttime);
                        // }
                        // // else
                        // // {
                        // //     printf("Foreground process %s exited abnormally\n", commandsarray[g]);
                        // //
                        foregroundprocessid = pid;
                        // Parent process
                        time_t starttime = time(NULL); // Record start time
                        int status;
                        // waitpid(pid, &status, 0);
                        int d;
                        waitpid(pid, &d, WUNTRACED);
                        if (WIFSTOPPED(d))
                        {
                            if (acti->front == NULL)
                            {
                                struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
                                temp->pid = foregroundprocessid;
                                strcpy(temp->name, set_of_commands2);
                                // temp->status = execstatus;
                                temp->next = NULL;
                                acti->front = temp;
                                acti->rear = temp;
                                acti->count++;
                            }
                            else
                            {
                                struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
                                temp->pid = foregroundprocessid;
                                strcpy(temp->name, set_of_commands2);
                                temp->next = NULL;
                                acti->rear->next = temp;
                                acti->rear = temp;
                                acti->count++;
                            }
                            continue;
                        }
                        time_t endtime = time(NULL); // Record start time
                        if ((WIFEXITED(status)) && (endtime - starttime > 2))
                        {
                            // printf("%s : %.0ld seconds\n", set_of_commands2, endtime - starttime);
                            // strcpy(display,set_of_commands2);
                            // strcat(display ," :");
                            snprintf(display, sizeof(display), "%s : %lds", set_of_commands2, endtime - starttime);
                            flagdis = 1;
                        }
                    }
                }
            }
            // }
            // else
            // {
            //     wait(NULL);
            // }
            if (flag == 0)
            {
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
        }
        else // & is also included
        {
            char *commandsarray[1024];
            for (int i = 0; i < 1024; i++)
            {
                commandsarray[i] = (char *)malloc(sizeof(char) * 500);
            }
            char *delimiters = ";";
            char *token = strtok(set_of_commands, delimiters);
            int no_of_commands = 0;
            while (token != NULL)
            {
                strcpy(commandsarray[no_of_commands], token);
                no_of_commands++;
                token = strtok(NULL, delimiters);
            }
            int past = 0;
            for (int h = 0; h < no_of_commands; h++)
            {
                int ampersandback = 0;
                int flag = 0;
                for (int s = strlen(commandsarray[h]) - 1; s >= 0; s--)
                {
                    if ((commandsarray[h][s] == '\n') || (commandsarray[h][s] == ' ') || (commandsarray[h][s] == '\t'))
                    {
                        continue;
                    }
                    else if (commandsarray[h][s] == '&')
                    {
                        ampersandback = 1;
                        break;
                    }
                    else if ((commandsarray[h][s] != '\n') && (commandsarray[h][s] != ' ') && (commandsarray[h][s] != '\t') && (commandsarray[h][s] != '&'))
                    {
                        ampersandback = 0;
                        break;
                    }
                }
                if (ampersandback == 1) // run all in background
                {
                    char *commandsarray2[1024];
                    for (int i = 0; i < 1024; i++)
                    {
                        commandsarray2[i] = (char *)malloc(sizeof(char) * 500);
                    }
                    char *delimiters2 = "&";
                    char *token2 = strtok(commandsarray[h], delimiters2);
                    int no_of_commands2 = 0;
                    while (token2 != NULL)
                    {
                        strcpy(commandsarray2[no_of_commands2], token2);
                        no_of_commands2++;
                        token2 = strtok(NULL, delimiters2);
                    }
                    background(commandsarray2, no_of_commands2, set_of_commands2, top, acti);
                }
                else
                {
                    char *commandsarray2[1024];
                    for (int i = 0; i < 1024; i++)
                    {
                        commandsarray2[i] = (char *)malloc(sizeof(char) * 500);
                    }
                    char *delimiters2 = "&";
                    char *token2 = strtok(commandsarray[h], delimiters2);
                    int no_of_commands2 = 0;
                    while (token2 != NULL)
                    {
                        strcpy(commandsarray2[no_of_commands2], token2);
                        no_of_commands2++;
                        token2 = strtok(NULL, delimiters2);
                    }

                    background(commandsarray2, no_of_commands2 - 1, set_of_commands2, top, acti);
                    // last one is foreground
                    char last[4096];
                    strcpy(last, commandsarray2[no_of_commands2 - 1]);
                    char *commandsarray3[1024];
                    for (int i = 0; i < 1024; i++)
                    {
                        int ampersandback = 0;

                        commandsarray3[i] = (char *)malloc(sizeof(char) * 500);
                    }
                    char *delimiters3 = " |\t|\n";
                    char *token3 = strtok(commandsarray2[no_of_commands2 - 1], delimiters3);
                    int no_of_commands3 = 0;
                    while (token3 != NULL)
                    {
                        strcpy(commandsarray3[no_of_commands3], token3);
                        no_of_commands3++;
                        token3 = strtok(NULL, delimiters3);
                    }
                    // pid_t cv = fork();
                    // if (cv == -1)
                    // {
                    //     printf("Fork Failed\n");
                    // }
                    // else if (cv == 0)
                    // {
                    if (strcmp(commandsarray3[0], "warp") == 0)
                    {
                        warp(commandsarray3, homedirofshell, 0, no_of_commands3, prevdir);
                    }
                    else if (strcmp(commandsarray3[0], "peek") == 0)
                    {
                        peek(commandsarray3, homedirofshell, 0, no_of_commands3, prevdir);
                    }
                    else if ((strcmp(commandsarray3[0], "pastevents") == 0) && (no_of_commands3 == 1))
                    {
                        past = 1;
                        pastevents(head);
                    }
                    else if ((strcmp(commandsarray3[0], "pastevents") == 0) && (no_of_commands3 == 2))
                    {
                        past = 1;
                        pastevents_purge(head);
                    }
                    else if ((strcmp(commandsarray3[0], "pastevents") == 0) && (no_of_commands3 == 3))
                    {
                        past = 1;
                        pastevents_execute(commandsarray3[2], head, homedirofshell, prevdir, top, acti);
                    }
                    else if (strcmp(commandsarray3[0], "seek") == 0)
                    {
                        seek(commandsarray3, homedirofshell, 0, no_of_commands3, prevdir);
                    }
                    else if (strcmp(commandsarray3[0], "proclore") == 0)
                    {
                        proclore(commandsarray3, 0, no_of_commands3, homedirofshell);
                    }
                    else if (strcmp(commandsarray3[0], "iMan") == 0)
                    {
                        printf("%s\n", commandsarray3[1]);
                        manpage(commandsarray3);
                    }
                    else if (strcmp(commandsarray3[0], "activities") == 0)
                    {
                        activities(acti);
                    }
                    else if (strcmp(commandsarray3[0], "ping") == 0)
                    {
                        signalsend(commandsarray3, 0, no_of_commands3, homedirofshell, top);
                    }
                    else if (strcmp(commandsarray3[0], "fg") == 0)
                    {
                        fg(commandsarray3, acti);
                    }
                    else if (strcmp(commandsarray3[0], "bg") == 0)
                    {
                        bg(commandsarray3, acti);
                    }
                    else if (strcmp(commandsarray3[0], "neonate") == 0)
                    {
                        neonate(commandsarray3);
                    }
                    else
                    {
                        char *store[] = {"sh", "-c", last, NULL};
                        pid_t pid = fork();
                        if (pid < 0)
                        {
                            perror("Fork failed");
                        }
                        else if (pid == 0)
                        {
                            // Child process
                            execvp("sh", store);
                            perror("Execvp failed");
                            exit(1);
                        }
                        else
                        {
                            // Parent process
                            // time_t starttime = time(NULL); // Record start time
                            // int status;
                            // waitpid(pid, &status, 0);
                            // time_t endtime = time(NULL); // Record start time
                            // if ((WIFEXITED(status)) && (endtime - starttime > 2))
                            // {
                            //     printf("%s : %.0ld seconds\n", last, endtime - starttime);
                            // }
                            // else
                            // {
                            //     printf("Foreground process %s exited abnormally\n", last);
                            // }
                            foregroundprocessid = pid;
                            // Parent process
                            time_t starttime = time(NULL); // Record start time
                            int status;
                            // waitpid(pid, &status, 0);
                            int d;
                            waitpid(pid, &d, WUNTRACED);
                            if (WIFSTOPPED(d))
                            {
                                if (acti->front == NULL)
                                {
                                    struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
                                    temp->pid = foregroundprocessid;
                                    strcpy(temp->name, set_of_commands2);
                                    // temp->status = execstatus;
                                    temp->next = NULL;
                                    acti->front = temp;
                                    acti->rear = temp;
                                    acti->count++;
                                }
                                else
                                {
                                    struct lognode *temp = (struct lognode *)malloc(sizeof(struct lognode));
                                    temp->pid = foregroundprocessid;
                                    strcpy(temp->name, set_of_commands2);
                                    temp->next = NULL;
                                    acti->rear->next = temp;
                                    acti->rear = temp;
                                    acti->count++;
                                }
                                continue;
                            }
                            time_t endtime = time(NULL); // Record start time
                            if ((WIFEXITED(status)) && (endtime - starttime > 2))
                            {
                                // printf("%s : %.0ld seconds\n", set_of_commands2, endtime - starttime);
                                // strcpy(display,set_of_commands2);
                                // strcat(display ," :");
                                snprintf(display, sizeof(display), "%s : %lds", set_of_commands2, endtime - starttime);
                                flagdis = 1;
                            }
                        }
                    }
                    // }
                    // else
                    // {
                    //     wait(NULL);
                    // }
                }
            }
            if (past == 0)
            {
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
        }
    }

    // if (by)
    // {
    //     exit(0);
    // }
    printf("\n");
    kill(pd, 9);
    return 0;
}
