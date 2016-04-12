#include <unp.h>
#include"read_fd.h"

/*
 * read file descriptor from unix domain socket
 */
int my_read_fd(int udfd, char* ptr, int n, int * rcv_fd)
{
    struct msghdr msg; 
    bzero(&msg, sizeof(struct msghdr));
    int new_fd;
#ifdef HAVE_MSGHDR_MSG_CONTROL
    union{
        struct cmsghdr controller;
        char buffer[CMSG_SPACE(sizeof(int))];
    } controller_un;
    msg.msg_controllen = sizeof(controller_un.buffer);
    msg.msg_control = controller_un.buffer;
#else
    msg.msg_accrights =(caddr_t) &new_fd;
    msg.msg_accrightslen = sizeof(new_fd);
#endif
    char name_buf[MAXLINE];
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    struct iovec iov;
    bzero(&iov, sizeof(struct iovec));
    iov.iov_base = ptr;
    iov.iov_len=n;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    int rt = 0;
    // it would never be 0, since we send one byte anyway
    if((rt =recvmsg(udfd, &msg, 0)) <=0)
    {
        fprintf(stdout, "123\n");
        err_msg("error: recv msg");
        return rt;
    }
#ifdef HAVE_MSGHDR_MSG_CONTROL
    struct cmsghdr *pcmsg;
    if((pcmsg =CMSG_FIRSTHDR(&msg)) != NULL
            && pcmsg->cmsg_len == CMSG_LEN(sizeof(int)))
    {
        if(pcmsg->cmsg_level != SOL_SOCKET)
        {
            err_quit("error, cmsg level is not SOL_SOCKET");
        }
        if(pcmsg->cmsg_type != SCM_RIGHTS)
        {
            err_quit("error, cmsg type is not SCM_RIGHTS");
        }
        *rcv_fd =*(int*) CMSG_DATA(pcmsg);
    }
#else
    if(msg.msg_accrightslen == sizeof(int))
    {
        *rcv_fd = new_fd;
    }
    else
    {
        rcv_fd = -1;
    }
#endif
    return rt;
}
