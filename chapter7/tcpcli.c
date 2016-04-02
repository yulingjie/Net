#include <unp.h>
int main(int argc, char *argv[])
{
    int sockfd = Socket(AF_INET,SOCK_STREAM, 0);
    struct sockaddr_in cliaddr;
    cliaddr.sin_port = htons(SERV_PORT);
    cliaddr.sin_family = AF_INET;
    
    Inet_pton(AF_INET, argv[1],&cliaddr.sin_addr.s_addr);
    socklen_t clilen = sizeof(cliaddr);
    Connect(sockfd, (struct sockaddr*) &cliaddr, clilen);

    char buff[1024];
    while(1)
    {
        bzero(buff, 1024);
        scanf("%s", buff);
        Send(sockfd, buff, strlen(buff), 0);

        Read(sockfd, buff, 1024);
        printf("%s", buff); 
    }
    return 0;
}
