#include <unp.h>

int main(int argc, const char *argv[])
{
    int sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
    struct sockaddr_un svraddr;
    bzero(&svraddr, sizeof(struct sockaddr_un));
    svraddr.sun_family = AF_LOCAL;
    unlink(UNIXSTR_PATH);
    strcpy(svraddr.sun_path, UNIXSTR_PATH);
    bind(sockfd,(struct sockaddr*)&svraddr, sizeof(struct sockaddr*));
    listen(sockfd, 1024);

    struct sockaddr_un cliaddr;
    bzero(&cliaddr, sizeof(struct sockaddr_un));
    socklen_t len = sizeof(struct sockaddr_un);
    int fd= accept(sockfd, (struct sockaddr*)&cliaddr, &len);
    if(fd < 0)
    {
        err_msg("accept errno %d",errno);
    }
    fprintf(stdout, "accept client path%s\n", cliaddr.sun_path);
    int n = 0;
    char rcv_buf[MAXLINE];
    bzero(rcv_buf, MAXLINE);
    while((n = read(fd, rcv_buf, MAXLINE)) >0 )
    {
        write(fd, rcv_buf, strlen(rcv_buf));
    }
    return 0;
}
