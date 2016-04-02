#include "Util.h"

int TcpListen(const char* host, const char* serv, socklen_t * addrlenp)
{
    int listenfd,n;
    const int on = 1;
    struct addrinfo hints, * res, *ressave;
    ressave = res; 
    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    
    n = getaddrinfo(host,serv,&hints, &res);
    if(n !=0)
    {
        fprintf(stderr, "error get addrinfo, %s\n",
                gai_strerror(n));
    }
    do{
        listenfd = 
            socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if(listenfd < 0)
        {
            continue;
        }

        Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if(bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;
        Close(listenfd);
    }while((res = res->ai_next) != NULL);

    if(res == NULL)
    {
        fprintf(stderr,
                "tcp listen error for host%s, serv %s\n",
                host, serv);
    }
    Listen(listenfd, LISTENQ);
    if(addrlenp )
        *addrlenp = res->ai_addrlen;
    freeaddrinfo(ressave);
    return listenfd;
}

