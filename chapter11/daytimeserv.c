#include<unp.h>

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        fprintf(stderr, 
                "usage: daytimeserv <host> <service>\n");
        exit(-1);
    }
    struct sockaddr_storage cliaddr;
    int listenfd = tcp_listen(argv[1], argv[2],NULL);
    
    socklen_t len;
    int connfd ;
    time_t ticks;
    char buff[MAXLINE];
    for(; ; )
    {
        len = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA*) &cliaddr,&len);
        printf("connection from %s\n",
                Sock_ntop((SA*)&cliaddr, len));
        ticks = time(NULL); 
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));
        Close(connfd);
    }

}
