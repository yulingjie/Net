#include <unp.h>

int main(int argc, char** argv)
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
    const int BUFF_SIZE =65504;
    char recvBuf[BUFF_SIZE];
    struct sockaddr_in cliaddr;
    bzero(&cliaddr, sizeof(cliaddr));
    socklen_t clilen = sizeof(cliaddr);
    //while(1)
    {
        bzero(recvBuf, BUFF_SIZE);
        int recvSize = Recvfrom(sockfd, recvBuf, BUFF_SIZE, 0,
                (struct sockaddr*)&cliaddr, &clilen);
        //if(recvSize == 0) break;
        char addr[32];
        bzero((char*) addr, 32);
        Inet_ntop(AF_INET,&cliaddr.sin_addr.s_addr, (char*) addr,32);
        printf("serv recvSize %d\n", recvSize);
        printf("serv %s\n", recvBuf); 
        printf("serv recv from cli [IP %s : %d]: %lu\n", addr, ntohs(cliaddr.sin_port) ,strlen(recvBuf));
       // Sendto(sockfd, (const char* ) recvBuf, strlen(recvBuf),
          //      0, (struct sockaddr*)&cliaddr, clilen);
    }
    exit(0);
}
