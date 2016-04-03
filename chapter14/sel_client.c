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
    while(fgets(in_buf, MAXLINE, stdin) != NULL)
    {
        write(sockfd, in_buf, strlen(in_buf));
        fprintf(stdout , "after write, before read\n");
        // will raise EAGAIN here, ofr sockfd is no-block
        // use select to read instead ??
        int r = read(sockfd,recv_buf, MAXLINE); 
        fprintf(stdout, "read after %d\n", r);
        if(r == -1)
        {
            
            fprintf(stdout, "errno : %d\n", errno);
        }
        fprintf(stdout, "%s", recv_buf);
        fflush(stdout);
    }
    return 0;
}
