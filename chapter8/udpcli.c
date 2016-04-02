#include<unp.h>

int main(int argc,char** argv)
{
    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // use standard echo server
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr);
    socklen_t servlen = sizeof(servaddr);
    const int BUFF_SIZE = 65503;
    char recvBuf[BUFF_SIZE];
    memset(recvBuf, (int)'a', BUFF_SIZE);
    struct sockaddr_in* precvaddr = Malloc(servlen);
    socklen_t recvlen;
    Connect(sockfd,(struct sockaddr*)&servaddr, servlen);
    
    //while(1)
    {
      //  int result = scanf("%s", (char*)recvBuf);
      
        Write(sockfd, recvBuf, BUFF_SIZE 
                );
        char addr[32];
        bzero((char*) addr, 32);
        Inet_ntop(AF_INET, & servaddr.sin_addr.s_addr,(char*) addr, 32);
        
        printf("cli sendto serv [IP %s, port %d]: %s\n",
               addr, ntohs(servaddr.sin_port), recvBuf);
        
        bzero(recvBuf, BUFF_SIZE);
        int result = Read(sockfd, recvBuf, BUFF_SIZE
               );
        printf("recv result %d", result);
        //printf("cli recvfrom serv [IP %s, port %d]: %s\n",
        //        addr, ntohs(servaddr.sin_port), recvBuf );
    }
    free(precvaddr);
    return 0;
}
