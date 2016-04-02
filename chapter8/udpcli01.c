#include <unp.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    const int SEND_COUNT = 2000000;
    const int DGLEN = 1400;
    int sockfd;
    sockfd = Socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in  servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1],&servaddr.sin_addr.s_addr);
    
    socklen_t servlen = sizeof(servaddr);
    Connect(sockfd,(struct sockaddr*)&servaddr, servlen);

    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr) ;
    Getsockname(sockfd, (struct sockaddr*) &cliaddr, &clilen);

    printf("socke addr %s\n", Sock_ntop((struct sockaddr *)&cliaddr,clilen) );
    /*char sendBuf[DGLEN];

    for (int i = 0; i < SEND_COUNT; ++i) {
        Sendto(sockfd, sendBuf, DGLEN,0, NULL, 0);
    }
    printf("send finished\n");
    */
    return 0;
}
