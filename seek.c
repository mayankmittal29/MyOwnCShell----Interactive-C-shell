#include "seek.h"
int countf = 0;
int countd = 0;
char pathstore[4096];
char store[4096];
int flag2 = 0;
void search(char *current_dir, char *searchingword, char *flag, char *homedirofshell, char *prevdir, char *pathstring)
{
    chdir(current_dir);
    if (strcmp(flag, "-f") == 0)
    {
        DIR *direc = opendir(current_dir);
        struct dirent *item;
        char initial[4096];
        strcpy(initial, pathstring);
        while ((item = readdir(direc)) != NULL)
        {
            if ((strcmp(item->d_name, ".") == 0) || (strcmp(item->d_name, "..") == 0)) // for hidden files
            {
                continue;
            }
            char fullPath[1024];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", current_dir, item->d_name);
            strcat(pathstring, "/");
            strcat(pathstring, item->d_name);
            struct stat info;
            stat(fullPath, &info);
            if (S_ISDIR(info.st_mode))
            {
                // if (strcmp(item->d_name, searchingword) == 0)
                // {
                //     printf(COLOR_BLUE"%s\n"COLOR_RESET, pathstring);
                // }
                search(fullPath, searchingword, flag, homedirofshell, prevdir, pathstring);
                strcpy(pathstring, initial);
            }
            else if (S_ISREG(info.st_mode))
            {
                if ((strncmp(item->d_name, searchingword, strlen(searchingword)) == 0)&&(item->d_name[strlen(searchingword)]=='.' ))
                {
                    printf(COLOR_GREEN "%s\n" COLOR_RESET, pathstring);
                }
                strcpy(pathstring, initial);
            }
        }
    }
    else if (strcmp(flag, "-d") == 0)
    {
        DIR *direc = opendir(current_dir);
        struct dirent *item;
        char initial[4096];
        strcpy(initial, pathstring);
        while ((item = readdir(direc)) != NULL)
        {
            if ((strcmp(item->d_name, ".") == 0) || (strcmp(item->d_name, "..") == 0)) // for hidden files
            {
                continue;
            }
            char fullPath[1024];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", current_dir, item->d_name);
            strcat(pathstring, "/");
            strcat(pathstring, item->d_name);
            struct stat info;
            stat(fullPath, &info);
            if (S_ISDIR(info.st_mode))
            {
                if (strcmp(item->d_name, searchingword) == 0)
                {
                    printf(COLOR_BLUE "%s\n" COLOR_RESET, pathstring);
                }
                search(fullPath, searchingword, flag, homedirofshell, prevdir, pathstring);
            }
            strcpy(pathstring, initial);
        }
    }
    else if (strcmp(flag, "-fe") == 0)
    {
        DIR *direc = opendir(current_dir);
        struct dirent *item;
        char initial[4096];
        strcpy(initial, pathstring);
        while ((item = readdir(direc)) != NULL)
        {
            if ((strcmp(item->d_name, ".") == 0) || (strcmp(item->d_name, "..") == 0)) // for hidden files
            {
                continue;
            }
            char fullPath[1024];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", current_dir, item->d_name);
            strcat(pathstring, "/");
            strcat(pathstring, item->d_name);
            struct stat info;
            stat(fullPath, &info);
            if (S_ISDIR(info.st_mode))
            {
                if (strcmp(item->d_name, searchingword) == 0)
                {
                    countd++;
                }
                search(fullPath, searchingword, flag, homedirofshell, prevdir, pathstring);
                strcpy(pathstring, initial);
            }
            else if (S_ISREG(info.st_mode))
            {
                if ((strncmp(item->d_name, searchingword, strlen(searchingword)) == 0)&&(item->d_name[strlen(searchingword)]=='.' ))
                {
                    // printf(COLOR_GREEN "%s\n" COLOR_RESET, pathstring);
                    countf++;
                    flag2 = 1;
                    strcpy(store, fullPath);
                    strcpy(pathstore, pathstring);
                }
                strcpy(pathstring, initial);
            }
        }
    }
    else if (strcmp(flag, "-de") == 0)
    {
        DIR *direc = opendir(current_dir);
        struct dirent *item;
        char initial[4096];
        strcpy(initial, pathstring);
        while ((item = readdir(direc)) != NULL)
        {
            if ((strcmp(item->d_name, ".") == 0) || (strcmp(item->d_name, "..") == 0)) // for hidden files
            {
                continue;
            }
            char fullPath[1024];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", current_dir, item->d_name);
            strcat(pathstring, "/");
            strcat(pathstring, item->d_name);
            struct stat info;
            stat(fullPath, &info);
            if (S_ISDIR(info.st_mode))
            {
                if (strcmp(item->d_name, searchingword) == 0)
                {
                    countd++;
                    flag2 = 1;
                    strcpy(store, fullPath);
                    strcpy(pathstore, pathstring);
                }
                search(fullPath, searchingword, flag, homedirofshell, prevdir, pathstring);
                strcpy(pathstring, initial);
            }
            else if (S_ISREG(info.st_mode))
            {
                if ((strncmp(item->d_name, searchingword, strlen(searchingword)) == 0)&&(item->d_name[strlen(searchingword)]=='.' ))
                {
                    countf++;
                }
                strcpy(pathstring, initial);
            }
        }
    }
    else if (strcmp(flag, "-e") == 0)
    {
        DIR *direc = opendir(current_dir);
        struct dirent *item;
        char initial[4096];
        strcpy(initial, pathstring);
        while ((item = readdir(direc)) != NULL)
        {
            if ((strcmp(item->d_name, ".") == 0) || (strcmp(item->d_name, "..") == 0)) // for hidden files
            {
                continue;
            }
            char fullPath[1024];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", current_dir, item->d_name);
            strcat(pathstring, "/");
            strcat(pathstring, item->d_name);
            struct stat info;
            stat(fullPath, &info);
            if (S_ISDIR(info.st_mode))
            {
                if (strcmp(item->d_name, searchingword) == 0)
                {
                    strcpy(pathstore, pathstring);
                    countd++;
                    strcpy(store, fullPath);
                }
                search(fullPath, searchingword, flag, homedirofshell, prevdir, pathstring);
                strcpy(pathstring, initial);
            }
            else if (S_ISREG(info.st_mode))
            {
                if ((strncmp(item->d_name, searchingword, strlen(searchingword)) == 0)&&(item->d_name[strlen(searchingword)]=='.' ))
                {
                    countf++;
                    strcpy(store, fullPath);
                    strcpy(pathstore, pathstring);
                }
                strcpy(pathstring, initial);
            }
        }
    }
    else
    {
        DIR *direc = opendir(current_dir);
        struct dirent *item;
        char initial[4096];
        strcpy(initial, pathstring);
        while ((item = readdir(direc)) != NULL)
        {
            if ((strcmp(item->d_name, ".") == 0) || (strcmp(item->d_name, "..") == 0)) // for hidden files
            {
                continue;
            }
            char fullPath[1024];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", current_dir, item->d_name);
            strcat(pathstring, "/");
            strcat(pathstring, item->d_name);
            struct stat info;
            stat(fullPath, &info);
            if (S_ISDIR(info.st_mode))
            {
                if (strcmp(item->d_name, searchingword) == 0)
                {
                    printf(COLOR_BLUE "%s\n" COLOR_RESET, pathstring);
                }
                search(fullPath, searchingword, flag, homedirofshell, prevdir, pathstring);
                strcpy(pathstring, initial);
            }
            else if (S_ISREG(info.st_mode))
            {
                if ((strncmp(item->d_name, searchingword, strlen(searchingword)) == 0)&&(item->d_name[strlen(searchingword)]=='.' ))
                {
                    printf(COLOR_GREEN "%s\n" COLOR_RESET, pathstring);
                }
                strcpy(pathstring, initial);
            }
        }
    }
    return;
}
void seek(char *commandsarray[1024], char *homedirofshell, int start, int end, char *prevdir)
{
    char flag[5];
    strcpy(flag, "\0");
    char dirname[4096];
    strcpy(dirname, "\0");
    char searchname[4096];
    strcpy(searchname, "\0");
    for (int d = start + 1; d < end; d++)
    {
        if (strcmp(commandsarray[d], "-f") == 0)
        {
            if (strcmp(flag, "\0") != 0)
            {
                if (strcmp(flag, "-d") == 0)
                {
                    printf("Invalid flags!\n");
                    return;
                }
                else if (strcmp(flag, "-e") == 0)
                {
                    strcpy(flag, "-fe"); // fe
                }
                else if (strcmp(flag, "-de") == 0)
                {
                    printf("Invalid flags!\n");
                    return;
                }
            }
            else
            {
                strcpy(flag, "-f");
            }
        }
        else if (strcmp(commandsarray[d], "-d") == 0)
        {
            if (strcmp(flag, "\0") != 0)
            {
                if (strcmp(flag, "-f") == 0)
                {
                    printf("Invalid flags!\n");
                    return;
                }
                else if (strcmp(flag, "-e") == 0)
                {
                    strcpy(flag, "-de"); // de
                }
                else if (strcmp(flag, "-fe") == 0)
                {
                    printf("Invalid flags!\n");
                    return;
                }
            }
            else
            {
                strcpy(flag, "-d");
            }
        }
        else if (strcmp(commandsarray[d], "-e") == 0)
        {
            if (strcmp(flag, "\0") != 0)
            {
                if (strcmp(flag, "-f") == 0)
                {
                    strcpy(flag, "-fe");
                }
                else if (strcmp(flag, "-d"))
                {
                    strcpy(flag, "-de");
                }
            }
            else
            {
                strcpy(flag, "-e");
            }
        }
        else if ((strcmp(commandsarray[d], "-f-e") == 0) || (strcmp(commandsarray[d], "-e-f") == 0) || (strcmp(commandsarray[d], "-fe") == 0) || (strcmp(commandsarray[d], "-ef") == 0))
        {
            strcpy(flag, "-fe");
        }
        else if ((strcmp(commandsarray[d], "-d-e") == 0) || (strcmp(commandsarray[d], "-e-d") == 0) || (strcmp(commandsarray[d], "-de") == 0) || (strcmp(commandsarray[d], "-ed") == 0))
        {
            strcpy(flag, "-de");
        }
        else if (((commandsarray[d][0] == '.') && (commandsarray[d][1] == '/')) || ((commandsarray[d][0] == '~') && (commandsarray[d][1] == '/')) || (((commandsarray[d][0] == '.') && (commandsarray[d][1] == '.') && (commandsarray[d][2] == '/'))))
        {
            strcpy(dirname, commandsarray[d]);
        }
        else
        {
            strcpy(searchname, commandsarray[d]);
        }
    }
    if ((dirname[0] == '.') && (dirname[1] == '/')) // search in current directory
    {
        char cwd1[4096];
        char prev2[4096];
        getcwd(cwd1, sizeof(cwd1));
        strcpy(prev2, cwd1);
        strcat(cwd1, "/");
        char folder[4096];
        for (int y = 2; dirname[y] != '\0'; y++)
        {
            folder[y - 2] = dirname[y];
        }
        folder[strlen(dirname) - 2] = '\0';
        strcat(cwd1, folder);
        char pathstring[4096];
        strcpy(pathstring, ".");
        if (opendir(folder))
        {
            search(cwd1, searchname, flag, homedirofshell, prevdir, pathstring);
            if ((strcmp(flag, "-de") != 0) && (strcmp(flag, "-e") != 0))
            {
                chdir(prev2);
            }
            if (strcmp(flag, "-fe") == 0)
            {
                if ((countf == 1) && (countd == 0))
                {
                    printf("%s\n", pathstore);
                    FILE *fp = fopen(store, "r");
                    char buffer[4096];
                    while (fgets(buffer, sizeof(buffer), fp))
                    {
                        printf("%s", buffer);
                    }
                    printf("\n");
                    fclose(fp);
                }
                else
                {
                    printf("No single file or may be same name directory exists!\n");
                }
                flag2 = 0;
                countf = 0;
                countd = 0;
            }
            else if (strcmp(flag, "-de") == 0)
            {
                if ((countf == 0) && (countd == 1))
                {
                    printf("%s/\n", pathstore);
                    chdir(store);
                }
                else
                {
                    printf("No single directory or may be same name file exists!\n");
                    chdir(prev2);
                }
                flag2 = 0;
                countf = 0;
                countd = 0;
            }
            else if (strcmp(flag, "-e") == 0)
            {
                if ((countf == 0) && (countd == 1))
                {
                    printf("%s/\n", pathstore);
                    chdir(store);
                }
                else if ((countf == 1) && (countd == 0))
                {
                    printf("%s\n", pathstore);
                    FILE *fp = fopen(store, "r");
                    char buffer[4096];
                    while (fgets(buffer, sizeof(buffer), fp))
                    {
                        printf("%s", buffer);
                    }
                    printf("\n");
                    fclose(fp);
                    chdir(prev2);
                }
                else
                {
                    printf("No single directory or file with this name\n");
                    chdir(prev2);
                }
                flag2 = 0;
                countf = 0;
                countd = 0;
            }
        }
        else
        {
            printf("No match found!\n");
            chdir(prev2);
        }
    }
    else if ((dirname[0] == '.') && (dirname[1] == '.') && (dirname[2] == '/'))
    {
        char cwd1[4096];
        char prev2[4096];
        getcwd(cwd1, sizeof(cwd1));
        strcpy(prev2, cwd1);
        chdir("..");
        char cwd2[4096];
        getcwd(cwd2, sizeof(cwd2));
        char folder[4096];
        for (int y = 3; dirname[y] != '\0'; y++)
        {
            folder[y - 3] = dirname[y];
        }
        folder[strlen(dirname) - 3] = '\0';
        strcat(cwd2, "/");
        strcat(cwd2, folder);
        char pathstring[4096];
        strcpy(pathstring, ".");
        if (opendir(folder))
        {
            search(cwd2, searchname, flag, homedirofshell, prevdir, pathstring);
            if (strcmp(flag, "-de") != 0)
            {
                chdir(prev2);
            }
            if (strcmp(flag, "-fe") == 0)
            {
                if ((flag2 == 1) && (countf == 1) && (countd == 0))
                {
                    printf("%s\n", pathstore);
                    FILE *fp = fopen(store, "r");
                    char buffer[4096];
                    while (fgets(buffer, sizeof(buffer), fp))
                    {
                        printf("%s", buffer);
                    }
                    printf("\n");
                    fclose(fp);
                }
                else
                {
                    printf("No single file or may be same name directory exists!\n");
                }
                flag2 = 0;
                countf = 0;
                countd = 0;
            }
            else if (strcmp(flag, "-de") == 0)
            {
                if ((countf == 0) && (countd == 1))
                {
                    printf("%s/\n", pathstore);
                    chdir(store);
                }
                else
                {
                    printf("No single directory or may be same name file exists!\n");
                    chdir(prev2);
                }
                flag2 = 0;
                countf = 0;
                countd = 0;
            }
            else if (strcmp(flag, "-e") == 0)
            {
                if ((countf == 0) && (countd == 1))
                {
                    printf("%s/\n", pathstore);
                    chdir(store);
                }
                else if ((countf == 1) && (countd == 0))
                {
                    printf("%s\n", pathstore);
                    FILE *fp = fopen(store, "r");
                    char buffer[4096];
                    while (fgets(buffer, sizeof(buffer), fp))
                    {
                        printf("%s", buffer);
                    }
                    printf("\n");
                    fclose(fp);
                    chdir(prev2);
                }
                else
                {
                    printf("No single directory or file with this name\n");
                    chdir(prev2);
                }
                flag2 = 0;
                countf = 0;
                countd = 0;
            }
        }
        else
        {
            printf("No match found!\n");
            chdir(prev2);
        }
    }
    else if ((dirname[0] == '~') && (dirname[1] == '/'))
    {
        char cwd1[4096];
        char prev2[4096];
        getcwd(cwd1, sizeof(cwd1));
        strcpy(prev2, cwd1);
        chdir(homedirofshell);
        char folder[4096];
        for (int y = 2; dirname[y] != '\0'; y++)
        {
            folder[y - 2] = dirname[y];
        }
        folder[strlen(dirname) - 2] = '\0';
        char cwd3[4096];
        strcpy(cwd3, homedirofshell);
        strcat(cwd3, "/");
        strcat(cwd3, folder);
        char pathstring[4096];
        strcpy(pathstring, ".");
        if (opendir(folder))
        {
            search(cwd3, searchname, flag, homedirofshell, prev2, pathstring);
            if (strcmp(flag, "-de") != 0)
            {
                chdir(prev2);
            }
            if (strcmp(flag, "-fe") == 0)
            {
                if ((flag2 == 1) && (countf == 1) && (countd == 0))
                {
                    printf("%s\n", pathstore);
                    FILE *fp = fopen(store, "r");
                    char buffer[4096];
                    while (fgets(buffer, sizeof(buffer), fp))
                    {
                        printf("%s", buffer);
                    }
                    printf("\n");
                    fclose(fp);
                }
                else
                {
                    printf("No single file or may be same name directory exists!\n");
                }
                flag2 = 0;
                countf = 0;
                countd = 0;
            }
            else if (strcmp(flag, "-de") == 0)
            {
                if ((countf == 0) && (countd == 1))
                {
                    printf("%s/\n", pathstore);
                    chdir(store);
                }
                else
                {
                    printf("No single directory or may be same name file exists!\n");
                    chdir(prev2);
                }
                flag2 = 0;
                countf = 0;
                countd = 0;
            }
            else if (strcmp(flag, "-e") == 0)
            {
                if ((countf == 0) && (countd == 1))
                {
                    printf("%s/\n", pathstore);
                    chdir(store);
                }
                else if ((countf == 1) && (countd == 0))
                {
                    printf("%s\n", pathstore);
                    FILE *fp = fopen(store, "r");
                    char buffer[4096];
                    while (fgets(buffer, sizeof(buffer), fp))
                    {
                        printf("%s", buffer);
                    }
                    printf("\n");
                    fclose(fp);
                    chdir(prev2);
                }
                else
                {
                    printf("No single directory or file with this name\n");
                    chdir(prev2);
                }
                flag2 = 0;
                countf = 0;
                countd = 0;
            }
        }
        else
        {
            printf("No match found!\n");
            chdir(prev2);
        }
    }
    else if (strcmp(dirname, "\0") == 0)
    {
        char cwd1[4096];
        char prev2[4096];
        getcwd(cwd1, sizeof(cwd1));
        strcpy(prev2, cwd1);
        char pathstring[4096];
        strcpy(pathstring, ".");
        search(cwd1, searchname, flag, homedirofshell, prev2, pathstring);
        if (strcmp(flag, "-de") != 0)
        {
            chdir(prev2);
        }
        if (strcmp(flag, "-fe") == 0)
        {
            if ((flag2 == 1) && (countf == 1) && (countd == 0))
            {
                printf("%s\n", pathstore);
                FILE *fp = fopen(store, "r");
                char buffer[4096];
                while (fgets(buffer, sizeof(buffer), fp))
                {
                    printf("%s", buffer);
                }
                printf("\n");
                fclose(fp);
            }
            else
            {
                printf("No single file or may be same name directory exists!\n");
            }
            flag2 = 0;
            countf = 0;
            countd = 0;
        }
        else if (strcmp(flag, "-de") == 0)
        {
            if ((countf == 0) && (countd == 1))
            {
                printf("%s/\n", pathstore);
                chdir(store);
            }
            else
            {
                printf("No single directory or may be same name file exists!\n");
                chdir(prev2);
            }
            flag2 = 0;
            countf = 0;
            countd = 0;
        }
        else if (strcmp(flag, "-e") == 0)
        {
            if ((countf == 0) && (countd == 1))
            {
                printf("%s/\n", pathstore);
                chdir(store);
            }
            else if ((countf == 1) && (countd == 0))
            {
                printf("%s\n", pathstore);
                FILE *fp = fopen(store, "r");
                char buffer[4096];
                while (fgets(buffer, sizeof(buffer), fp))
                {
                    printf("%s", buffer);
                }
                printf("\n");
                fclose(fp);
                chdir(prev2);
            }
            else
            {
                printf("No single directory or file with this name\n");
                chdir(prev2);
            }
            flag2 = 0;
            countf = 0;
            countd = 0;
        }
    }
    return;
}
