#include <unp.h>

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        err_msg("usage: udc <filepath>");
    }
    int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0); 
    struct sockaddr_un svraddr;
    bzero(&svraddr, sizeof(struct sockaddr_un));
    svraddr.sun_family = AF_LOCAL;
    memcpy(svraddr.sun_path, argv[1], strlen(argv[1]));
    connect(sockfd, (struct sockaddr*)&svraddr, sizeof(struct sockaddr*));

    char in_buf[MAXLINE];
    while(fgets(in_buf, MAXLINE, stdin) != NULL)
    {
        write(sockfd, in_buf, strlen(in_buf));
        bzero(in_buf, MAXLINE);
        read(sockfd, in_buf, MAXLINE);
        fprintf(stdout, "%s\n", in_buf);
    }
    return 0;
}
