#include <unp.h>
int main(int argc, const char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, 
                "useage : cli <host/ipaddress> <service/port>\n");
        exit(-1);
    }
    struct sockaddr* psa;
    socklen_t len;
    int sockfd = Udp_client(argv[1], argv[2],&psa, &len);
    Sendto(sockfd,"",1,0,psa,len);
    fprintf(stdout, "send to success\n");
    int n = 0;
    char buff[MAXLINE];
    while((n = Recvfrom(sockfd, buff, MAXLINE, 0,NULL, NULL))>0)
    {
        printf("%s\n", buff); 
    }
    return 0;
}
