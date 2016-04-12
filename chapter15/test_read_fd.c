#include <unp.h>
#include "read_fd.h"
#include "write_fd.h"
int main(int argc, const char *argv[])
{
    int test_sendfd = 10;
    char test_bt = 'a';
    // 0 server, 1 client
    int fdarr[2];
    if(socketpair(AF_LOCAL,SOCK_STREAM, 0, fdarr) < 0)
    {
        err_quit("error, socket pair");
    }
    pid_t cid;
    if((cid =fork()) == 0)
    {
        fprintf(stdout, "%s\n", "in_child process");
        // child
        close(fdarr[1]);
        char c = test_bt;
        int fd = open("./test_data",O_RDONLY);
        if(fd < 0)
        {
            fprintf(stderr, "open test_data error\n");
            exit(errno > 0 ? errno : 255);
        }
        int n = my_write_fd(fdarr[0],&c, 1, fd);
        if(n <0)
        {
            fprintf(stderr, "write_fd error\n");
            exit(errno> 0 ? errno : 255);
        }
    }
    else
    {
        fprintf(stdout, "%s\n", "in parent process");
        // parent
        close(fdarr[0]);
        char c;
        int rcv_fd;

        int status = 0;
        waitpid(cid,&status, 0);
        int n = 0;
        if(WIFEXITED(status))
        {
            fprintf(stdout, "%s\n","before recv msg");
            if ( (n = my_read_fd(fdarr[1],&c, 1,&rcv_fd))  <= 0)
            {
                fprintf(stderr, "error recv msg %d\n", errno );
                exit(errno);
            }
            else{
                fprintf(stdout, "%s\n","success");
            }
            char buf[MAXLINE];
            read(rcv_fd, buf, MAXLINE);
            fprintf(stdout, "read result:\n%s\n", buf);
        }
    }
    return 0;
}
