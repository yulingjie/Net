#include <unp.h>
void signal_alarm(int signu )
{
    return;
}
int main(int argc, const char *argv[])
{
   int sockfd;
   if(argc <3)
   {
       err_msg("error, usage: cli <Host> <Service>");
       exit(-1);
   }
   struct addrinfo hints;
   bzero(&hints, sizeof(struct addrinfo));
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_protocol = 0;
   struct addrinfo* res;
   int result = getaddrinfo(argv[1],argv[2], &hints, &res);
   if(result != 0)
   {
       const char* tips = gai_strerror(result);
       err_msg("error, get addrinfo %s", tips);
       exit(-1);
   }
  Sigfunc * sigfunc = Signal(SIGALRM, signal_alarm); 
   struct addrinfo * ai = res;    
   while(ai != NULL)
   {
       alarm(10);
       sockfd = Socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
       int result = connect(sockfd, ai->ai_addr, ai->ai_addrlen);
       if(result == 0)
       { // success
           fprintf(stdout, "connect success");
           fflush(stdout);
           break;
       }
       else if(result < 0)
       {
           ai = ai->ai_next;
           if(errno == EINTR)
           {
               err_msg("time out");
           }
       }
   }
   alarm(0);
   Signal(SIGALRM, sigfunc);
    char in_buf[MAXLINE];
    char recv_buf[MAXLINE];
    bzero(recv_buf, MAXLINE);
    bzero(in_buf, MAXLINE);
    while(fgets(in_buf, MAXLINE, stdin) != NULL)
    {
        write(sockfd, in_buf, strlen(in_buf));
        bzero(recv_buf, MAXLINE);
        read(sockfd, recv_buf, MAXLINE);
        fprintf(stdout, "%s \n", recv_buf);
    }
    return 0;
}
