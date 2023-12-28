#include"manpage.h"
void extractSection(char *html, char *start, char *end)
{
    char *startTag = NULL;
    char *endTag = NULL;
    char sectionStart[200];
    char sectionEnd[200];
    strcpy(sectionStart, start);
    strcpy(sectionEnd, end);
    startTag = strstr(html, start);
    if (startTag)
    {
        endTag = strstr(startTag, end);
        if (endTag)
        {
            while (startTag != endTag)
            {
                putchar(*startTag);
                startTag++;
            }
            putchar('\n');
        }
        else
        {
            printf("Invalid command\n");
        }
    }
    else
    {
        printf("Invalid command\n");
    }
    return;
}
void manpage(char *commandsarray[1024])
{
    char commandname[4096];
    strcpy(commandname, commandsarray[1]);
    char hostname[] = "man.he.net";
    struct hostent *he = gethostbyname(hostname);
    if (he == NULL)
    {
        fprintf(stderr, "Failed to get host by name\n");
        return;
    }
    char path[8192];
    snprintf(path, sizeof(path), "/?section=all&topic=%s&manpath=FreeBSD+12.2-RELEASE+and+Ports", commandname);
    char request[13684];
    snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", path, hostname);
    int socketdesc;
    socketdesc = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);
    connect(socketdesc, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    if (send(socketdesc, request, strlen(request), 0) < 0)
    {
        fprintf(stderr, "Failed to send HTTP request\n");
        close(socketdesc);
        return;
    }
    char response[13684];
    char html[13684];
    memset(response, 0, sizeof(response));
    while (recv(socketdesc, response, sizeof(response) - 1, 0) > 0)
    {
        strcpy(html, response);
        memset(response, 0, sizeof(response));
    }
    // printf("%s\n",html);
    extractSection(html, "NAME\n", "<");
    close(socketdesc);
}
