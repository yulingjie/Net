#include<sys/select.h>
#include<sys/types.h>
#include<sys/select.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

static volatile int exit_request = 0;
static void hdl(int sig){
    exit_request = 1;
}

static void handle_client(int lfd)
{
    int sock = accept(lfd, NULL, 0);
    if(sock <0){
        perror("accept");
        exit(1);
    }
    puts("acceptd client");

    close(sock);
}
int main(int args, char* argv[])
{
    int lfd;
    struct sockaddr_in myaddr;
    int yes = 1;
    sigset_t mask;
    sigset_t orig_mast;
    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_handler = hdl;
    if(sigaction(SIGTERM, &act,0)){
        perror("sigaction");
        return 1;
    }

}
