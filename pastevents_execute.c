#include "pe.h"

void pastevents_execute(char *position, struct list *head, char *homedirofshell, char *prevdir, struct log *top, struct log *acti)
{
    if ((position[0] - '0') > head->count)
    {
        printf("Command not available\n");
    }
    else
    {
        int block = head->count - (position[0] - '0') + 1;
        struct node *start = head->front;
        int c = 1;
        while (c < block)
        {
            start = start->next;
            c++;
        }
        char set_of_commands[4096];
        strcpy(set_of_commands, start->command);
        char set_of_commands2[4096];
        strcpy(set_of_commands2, set_of_commands);
        // int count = 0;
        // int k = 0;
        // int d = 0;
        // for (int g = 0; commandset[g] != '\0'; g++)
        // {
        //     if ((commandset[g] == ';') || (commandset[g] == '&'))
        //     {
        //         k = 1;
        //         if (commandset[g] == '&')
        //         {
        //             d = 1;
        //         }
        //         break;
        //     }
        // }
        // if (k == 0)
        // {
        //     char *commandsarray[1024];
        //     for (int i = 0; i < 1024; i++)
        //     {
        //         commandsarray[i] = (char *)malloc(sizeof(char) * 500);
        //     }
        //     char *delimiters = " |\t";
        //     char s[4096];
        //     strcpy(s, commandset);
        //     char *token = strtok(commandset, delimiters);
        //     int no_of_commands = 0;
        //     while (token != NULL)
        //     {
        //         strcpy(commandsarray[no_of_commands], token);
        //         no_of_commands++;
        //         token = strtok(NULL, delimiters);
        //     }
        //     if (strcmp(commandsarray[0], "warp") == 0)
        //     {
        //         warp(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
        //         head->front = newnode(commandset2, head);
        //     }
        //     else if (strcmp(commandsarray[0], "peek") == 0)
        //     {
        //         peek(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
        //         head->front = newnode(commandset2, head);
        //     }
        //     else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 1))
        //     {
        //         pastevents(head);
        //     }
        //     else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 2))
        //     {
        //         pastevents_purge(head);
        //     }
        //     else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 3))
        //     {
        //         pastevents_execute(commandsarray[2], head, homedirofshell, prevdir);
        //     }
        //     else if (strcmp(commandsarray[0], "seek") == 0)
        //     {
        //         seek(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
        //         head->front = newnode(commandset2, head);
        //     }
        //     else if (strcmp(commandsarray[0], "proclore") == 0)
        //     {
        //         proclore(commandsarray, 0, no_of_commands);
        //         head->front = newnode(commandset2, head);
        //     }
        //     else
        //     {
        //         head->front = newnode(commandset, head);
        //         char *store[] = {"sh", "-c", s, NULL};
        //         pid_t pid = fork();
        //         if (pid < 0)
        //         {
        //             perror("Fork failed");
        //         }
        //         else if (pid == 0)
        //         {
        //             // Child process
        //             execvp("sh", store);
        //             perror("Execvp failed");
        //             exit(1);
        //         }
        //         else
        //         {
        //             // Parent process
        //             time_t starttime = time(NULL); // Record start time
        //             int status;
        //             waitpid(pid, &status, 0);
        //             time_t endtime = time(NULL); // Record start time
        //             if ((WIFEXITED(status)) && (endtime - starttime > 2))
        //             {
        //                 printf("%s : %.0ld seconds\n", s, endtime - starttime);
        //             }
        //      #endif       // else
        //             // {
        //             //     printf("Foreground process %s exited abnormally\n", set_of_commands2);
        //             // }
        //         }
        //     }
        // }
        // else
        // {
        //     char *commandsarray[1024];
        //     for (int i = 0; i < 1024; i++)
        //     {
        //         commandsarray[i] = (char *)malloc(sizeof(char) * 500);
        //     }
        //     char *delimiters = ";|&";
        //     char *token = strtok(commandset, delimiters);
        //     int no_of_commands = 0;
        //     while (token != NULL)
        //     {
        //         strcpy(commandsarray[no_of_commands], token);
        //         no_of_commands++;
        //         token = strtok(NULL, delimiters);
        //     }
        //     int flag = 0;
        //     for (int s = 0; s < no_of_commands; s++)
        //     {
        //         if (strcmp(commandsarray[s], "pastevents") == 0)
        //         {
        //             flag = 1;
        //             break;
        //         }
        //     }
        //     for (int g = 0; g < no_of_commands; g++)
        //     {
        //         char *commandsarrayset[1024];
        //         for (int i = 0; i < 1024; i++)
        //         {
        //             commandsarrayset[i] = (char *)malloc(sizeof(char) * 500);
        //         }
        //         char *delimiters2 = " |\t";
        //         char *token2 = strtok(commandsarray[g], delimiters2);
        //         int no_of_commands2 = 0;
        //         while (token2 != NULL)
        //         {
        //             strcpy(commandsarrayset[no_of_commands2], token2);
        //             no_of_commands2++;
        //             token2 = strtok(NULL, delimiters2);
        //         }
        //         //     if ((strcmp(commandsarrayset[g], ";") == 0) || (strcmp(commandsarray[g], "&") == 0))
        //         //     {
        //         //         g = 1;
        //         //         if (strcmp(commandsarray[pt], "warp") == 0)
        //         //         {
        //         //             warp(commandsarray, homedirofshell, pt, g, prevdir);
        //         //             pt = g + 1;
        //         //         }
        //         //         else if (strcmp(commandsarray[pt], "peek") == 0)
        //         //         {
        //         //             peek(commandsarray, homedirofshell, pt, g, prevdir);
        //         //             pt = g + 1;
        //         //         }
        //         //         else if (strcmp(commandsarray[pt], "pastevents") == 0)
        //         //         {
        //         //             pastevents(head);
        //         //             pt = g + 1;
        //         //             d = 1;
        //         //         }
        //         //         else if (strcmp(commandsarray[pt], "pastevents purge") == 0)
        //         //         {
        //         //             pastevents_purge(head);
        //         //             pt = g + 1;
        //         //             d = 1;
        //         //         }
        //         //     }
        //         // }
        //         // if ((d == 0) && (g == 1))
        //         // {
        //         //     newnode(set_of_commands, head);
        //         //     head->count++;
        //         // }
        //         if (d == 0)
        //         {
        //             if (strcmp(commandsarrayset[0], "warp") == 0)
        //             {
        //                 warp(commandsarrayset, homedirofshell, 0, no_of_commands2, prevdir);
        //                 // head->front = newnode(set_of_commands2, head);
        //                 // head->count++;
        //             }
        //             else if (strcmp(commandsarrayset[0], "peek") == 0)
        //             {
        //                 peek(commandsarrayset, homedirofshell, 0, no_of_commands2, prevdir);
        //                 // head->front = newnode(set_of_commands2, head);
        //                 // head->count++;
        //             }
        //             else if ((strcmp(commandsarrayset[0], "pastevents") == 0) && (no_of_commands2 == 1))
        //             {
        //                 pastevents(head);
        //             }
        //             else if ((strcmp(commandsarrayset[0], "pastevents") == 0) && (no_of_commands2 == 2))
        //             {
        //                 pastevents_purge(head);
        //             }
        //             else if ((strcmp(commandsarrayset[0], "pastevents") == 0) && (no_of_commands2 == 3))
        //             {
        //                 pastevents_execute(commandsarrayset[2], head, homedirofshell, prevdir);
        //             }
        //         }
        //         else
        //         {
        //             //  &
        //         }
        //     }
        //     if (flag == 0)
        //     {
        //         head->front = newnode(commandset2, head);
        //     }
        // }
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
        if ((k == 0) && (d == 0)) // not in combination
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
            if (strcmp(commandsarray[0], "warp") == 0)
            {
                warp(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
            else if (strcmp(commandsarray[0], "peek") == 0)
            {
                peek(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
            else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 1))
            {
                pastevents(head);
            }
            else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 2))
            {
                pastevents_purge(head);
            }
            else if ((strcmp(commandsarray[0], "pastevents") == 0) && (no_of_commands == 3))
            {
                pastevents_execute(commandsarray[2], head, homedirofshell, prevdir, top, acti);
            }
            else if (strcmp(commandsarray[0], "seek") == 0)
            {
                seek(commandsarray, homedirofshell, 0, no_of_commands, prevdir);
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
            else if (strcmp(commandsarray[0], "proclore") == 0)
            {
                proclore(commandsarray, 0, no_of_commands, homedirofshell);
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
            else if (strcmp(commandsarray[0], "iMan") == 0)
            {
                manpage(commandsarray);
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
            else if (strcmp(commandsarray[0], "activities") == 0)
            {
                activities(acti);
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
            else if (strcmp(commandsarray[0], "ping") == 0)
            {
                signalsend(commandsarray, 0, no_of_commands, homedirofshell, top);
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
            else if (strcmp(commandsarray[0], "fg") == 0)
            {
                fg(commandsarray, acti);
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
            else if (strcmp(commandsarray[0], "bg") == 0)
            {
                fg(commandsarray, acti);
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
            else if (strcmp(commandsarray[0], "neonate") == 0)
            {
                neonate(commandsarray);
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
            else
            {
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
                    execvp("sh", store);
                    perror("Execvp failed");
                    exit(1);
                }
                else
                {
                    // Parent process
                    time_t starttime = time(NULL); // Record start time
                    int status;
                    waitpid(pid, &status, 0);
                    time_t endtime = time(NULL); // Record start time
                    if ((WIFEXITED(status)) && (endtime - starttime > 2))
                    {
                        printf("%s : %.0ld seconds\n", set_of_commands2, endtime - starttime);
                    }
                    // else
                    // {
                    //     printf("Foreground process %s exited abnormally\n", set_of_commands2);
                    // }
                }
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
                    signalsend(commandsarrayset, 0, no_of_commands, homedirofshell, top);
                }
                else if (strcmp(commandsarrayset[0], "fg") == 0)
                {
                    fg(commandsarrayset,acti);
                }
                else if (strcmp(commandsarrayset[0], "bg") == 0)
                {
                    bg(commandsarrayset,acti);
                }
                else if (strcmp(commandsarrayset[0], "neonate") == 0)
                {
                    neonate(commandsarrayset);
                }
                else
                {
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
                        time_t starttime = time(NULL); // Record start time
                        int status;
                        waitpid(pid, &status, 0);
                        time_t endtime = time(NULL); // Record start time
                        if ((WIFEXITED(status)) && (endtime - starttime > 2))
                        {
                            printf("%s : %.0ld seconds\n", commandsarray[g], endtime - starttime);
                        }
                        // else
                        // {
                        //     printf("Foreground process %s exited abnormally\n", commandsarray[g]);
                        // }
                    }
                }
            }
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
            int ampersandback = 0;
            int past = 0;
            for (int h = 0; h < no_of_commands; h++)
            {
                int flag = 0;
                for (int s = strlen(commandsarray[h]) - 1; s >= 0; s--)
                {
                    if (commandsarray[h][s] == '&')
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

                    char last[4096];
                    strcpy(last, commandsarray2[no_of_commands2 - 1]);
                    char *commandsarray3[1024];
                    for (int i = 0; i < 1024; i++)
                    {
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
                        manpage(commandsarray3);
                    }
                    else if (strcmp(commandsarray3[0], "activities") == 0)
                    {
                        activities(acti);
                    }
                    else if (strcmp(commandsarray3[0], "ping") == 0)
                    {
                        signalsend(commandsarray3, 0, no_of_commands, homedirofshell, top);
                    }
                    else if (strcmp(commandsarray3[0], "fg") == 0)
                    {
                        fg(commandsarray3,acti);
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
                            time_t starttime = time(NULL); // Record start time
                            int status;
                            waitpid(pid, &status, 0);
                            time_t endtime = time(NULL); // Record start time
                            if ((WIFEXITED(status)) && (endtime - starttime > 2))
                            {
                                printf("%s : %.0ld seconds\n", last, endtime - starttime);
                            }
                            // else
                            // {
                            //     printf("Foreground process %s exited abnormally\n", last);
                            // }
                        }
                    }
                }
            }
            if (past == 0)
            {
                head->front = newnode(set_of_commands2, head, homedirofshell);
            }
        }
    }
    return;
}