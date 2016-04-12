#include <unp.h>
#include "my_open.h"
#include "read_fd.h"
int my_open(char* pathname, int mode)
{
    int sockfd[2];
    if(socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd) <0)
    {
        fprintf(stderr, "error create socket pair\n");
        exit(errno > 0 ? errno : 255);
    }
    int childpid = 0;
    if((childpid = Fork()) == 0)
    {
        close(sockfd[0]);    
        char c;
        char argsockfd[20];
        char argmode[20];
        snprintf(argsockfd, sizeof(argsockfd), "%d",sockfd[1]);
        snprintf(argmode, sizeof(argmode), "%d", mode);
        execl("./openfile","openfile", argsockfd, pathname, argmode, (char*)NULL);
        err_sys("execl error");
        exit(errno > 0 ? errno : 255);
    }
    close(sockfd[1]);
    int status;
    int fd;
    char c;
    waitpid(childpid, &status, 0);
    if(!WIFEXITED(status))
    {
        err_quit("error, child not terminate correctly");
    }
    if((status = WEXITSTATUS(status)) == 0)
    {
        my_read_fd(sockfd[0], &c,1,&fd);
    }
    else
    {
        errno = status;
        fd = -1;
    }
    close(sockfd[0]);
    return fd;
}
