#include <unp.h>
#include <stdio.h>

static int count = 0;
static void recv_key_interrupt(int sign);

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    Bind(sockfd, 
            (struct sockaddr*)& servaddr, 
            sizeof(struct sockaddr_in));
    const int BUFF_SIZE = 1024;
    char recvBuf[BUFF_SIZE];
    struct sockaddr_in cliaddr;
    bzero(&cliaddr, sizeof(cliaddr));
    socklen_t clilen = sizeof(cliaddr);
    Signal(SIGINT, recv_key_interrupt);
    printf("after signal\n");
    while(1)
    {
        bzero(recvBuf, BUFF_SIZE);
        int recvSize = Recvfrom(sockfd, recvBuf, BUFF_SIZE, 0,
                (struct sockaddr*)&cliaddr, &clilen);
        if(recvSize == 0) break;
        ++count;
    }
    return 0;
}
static void recv_key_interrupt(int sign)
{
    printf("recv count %d\n", count);
    exit(0);
}
