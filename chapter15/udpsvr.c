#include <unp.h>

int main(int argc, const char *argv[])
{

    int sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    unlink(UNIXDG_PATH);
    struct sockaddr_un svraddr;
    bzero(&svraddr, sizeof(svraddr));
    svraddr.sun_family= AF_LOCAL;
    strncpy(svraddr.sun_path, UNIXDG_PATH, sizeof(svraddr.sun_path));
    bind(sockfd, (SA*)&svraddr, sizeof(svraddr));

    struct sockaddr_un cliaddr;
    bzero(&cliaddr, sizeof(struct sockaddr_un));
    socklen_t len = sizeof(struct sockaddr_un);
    char recv_buf[MAXLINE];
    int n = 0;
    while((n = recvfrom(sockfd, recv_buf, MAXLINE,0,(SA*) &cliaddr, &len))>0)
    {
        fprintf(stdout, "recv from client path%s\n", cliaddr.sun_path);
        if(sendto(sockfd, recv_buf, strlen(recv_buf),0, (SA*)&cliaddr, len)<0)
        {
            err_msg("send to error %d", errno);
        }
    }
    return 0;
}
