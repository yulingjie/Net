#include <unp.h>
int main(int argc, char **argv)
{
    int    sockfd;
    struct sockaddr_un servaddr, cliaddr;
    sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);
    unlink(UNIXDG_PATH);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXDG_PATH);
    Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));
//    dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));
    char recv_buf[MAXLINE];
    int n = 0;
    socklen_t len = sizeof(cliaddr);
    while((n = recvfrom(sockfd, recv_buf, MAXLINE,0,(SA*) &cliaddr, &len))>0)
    {
        fprintf(stdout, "recv from client path%s\n", cliaddr.sun_path);
        if(sendto(sockfd, recv_buf, strlen(recv_buf),0, (SA*)&cliaddr, len)<0)
        {
            err_msg("send to error %d", errno);
        }
    }

}
