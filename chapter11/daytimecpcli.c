#include <unp.h>

int main(int argc, char *argv[])
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if(argc != 2)
        fprintf(stderr,"usage: a.out <IPaddreee>");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        fprintf(stderr, "socket error\n");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    
    if(inet_pton(AF_INET, argv[1],&servaddr.sin_addr) <=0)
        fprintf(stderr,"inet_pton error for %s", argv[1]);
    
    if(connect(sockfd, (SA*) &servaddr, sizeof(servaddr))< 0)
    {
        fprintf(stderr, "connect_error, errno %d", errno);
    }
    while((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if(fputs(recvline,stdout) == EOF)
            fprintf(stderr,"fputs errpr");
    }

    if(n < 0)
        fprintf(stderr,"read error");
    exit(0);
}
