#include <unp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in tcpaddr;    
    bzero(&tcpaddr, sizeof(tcpaddr));
    tcpaddr.sin_port = htons(SERV_PORT);
    tcpaddr.sin_family = AF_INET;
    tcpaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    socklen_t tcplen = sizeof(tcpaddr);
    const int optval = 1;
    Setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR, &optval, sizeof(optval));
    Bind(listenfd, (struct sockaddr*) &tcpaddr, tcplen);
    Listen(listenfd, LISTENQ);

    struct sockaddr_in udpaddr;
    bzero(&udpaddr, sizeof(udpaddr));
    udpaddr.sin_port = htons(SERV_PORT);
    udpaddr.sin_family = AF_INET;
    udpaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t udplen = sizeof(udpaddr);
    int udpfd = Socket(AF_INET, SOCK_DGRAM, 0);
    Bind(udpfd, (struct sockaddr*) &udpaddr, udplen);

    // listen to listenfd and udpfd
    fd_set fds;
    FD_ZERO(&fds);
    int maxfdp1 = 0;

    const int total_fd_numer = 2;
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    int nready = 0; 
    fprintf(stdout, "begin\n");
    for(; ; )
    {
        FD_SET(listenfd, &fds);
        FD_SET(udpfd, &fds);
        maxfdp1 = max(listenfd, udpfd) +1;

        fprintf(stdout, "before select\n");
        if((nready = Select(maxfdp1, &fds, NULL, NULL, NULL)) < 0)
        {
            fprintf(stdout,"select error");
            if(EINTR == errno)
            {
                continue;
            }
            else
            {
                err_sys("select error");
            }
        }
        fprintf(stdout, "before listen\n");
        if(FD_ISSET(listenfd, &fds))
        {
            fprintf(stdout, "tcp is set");
            int sockfd = Accept(listenfd, NULL, NULL);
            pid_t childId;
            if((childId = Fork()) == 0)
            {
 //               Close(udpfd);
                Close(listenfd);
                char buf[1024];
                str_echo(sockfd);
                exit(0);
            }
            Close(sockfd);
            if(--nready <= 0) continue;
        }

        fprintf(stdout, "before udp\n");
        if(FD_ISSET(udpfd, &fds))
        {
            printf("udp is set ");
            char buf[1024];
            clilen = sizeof(cliaddr);
            Recvfrom(udpfd, buf, 1024, 0,(struct sockaddr*)&cliaddr , &clilen);
            Sendto(udpfd,buf, strlen(buf),0, (struct sockaddr* )&cliaddr, clilen);
        }

    }

    return 0;
}
