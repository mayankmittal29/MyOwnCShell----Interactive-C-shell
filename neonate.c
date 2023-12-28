#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
void die(const char *s)
{
    perror(s);
    exit(1);
}
struct termios orig_termios;
void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}
/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}
/**
 * stdout and stdin are buffered we disable buffering on that
 * After entering in raw mode we read characters one by one
 * Up arrow keys and down arrow keys are represented by 3 byte escape codes
 * starting with ascii number 27 i.e. ESC key
 * This way we interpret arrow keys
 * Tabs are usually handled by the term, but here we are simulating tabs for the sake of simplicity
 * Backspace move the cursor one control character to the left
 * @return
 */
void neonate(char *commandarray[1024])
{
    int timegap = atoi(commandarray[2]);
    setbuf(stdout, NULL);
    enableRawMode();
    int r = 1;
    __pid_t child_pid = fork();
    if (child_pid == -1)
    {
        printf("Fork Failed\n");
    }
    else if (child_pid == 0)
    {
        while (1)
        {
            int fd = open("/proc/sys/kernel/ns_last_pid", O_RDONLY);
            if (fd != -1)
            {
                char buffer[64];
                ssize_t n = read(fd, buffer, sizeof(buffer));
                if (n > 0)
                {
                    buffer[n] = '\0';
                    printf("%s", buffer);
                }
                close(fd);
            }
            sleep(timegap);
        }
    }
    else
    {
        // Parent process
        char c;
        setbuf(stdout, NULL);
        while (1)
        {
            if (read(STDIN_FILENO, &c, 1) == 1)
            {
                if (c == 'x')
                {
                    disableRawMode();
                    kill(child_pid, 9);
                    waitpid(child_pid, NULL, 0);
                    return;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    return;
}