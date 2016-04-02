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
    struct sockaddr *psa;
    socklen_t len;
    socklen_t clilen= sizeof(cliaddr);
    int listenfd = udp_client(argv[1], argv[2], &psa, &len);
    if(listenfd < 0) fprintf(stderr, "wrong fd\n");

    Bind(listenfd,(struct sockaddr*)psa, len);
    int n = 0;

    time_t ticks;
    char buff[MAXLINE];
    char tmbuff[MAXLINE]; 
    Recvfrom(listenfd,buff, MAXLINE,0,(struct sockaddr*)&cliaddr, &clilen);
    ticks = time(NULL); 
    fprintf(stdout, "recv end\n");
    snprintf(tmbuff, sizeof(tmbuff), "%.24s\r\n", ctime(&ticks));
    Sendto(listenfd,tmbuff, sizeof(tmbuff), 0,(struct sockaddr*)&cliaddr,clilen);

   
}
