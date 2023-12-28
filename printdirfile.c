#include "printdirfile.h"
int compare_strings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}
void hidden(char *directory) // not -a
{
    DIR *direc = opendir(directory);
    struct dirent *item;
    int totalitems = 0;
    while ((item = readdir(direc)) != NULL)
    {
        if (item->d_name[0] != '.')
        {
            totalitems++;
        }
    }
    char **itemname = malloc(sizeof(char *) * totalitems);
    for (int i = 0; i < totalitems; i++)
    {
        itemname[i] = (char *)malloc(sizeof(char) * 1000);
    }
    rewinddir(direc);
    int a = 0;
    while ((item = readdir(direc)) != NULL)
    {
        if (item->d_name[0] != '.')
        {
            strcpy(itemname[a], item->d_name);
            a++;
        }
    }
    qsort(itemname, totalitems, sizeof(char *), compare_strings);
    for (int i = 0; i < totalitems; i++)
    {
        struct stat file_stat;
        if (stat(itemname[i], &file_stat) == 0)
        {
            char color[2];
            strcpy(color, "0");
            if (S_ISDIR(file_stat.st_mode))
            {
                strcpy(color, "1"); // Blue for directories
            }
            else if (file_stat.st_mode & S_IXUSR || file_stat.st_mode & S_IXGRP || file_stat.st_mode & S_IXOTH)
            {
                strcpy(color, "2"); // Green for executables
            }

            if (strcmp(color, "0") == 0)
            {
                printf(COLOR_WHITE "%s\n" COLOR_RESET, itemname[i]);
            }
            else if (strcmp(color, "1") == 0)
            {
                printf(COLOR_BLUE "%s\n" COLOR_RESET, itemname[i]);
            }
            else if (strcmp(color, "2") == 0)
            {
                printf(COLOR_GREEN "%s\n" COLOR_RESET, itemname[i]);
            }
        }

        free(itemname[i]);
    }

    free(itemname);
    closedir(direc);
}
void nothidden(char *directory) // -a
{
    DIR *direc = opendir(directory);
    struct dirent *item;
    int totalitems = 0;
    while ((item = readdir(direc)) != NULL)
    {
        totalitems++;
    }
    char **itemname = malloc(sizeof(char *) * totalitems);
    for (int i = 0; i < totalitems; i++)
    {
        itemname[i] = (char *)malloc(sizeof(char) * 1000);
    }
    rewinddir(direc);
    int a = 0;
    while ((item = readdir(direc)) != NULL)
    {
        strcpy(itemname[a], item->d_name);
        a++;
    }
    qsort(itemname, totalitems, sizeof(char *), compare_strings);
    for (int i = 0; i < totalitems; i++)
    {
        struct stat file_stat;
        if (stat(itemname[i], &file_stat) == 0)
        {
            char color[2];
            strcpy(color, "0");
            if (S_ISDIR(file_stat.st_mode))
            {
                strcpy(color, "1"); // Blue for directories
            }
            else if (file_stat.st_mode & S_IXUSR || file_stat.st_mode & S_IXGRP || file_stat.st_mode & S_IXOTH)
            {
                strcpy(color, "2"); // Green for executables
            }

            if (strcmp(color, "0") == 0)
            {
                printf(COLOR_WHITE "%s\n" COLOR_RESET, itemname[i]);
            }
            else if (strcmp(color, "1") == 0)
            {
                printf(COLOR_BLUE "%s\n" COLOR_RESET, itemname[i]);
            }
            else if (strcmp(color, "2") == 0)
            {
                printf(COLOR_GREEN "%s\n" COLOR_RESET, itemname[i]);
            }
        }

        free(itemname[i]);
    }

    free(itemname);
    closedir(direc);
}
void descriptionhidden(char *directory) // -l
{
    DIR *direc = opendir(directory);
    struct dirent *item;
    int totalitems = 0;
    while ((item = readdir(direc)) != NULL)
    {
        if (item->d_name[0] != '.')
        {
            totalitems++;
        }
    }
    char **itemname = malloc(sizeof(char *) * totalitems);
    for (int i = 0; i < totalitems; i++)
    {
        itemname[i] = (char *)malloc(sizeof(char) * 1000);
    }
    rewinddir(direc);
    int a = 0;
    while ((item = readdir(direc)) != NULL)
    {
        if (item->d_name[0] != '.')
        {
            strcpy(itemname[a], item->d_name);
            a++;
        }
    }
    qsort(itemname, totalitems, sizeof(char *), compare_strings);
    for (int i = 0; i < totalitems; i++)
    {
        struct stat file_stat;
        if (stat(itemname[i], &file_stat) == 0)
        {
            struct passwd *pw = getpwuid(file_stat.st_uid);
            struct group *gr = getgrgid(file_stat.st_gid);
            char moditime[80];
            strftime(moditime, sizeof(moditime), "%b %d %H:%M", localtime(&file_stat.st_mtime));

            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
            printf(" %2ld ", file_stat.st_nlink);
            printf("%-8s ", pw ? pw->pw_name : "");
            printf("%-8s ", gr ? gr->gr_name : "");
            printf("%6ld ", (long)file_stat.st_size);
            printf("%s ", moditime);
            char color[2];
            strcpy(color, "0");
            if (S_ISDIR(file_stat.st_mode))
            {
                strcpy(color, "1"); // Blue for directories
            }
            else if (file_stat.st_mode & S_IXUSR || file_stat.st_mode & S_IXGRP || file_stat.st_mode & S_IXOTH)
            {
                strcpy(color, "2"); // Green for executables
            }
            if (strcmp(color, "0") == 0)
            {
                printf(COLOR_WHITE "%s\n" COLOR_RESET, itemname[i]);
            }
            else if (strcmp(color, "1") == 0)
            {
                printf(COLOR_BLUE "%s\n" COLOR_RESET, itemname[i]);
            }
            else if (strcmp(color, "2") == 0)
            {
                printf(COLOR_GREEN "%s\n" COLOR_RESET, itemname[i]);
            }
        }
    }
    closedir(direc);
    return;
}
void descriptionnothidden(char *directory) // -al
{
    DIR *direc = opendir(directory);
    struct dirent *item;
    int totalitems = 0;
    while ((item = readdir(direc)) != NULL)
    {
        totalitems++;
    }
    char **itemname = malloc(sizeof(char *) * totalitems);
    for (int i = 0; i < totalitems; i++)
    {
        itemname[i] = (char *)malloc(sizeof(char) * 1000);
    }
    rewinddir(direc);
    int a = 0;
    while ((item = readdir(direc)) != NULL)
    {
        strcpy(itemname[a], item->d_name);
        a++;
    }
    qsort(itemname, totalitems, sizeof(char *), compare_strings);
    for (int i = 0; i < totalitems; i++)
    {
        struct stat file_stat;
        if (stat(itemname[i], &file_stat) == 0)
        {
            struct passwd *pw = getpwuid(file_stat.st_uid);
            struct group *gr = getgrgid(file_stat.st_gid);
            char moditime[80];
            strftime(moditime, sizeof(moditime), "%b %d %H:%M", localtime(&file_stat.st_mtime));

            printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
            printf(" %2ld ", file_stat.st_nlink);
            printf("%-8s ", pw ? pw->pw_name : "");
            printf("%-8s ", gr ? gr->gr_name : "");
            printf("%6ld ", (long)file_stat.st_size);
            printf("%s ", moditime);
            char color[2];
            strcpy(color, "0");
            if (S_ISDIR(file_stat.st_mode))
            {
                strcpy(color, "1"); // Blue for directories
            }
            else if (file_stat.st_mode & S_IXUSR || file_stat.st_mode & S_IXGRP || file_stat.st_mode & S_IXOTH)
            {
                strcpy(color, "2"); // Green for executables
            }
            if (strcmp(color, "0") == 0)
            {
                printf(COLOR_WHITE "%s\n" COLOR_RESET, itemname[i]);
            }
            else if (strcmp(color, "1") == 0)
            {
                printf(COLOR_BLUE "%s\n" COLOR_RESET, itemname[i]);
            }
            else if (strcmp(color, "2") == 0)
            {
                printf(COLOR_GREEN "%s\n" COLOR_RESET, itemname[i]);
            }
        }
    }
    closedir(direc);
    return;
}