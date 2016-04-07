#include <unp.h>

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        err_msg("usage: udpcli <filepath>");
    }
   int sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
   struct sockaddr_un cliaddr;
   bzero(&cliaddr, sizeof(struct sockaddr_un));
   cliaddr.sun_family = AF_LOCAL;
   strncpy(cliaddr.sun_path,tmpnam(NULL), sizeof(cliaddr.sun_path));
   bind(sockfd, (SA*)&cliaddr, sizeof(cliaddr));
   struct sockaddr_un svraddr;
   bzero(&svraddr, sizeof(struct sockaddr_un));
   svraddr.sun_family = AF_LOCAL;
   strncpy(svraddr.sun_path, argv[1], sizeof(svraddr.sun_path));
   char in_buf[MAXLINE];
   while(fgets(in_buf, MAXLINE, stdin) != NULL)
   {
       sendto(sockfd,in_buf, MAXLINE,0, (SA*)&svraddr, sizeof(svraddr));
       fprintf(stdout, "sendto success\n");
       bzero(in_buf, MAXLINE);
       recvfrom(sockfd, in_buf, MAXLINE, 0, NULL, NULL);
       fprintf(stdout, "%s\n",in_buf);
   }
   return 0;
}
