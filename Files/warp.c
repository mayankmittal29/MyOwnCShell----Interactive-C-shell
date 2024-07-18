#include "warp.h"
void warp(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir)
{
    // printf("%d\n",end);
    if (end == 1)
    {
        printf("%s\n", homedirofshell);
        char cwd4[4096];
        getcwd(cwd4, sizeof(cwd4));
        strcpy(prevdir, cwd4);
        chdir(homedirofshell);
    }
    else
    {
        for (int d = start + 1; d < end; d++)
        {
            // printf("%s\n", commandsarray[d]);
            if (strcmp(commandsarray[d], ".") == 0)
            {
                char cwd2[4096];
                getcwd(cwd2, sizeof(cwd2));
                printf("%s\n", cwd2);
            }
            else if ((commandsarray[d][0] == '~') && (commandsarray[d][1] != '/'))
            {
                printf("%s\n", homedirofshell);
                char cwd4[4096];
                getcwd(cwd4, sizeof(cwd4));
                strcpy(prevdir, cwd4);
                chdir(homedirofshell);
            }
            else if ((strcmp(commandsarray[d], "..") == 0) || (strcmp(commandsarray[d], "...") == 0))
            {
                char cwd5[4096];
                getcwd(cwd5, sizeof(cwd5));
                strcpy(prevdir, cwd5);
                chdir("..");
                char cwd3[4096];
                getcwd(cwd3, sizeof(cwd3));
                printf("%s\n", cwd3);
            }
            else if (strcmp(commandsarray[d], "-") == 0)
            {
                char cwd4[4096];
                char prevdir2[4096];
                getcwd(cwd4, sizeof(cwd4));
                strcpy(prevdir2, cwd4);
                chdir(prevdir);
                printf("%s\n", prevdir);
                strcpy(prevdir, prevdir2);
            }
            else if ((commandsarray[d][0] == '~') && (commandsarray[d][1] == '/'))
            {
                char cwd5[4096];
                getcwd(cwd5, sizeof(cwd5));
                strcpy(prevdir, cwd5);
                chdir(homedirofshell);
                char xy[4096];
                strcpy(xy, homedirofshell);
                strcat(xy, "/");
                char folder[4096];
                for (int f = 2; f < strlen(commandsarray[d]); f++)
                {
                    folder[f - 2] = commandsarray[d][f];
                }
                folder[strlen(commandsarray[d]) - 2] = '\0';
                strcat(xy, folder);
                // printf("%s\n", xy);
                if (opendir(folder))
                {
                    // char cwd8[4096];
                    // strcpy(cwd8, homedirofshell);
                    // strcat(cwd8, "/");
                    // strcat(cwd8, folder);
                    // chdir(cwd8);
                    // printf("%s\n", cwd8);
                    printf("%s\n", xy);
                    chdir(xy);
                }
                else
                {
                    chdir(cwd5);
                    // char cwd6[4096];
                    // getcwd(cwd6, sizeof(cwd6));
                    // printf("%s\n", cwd6);
                    printf("No such file or directory\n");
                }
            }
            else if ((commandsarray[d][0] == '.') && (commandsarray[d][1] == '/'))
            {
                char cwd5[4096];
                getcwd(cwd5, sizeof(cwd5));
                strcpy(prevdir, cwd5);
                char xy[4096];
                strcpy(xy, cwd5);
                strcat(xy, "/");
                char folder[4096];
                for (int f = 2; f < strlen(commandsarray[d]); f++)
                {
                    folder[f - 2] = commandsarray[d][f];
                }
                folder[strlen(commandsarray[d]) - 2] = '\0';
                strcat(xy, folder);
                // printf("%s\n",xy);
                if (opendir(xy))
                {
                    // strcat(cwd5, "/");
                    // strcat(cwd5, folder);
                    chdir(xy);
                    printf("%s\n", xy);
                }
                else
                {
                    // char cwd6[4096];
                    // getcwd(cwd6, sizeof(cwd6));
                    // printf("%s\n", cwd6);
                    printf("No such file or directory\n");
                }
            }
            else if (((commandsarray[d][0] == '.') && (commandsarray[d][1] == '.') && (commandsarray[d][2] == '/')) || ((commandsarray[d][0] == '.') && (commandsarray[d][1] == '.') && (commandsarray[d][2] == '.') && (commandsarray[d][3] == '/')))
            {
                char cwd5[4096];
                getcwd(cwd5, sizeof(cwd5));
                strcpy(prevdir, cwd5);
                chdir("..");
                char folder[4096];
                if (commandsarray[d][2] == '/')
                {
                    for (int f = 3; f < strlen(commandsarray[d]); f++)
                    {
                        folder[f - 3] = commandsarray[d][f];
                    }
                    folder[strlen(commandsarray[d])-3] = '\0';
                }
                else
                {
                    for (int f = 4; f < strlen(commandsarray[d]); f++)
                    {
                        folder[f - 4] = commandsarray[d][f];
                    }
                    folder[strlen(commandsarray[d])-4] = '\0';
                }
                // folder[strlen(commandsarray[d])] = '\0';
                if (opendir(folder))
                {
                    char cwd8[4096];
                    getcwd(cwd8, sizeof(cwd8));
                    strcat(cwd8, "/");
                    strcat(cwd8, folder);
                    chdir(cwd8);
                    printf("%s\n", cwd8);
                }
                else
                {
                    chdir(prevdir);
                    // char cwd6[4096];
                    // getcwd(cwd6, sizeof(cwd6));
                    // printf("%s\n", cwd6);
                    printf("No such file or directory\n");
                }
            }
            else if (commandsarray[d][0] == '/')
            {
                if (opendir(commandsarray[d]))
                {
                    printf("%s\n", commandsarray[d]);
                    chdir(commandsarray[d]);
                }
                else
                {
                    printf("No directory found\n");
                }
            }
            else
            {
                char cwd7[4096];
                getcwd(cwd7, sizeof(cwd7));
                strcpy(prevdir, cwd7);
                // printf("%s\n", cwd7);
                char xy[4096];
                strcpy(xy,cwd7);
                strcat(xy,"/");
                strcat(xy,commandsarray[d]);
                if (opendir(xy))
                {
                    // strcat(cwd7, "/");
                    // strcat(cwd7, commandsarray[d]);
                    // printf("%s\n", cwd7);
                    // chdir(cwd7);
                    // char cwd8[4096];
                    // getcwd(cwd8, sizeof(cwd8));
                    // printf("%s\n",cwd8);
                    // char z[4096];
                    // strcpy(z,cwd7);
                    // strcpy(commandsarray[0],z);
                    // return commandsarray[0];
                    chdir(xy);
                    printf("%s\n",xy);
                }
                else
                {
                    printf("No such file or directory\n");
                }
            }
        }
    }
    return;
}