#include <unp.h>
int main(int argc, char *argv[])
{
    int sockfd = Socket(AF_INET,SOCK_STREAM,0); 
    struct sockaddr_in servaddr;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    socklen_t servlen = sizeof(servaddr);
    Bind(sockfd, (struct sockaddr*) &servaddr, servlen);
    Listen(sockfd, SOMAXCONN);
    int clifd;
    for(; ; )
    {
       clifd = Accept(sockfd, NULL, NULL);  
       if(clifd != -1)
       {
            pid_t child = Fork();
            if(child == 0)
            {
                Close(sockfd);
                printf("create child process success! \n");     
                break;
            }
            else
            {
                printf("child process pid [%d]", child);

            }
       }
    }
    // echo server
    char buff[1024];
    while(1)
    {
        Read(clifd,buff, 1024); 
        Write(clifd, buff, strlen(buff));
    }
    return 0;
}

