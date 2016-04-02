#include <unp.h> 

int main( int argc, char** argv)
{
    int fdSock;
    struct sockaddr_in addrSvr;
    if(argc != 2)
    {
        err_quit("usage: tcpcli <IPAddress>");
    }
    fdSock = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&addrSvr, sizeof(addrSvr));
    addrSvr.sin_family = AF_INET;
    addrSvr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], & addrSvr.sin_addr);

    Connect(fdSock, (SA*) &addrSvr, sizeof(addrSvr));

    str_cli(stdin, fdSock);
    
    exit(0);
}
