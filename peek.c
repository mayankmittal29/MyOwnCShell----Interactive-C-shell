#include "peek.h"
void peek(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir)
{
    char cwd1[4096];
    getcwd(cwd1, sizeof(cwd1));
    char cwd6[4096];
    strcpy(cwd6, homedirofshell);
    if (end == 1) // only peek
    {
        char cwd1[4096];
        getcwd(cwd1, sizeof(cwd1));
        hidden(cwd1);
    }
    else // when end is 2 or 3
    {
        char flag[5];
        strcpy(flag, "\0");
        char pathname[4096];
        strcpy(pathname, "\0");
        for (int d = start + 1; d < end; d++)
        {
            if (strcmp(commandsarray[d], "-a") == 0)
            {
                if (strcmp(flag, "\0") != 0)
                {
                    strcpy(flag, "-al");
                }
                else
                {
                    strcpy(flag, "-a");
                }
            }
            else if (strcmp(commandsarray[d], "-l") == 0)
            {

                if (strcmp(flag, "\0") != 0)
                {
                    strcpy(flag, "-al");
                }
                else
                {
                    strcpy(flag, "-l");
                }
            }
            else if ((strcmp(commandsarray[d], "-al") == 0) || (strcmp(commandsarray[d], "-la") == 0) || (strcmp(commandsarray[d], "-l-a") == 0) || (strcmp(commandsarray[d], "-a-l") == 0))
            {
                strcpy(flag, "-al");
            }
            else if (strcmp(commandsarray[d], ".") == 0)
            {
                strcpy(pathname, ".");
            }
            else if (strcmp(commandsarray[d], "..") == 0)
            {
                strcpy(pathname, "..");
            }
            else if (strcmp(commandsarray[d], "...") == 0)
            {
                strcpy(pathname, "...");
            }
            else if (strcmp(commandsarray[d], "~") == 0)
            {
                strcpy(pathname, "~");
            }
            else if (strcmp(commandsarray[d], "-") == 0)
            {
                strcpy(pathname, "-");
            }
            else
            {
                strcpy(pathname, commandsarray[d]); // actual pathname
            }
        }
        if (strcmp(pathname, ".") == 0)
        {
            if (strcmp(flag, "\0") != 0)
            {
                if (strcmp(flag, "-a") == 0)
                {
                    char cwd1[4096];
                    getcwd(cwd1, sizeof(cwd1));
                    nothidden(cwd1);
                }
                else if (strcmp(flag, "-l") == 0)
                {
                    char cwd1[4096];
                    getcwd(cwd1, sizeof(cwd1));
                    descriptionhidden(cwd1);
                }
                else if (strcmp(flag, "-al") == 0)
                {
                    char cwd1[4096];
                    getcwd(cwd1, sizeof(cwd1));
                    descriptionnothidden(cwd1);
                }
                else
                {
                    char cwd1[4096];
                    getcwd(cwd1, sizeof(cwd1));
                    hidden(cwd1);
                }
            }
        }
        else if ((strcmp(pathname, "..") == 0) || (strcmp(pathname, "...") == 0))
        {
            if (strcmp(flag, "\0") != 0)
            {
                if (strcmp(flag, "-a") == 0)
                {
                    char cwd1[4096];
                    getcwd(cwd1, sizeof(cwd1));
                    char cur[4096];
                    strcpy(cur, cwd1);
                    chdir("..");
                    char cwd2[4096];
                    getcwd(cwd2, sizeof(cwd2));
                    nothidden(cwd2);
                    chdir(cur);
                }
                else if (strcmp(flag, "-l") == 0)
                {
                    char cwd1[4096];
                    getcwd(cwd1, sizeof(cwd1));
                    char cur[4096];
                    strcpy(cur, cwd1);
                    chdir("..");
                    char cwd2[4096];
                    getcwd(cwd2, sizeof(cwd2));
                    descriptionhidden(cwd2);
                    chdir(cur);
                }
                else if (strcmp(flag, "-al") == 0)
                {
                    char cwd1[4096];
                    getcwd(cwd1, sizeof(cwd1));
                    char cur[4096];
                    strcpy(cur, cwd1);
                    chdir("..");
                    char cwd2[4096];
                    getcwd(cwd2, sizeof(cwd2));
                    descriptionnothidden(cwd2);
                    chdir(cur);
                }
            }
            else
            {
                char cwd1[4096];
                getcwd(cwd1, sizeof(cwd1));
                char cur[4096];
                strcpy(cur, cwd1);
                chdir("..");
                char cwd2[4096];
                getcwd(cwd2, sizeof(cwd2));
                hidden(cwd2);
                chdir(cur);
            }
        }
        else if (strcmp(pathname, "-") == 0)
        {
            if (strcmp(flag, "\0") != 0)
            {
                if (strcmp(flag, "-a") == 0)
                {
                    nothidden(prevdir);
                }
                else if (strcmp(flag, "-l") == 0)
                {
                    descriptionhidden(prevdir);
                }
                else if (strcmp(flag, "-al") == 0)
                {
                    descriptionnothidden(prevdir);
                }
            }
            else
            {
                hidden(prevdir);
            }
        }
        else if (strcmp(pathname, "~") == 0)
        {
            if (strcmp(flag, "\0") != 0)
            {
                if (strcmp(flag, "-a") == 0)
                {
                    nothidden(cwd6);
                }
                else if (strcmp(flag, "-l") == 0)
                {
                    descriptionhidden(cwd6);
                }
                else if (strcmp(flag, "-al") == 0)
                {
                    descriptionnothidden(cwd6);
                }
            }
            else
            {
                hidden(cwd6);
            }
        }
        else if (strcmp(pathname, "\0") != 0) // actual pathname
        {
            if (strcmp(flag, "\0") != 0)
            {
                if (strcmp(flag, "-a") == 0)
                {
                    nothidden(pathname);
                }
                else if (strcmp(flag, "-l") == 0)
                {
                    descriptionhidden(pathname);
                }
                else if (strcmp(flag, "-al") == 0)
                {
                    descriptionnothidden(pathname);
                }
            }
            else
            {
                hidden(pathname);
            }
        }
        else if (strcmp(pathname, "\0") == 0)
        {
            if (strcmp(flag, "\0") != 0)
            {
                if (strcmp(flag, "-a") == 0)
                {
                    char cwd5[4096];
                    getcwd(cwd5, sizeof(cwd5));
                    nothidden(cwd5);
                }
                else if (strcmp(flag, "-l") == 0)
                {
                    char cwd5[4096];
                    getcwd(cwd5, sizeof(cwd5));
                    descriptionhidden(cwd5);
                }
                else if (strcmp(flag, "-al") == 0)
                {
                    char cwd5[4096];
                    getcwd(cwd5, sizeof(cwd5));
                    descriptionnothidden(cwd5);
                }
                else
                {
                    char cwd5[4096];
                    getcwd(cwd5, sizeof(cwd5));
                    hidden(cwd5);
                }
            }
        }
    }
    return;
}
