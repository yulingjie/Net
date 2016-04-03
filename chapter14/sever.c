#include <unp.h>

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        err_msg("usage: svr <service>");
    }
    // listen to tcp socket
    struct addrinfo hints;
    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    struct addrinfo * ai_res;
    int result = getaddrinfo(NULL, argv[1], &hints, &ai_res);
    if(result != 0)
    {
        const char* err = gai_strerror(result);
        err_msg(err);
    }
    int listenfd = -1 ;
    while(ai_res != NULL)
    {
        fprintf(stdout,"%s",
                sock_ntop(ai_res->ai_addr, ai_res->ai_addrlen));
        listenfd = socket(ai_res->ai_family, ai_res->ai_socktype, ai_res->ai_protocol);
        
        if(bind(listenfd, ai_res->ai_addr, ai_res->ai_addrlen) == 0)
        {
            break;
        }
        ai_res = ai_res->ai_next;
    }
    freeaddrinfo(ai_res);

    if(listenfd == -1)
    {
        err_msg("error, cannot find listen fd to bind");
    }
    listen(listenfd, 1024);
    struct sockaddr_storage ss;
    bzero(&ss, sizeof(ss));
    socklen_t len = sizeof(ss);
    int sockfd = accept(listenfd,(struct sockaddr*) &ss, &len);
    if(sockfd == -1)
    {
        err_msg("error, cannot accept sockfd");
    }
    char recv_buf[MAXLINE];
    int n = 0;
    while((n = read(sockfd, recv_buf, MAXLINE)) > 0)
    {
        write(sockfd, recv_buf, strlen(recv_buf));
    }
    return 0;
}
