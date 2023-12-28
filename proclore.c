#include "proclore.h"
void subtract_substring_from_start(char *string, const char *substring)
{
    size_t substring_length = strlen(substring);

    if (strncmp(string, substring, substring_length) == 0)
    {
        memmove(string, string + substring_length, strlen(string) - substring_length + 1);
    }
    char a[4096];
    snprintf(a, sizeof(a), "%s%s", "~", string);
    printf("Executable Path: %s\n", a);
}
void printinfo(int pid, char *homedirofshell)
{
    char filepath[MAX_BUFFER_SIZE];
    snprintf(filepath, MAX_BUFFER_SIZE, "/proc/%d/status", pid);
    char ab[4096];
    snprintf(ab,sizeof(ab),"/proc/%d",pid);
    struct stat dirStat;
    if ((stat(ab, &dirStat) == -1) && (!S_ISDIR(dirStat.st_mode)))
    {
        printf("Process Not found\n");
        return;
    }
    FILE *file = fopen(filepath, "r");
    ProcessInfo process;
    // memset(&process, 0, sizeof(ProcessInfo));
    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (sscanf(buffer, "Pid: %d", &process.pid) == 1)
        {
            continue;
        }
        else if (sscanf(buffer, "Tgid: %d", &process.groupid) == 1)
        {
            continue;
        }
        else if (sscanf(buffer, "VmSize: %d", &process.vm) == 1)
        {
            continue;
        }
        else if (sscanf(buffer, "State: %c", &process.status) == 1)
        {
            continue;
        }
    }
    char fg = ' ';
    // if (process.status == 'S')
    // {
    //     fg = '+';
    // }
    printf("Pid: %d\n", process.pid);
    printf("State: %c%c\n", process.status, fg);
    printf("Group id: %d\n", process.groupid);
    printf("Virtual Memory : %d\n", process.vm);
    char exe_path[MAX_BUFFER_SIZE];
    snprintf(exe_path, MAX_BUFFER_SIZE, "/proc/%d/exe", pid);
    char exe_realpath[MAX_BUFFER_SIZE];
    ssize_t len = readlink(exe_path, exe_realpath, sizeof(exe_realpath) - 1);
    int flag = 0;
    if (len != -1)
    {
        exe_realpath[len] = '\0';
    }
    else
    {
        perror("Error reading executable path");
    }
    if (strncmp(exe_realpath, homedirofshell, strlen(homedirofshell)) == 0)
    {
        subtract_substring_from_start(exe_realpath, homedirofshell);
    }
    else
    {
        flag = 1;
    }
    fclose(file);
    // Print the stored information
    if (flag)
    {
        printf("Executable Path: %s\n", exe_realpath);
    }
    return;
}
void proclore(char *commandsarray[1024], int start, int end, char *homedirofshell)
{
    if (end == 1)
    {
        int pid = getpid();
        printinfo(pid, homedirofshell);
    }
    else
    {
        for (int a = start + 1; a < end; a++)
        {
            printinfo(atoi(commandsarray[a]), homedirofshell);
        }
    }
    return;
}