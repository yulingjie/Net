#include <unp.h>
#include "write_fd.h"

int my_write_fd(int udfd, char* ptr, int nbyte, int sendfd)
{
    struct msghdr msg;
    struct iovec iov;
    ssize_t n;
    bzero(&msg, sizeof(struct msghdr));

    union {
        struct cmsghdr cm;
        char controller[CMSG_SPACE(sizeof (int))];
    } controller_un;
    msg.msg_control = controller_un.controller;
    msg.msg_controllen = sizeof(controller_un.controller);

    struct cmsghdr* pcmsg =CMSG_FIRSTHDR(&msg);
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    *((int*)CMSG_DATA(pcmsg)) = sendfd;
    bzero(&iov, sizeof(struct iovec));
    iov.iov_base = ptr;
    iov.iov_len = nbyte;
    msg.msg_iov= &iov;
    msg.msg_iovlen = 1;
    return sendmsg(udfd, &msg, 0);
}
