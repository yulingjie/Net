#include <unp.h>

int main(int argc, const char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, "usage: cli <host> <service>\n");
        exit(-1);
    }
    int sockfd = udp_connect(argv[1], argv[2]);
    write(sockfd, "", 1);
    int n = 0;
    char buff[MAXLINE];
    while((n = Read(sockfd, buff, MAXLINE)) > 0)
    {
        printf("%s", buff);
    }
    return 0;
}
