#include <unp.h>

int main(int argc, char *argv[])
{
    if(argv[1] == NULL)
    {
        fprintf(stderr, "should input host address name in first place\n");
        exit(1);
    }
    if(argv[2] == NULL)
    {
        fprintf(stderr, "should input host port name in second place\n");
        exit(1);
    }

    struct hostent * pserv = gethostbyname(argv[1]);
    if(pserv == NULL)
    {
        fprintf(stderr, "error, cannot find numeric address of input host\n");
        exit(1);
    }
    if(pserv->h_addrtype != AF_INET)
    {
        fprintf(stderr, "error, pserver typer is not ipv4\n");
        exit(1);
    }
    struct servent* pport = getservbyname(argv[2],argv[3]);
    if(pport == NULL)
    {
        fprintf(stderr, "error, cannot find numeric port of input port name\n");
        exit(1);
    }
    else
    {
        printf("get serv by name success\n");
    }
    char** pptr = pserv->h_addr_list;
    int count = 0;
    for(; *pptr != NULL; ++pptr)
    {
        ++count;
    }
    pptr = NULL;
    int i = 0;
    struct sockaddr_in servaddr;
    fd_set fds;
    int maxp1 = 0;
    pptr = pserv->h_addr_list;
    //for(;*pptr != NULL; ++pptr)
    //{
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = pport->s_port;
        memcpy(&servaddr.sin_addr,*pptr, sizeof(struct in_addr));
        int sockfd = Socket(AF_INET, SOCK_STREAM,0);
       // Fcntl(sockfd, F_SETFL, O_NONBLOCK);
        if(0 == connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
        {
            printf("connect success!\n");
        }
        
        if(errno == EINPROGRESS)
        {
            printf("need wait for connection \n");
        }
        FD_SET(sockfd, &fds);
        maxp1 = max(sockfd, maxp1) + 1;
    //}
    
    int n = 0;
    char recvbuf[MAXLINE];
    scanf(recvbuf, "%s", MAXLINE);
    Write(sockfd, recvbuf, strlen(recvbuf));
    while( (n = Read(sockfd, recvbuf, MAXLINE)) > 0)
    {
        recvbuf[n] = 0;
        printf("read from serv %s\n", recvbuf );
    }
   /* struct timeval wait_time;
    wait_time.tv_sec = 20L;
    wait_time.tv_usec = 0L;
    i = 0;
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    char addr[128];
    char buff[MAXLINE];
    printf("before while \n");
    //while(1)
    {
        int rt = Select(maxp1, NULL,&fds, NULL, &wait_time);    
        printf("after select rt = %d",rt);
        while( (i < maxp1) && (rt > 0))
        {
            if(FD_ISSET(i, &fds))
            {
                printf("connect success!");
                --rt;
                bzero(&cliaddr, sizeof(cliaddr));
                clilen = sizeof(cliaddr);
                if(0 == getsockname(i, (struct sockaddr*)& cliaddr, &clilen))
                {
                    printf("sock addr %s port %d connect success!\n", 
                            Inet_ntop(AF_INET, &cliaddr.sin_addr, addr, 128),
                            ntohs(cliaddr.sin_port) );
                    exit(0);

                }

            }
        }
    }
    */

    return 0;
}
