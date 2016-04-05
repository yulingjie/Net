#include <unp.h>

int main(int argc, const char *argv[])
{
    if(argc <2)
    {
        err_msg("usage: unixbind <filepath>");
    }
    
    unlink(argv[1]);
    struct sockaddr_un addr1, addr2;
    bzero(&addr1, sizeof(struct sockaddr_un));
    addr1.sun_family = AF_LOCAL;
    strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path) -1);
    int sockfd = socket(AF_LOCAL,SOCK_STREAM, 0);
    // use sizeof(addr1) here is valid too
    bind(sockfd, (struct sockaddr*)&addr1, SUN_LEN(&addr1));
    printf("sun len %lu, normal len %lu\n", SUN_LEN(&addr1), sizeof(addr1));
    socklen_t len = sizeof(addr2);
    getsockname(sockfd, (struct sockaddr*)&addr2, &len);
    printf("bind path name %s, length %d\n",addr2.sun_path,len);
    return 0;
}
