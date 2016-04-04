#include <unp.h>

int main(int argc, const char *argv[])
{
    if(argc < 3)
    {
        err_msg("error, usage: cli <host> <service>");
    }

    struct addrinfo hints;
    bzero(&hints, sizeof(hints));
    hints.ai_family =AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo * res;
    int err_code = 0;
    if(0 !=(err_code = getaddrinfo(argv[1], argv[2], &hints, &res)))
    {
        const char* err = gai_strerror(err_code);
        err_msg(err);
    }
    fd_set fds;
    FD_ZERO(&fds);
    int opt_val = 1;
    socklen_t optlen = sizeof(opt_val);
    int maxp1 = 0;
    while(res != NULL)
    {
        int sockfd = socket(res->ai_family,
                res->ai_socktype | SOCK_NONBLOCK,
                res->ai_protocol);
        maxp1 = max(maxp1, sockfd) + 1; 

        connect(sockfd, res->ai_addr, res->ai_addrlen);

        FD_SET(sockfd, &fds);

        res = res->ai_next;
    }
    fprintf(stdout, "after connect iteration\n");
    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;

    int nresult = 0;
    int sockfd;

    nresult = select(maxp1,NULL,&fds, NULL,&tv);
    fprintf(stdout, "select finish %d\n", nresult);
    if(nresult == 0)
    {
        err_msg("time out");
    }
    else if(nresult == -1)
    {
        err_msg("error");
    }

    for(int i = 0; i < maxp1; ++i)
    {
        if(FD_ISSET(i, &fds))
        {
            sockfd = i;
            break;
        }
    }
    fprintf(stdout, "connect success\n");
    char in_buf[MAXLINE];
    char recv_buf[MAXLINE];
    int n = 0;
    fd_set fd_rd;
    fd_set fd_wt;
    maxp1 = sockfd +1; 
    char* buf = fgets(in_buf, MAXLINE, stdin);
    struct timeval rwtv;
    rwtv.tv_sec = 5;
    rwtv.tv_usec = 0;
    Setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &rwtv, sizeof(rwtv));
    Setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &rwtv, sizeof(rwtv));
    struct msghdr rcv_msg;
    bzero(&rcv_msg, sizeof(struct msghdr));
    rcv_msg.msg_name = NULL;
    rcv_msg.msg_namelen = 0;
    struct iovec rcv_iovec;
    bzero(&rcv_iovec, sizeof(struct iovec));
    rcv_iovec.iov_base = recv_buf;
    rcv_iovec.iov_len = MAXLINE;
    rcv_msg.msg_iov = &rcv_iovec;
    rcv_msg.msg_iovlen = 1;
    // don't care ancillary data
    rcv_msg.msg_controllen = 0;
    rcv_msg.msg_control = NULL;
    
    
    while(buf != NULL)
    {
        FD_ZERO(&fd_rd);
        FD_ZERO(&fd_wt);
        FD_SET(sockfd, &fd_rd);
        FD_SET(sockfd, &fd_wt);
        FD_SET(fileno(stdin), &fd_rd);
        //FD_SET(fileno(stdout), &fd_wt);

        int nres = select(maxp1,&fd_rd, &fd_wt, NULL,NULL);
        if(nres <0)
        {
            err_msg("error occur on select");
            break;
        }
        char tmpbuf[MAXLINE];
        bzero(tmpbuf, MAXLINE);
        if(FD_ISSET(sockfd, &fd_rd))
        {
            bzero(rcv_iovec.iov_base, MAXLINE);
            recvmsg(sockfd, &rcv_msg, 0);
            //read(sockfd, tmpbuf, MAXLINE);    
            fprintf(stdout, "recv from sever %s\n", rcv_iovec.iov_base);
            --nres;
            if(nres <= 0) continue;
        }
        if(FD_ISSET(sockfd, &fd_wt))
        {
            if(strlen(in_buf) > 0)
            {
                // equals to write
                if(-1== send(sockfd,in_buf, MAXLINE, 0))
                {
                    fprintf(stdout, "send failure, errno %d\n",errno); 
                }
                else
                {
                    bzero(in_buf, MAXLINE);
                }
            }
            --nres;
            if(nres <=0) continue;
        }
        if(FD_ISSET(fileno(stdin), &fd_rd))
        {
            if(strlen(in_buf) == 0)
            {
                buf = fgets(in_buf, MAXLINE, stdin);
            }
        }

    }

    return 0;
}
