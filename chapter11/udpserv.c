#include <unp.h>

int main(int argc, const char *argv[])
{
    if(argc <3)
    {
        fprintf(stderr, "usage: udpserv <host> <service>\n");
        exit(-1);
    }
    int sockfd = udp_server(argv[1], argv[2], NULL);
    int n = 0;
    struct sockaddr_storage ss;
    socklen_t clilen = sizeof(ss);
    char buf[MAXLINE];
    time_t ticks; 
    char tmbuf[MAXLINE];
    while( ( n = recvfrom(sockfd,buf, MAXLINE, 0, (struct sockaddr*)&ss, &clilen)) >0)
    {
      ticks = time(NULL); 
      snprintf(tmbuf, sizeof(tmbuf), "%.24s\r\n", ctime(&ticks));
      sendto(sockfd, tmbuf, strlen(tmbuf),0, (struct sockaddr*)&ss, clilen);
    }
    return 0;
}
