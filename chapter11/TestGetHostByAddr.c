#include <unp.h>

int main(int argc, char *argv[])
{
    if(argv[1] == NULL)
    {
        printf("error, input address is null\n");
        exit(1);
    }
    struct in_addr addr;
    if(inet_aton(argv[1], &addr) != 1)
    {
       printf("error, cannot translate addr to numeric\n");     
       exit(1);
    }

    char buf[128];
    printf("test inet_aton %s\n len %lu\n", Inet_ntop(AF_INET,&addr, buf, 128), sizeof(addr));
    struct hostent * phn=gethostbyaddr(&addr, sizeof(addr), AF_INET);
    if(phn == NULL)
    {
        printf("error, hostent is null\n");
        printf("%s\n", hstrerror(h_errno));
        exit(1);
    }
    printf("official addr: %s\n", phn->h_name);
    return 0;
}
