#include <unp.h>

int main(int argc, char *argv[])
{
    if(argv[1] == NULL)
    {
        printf("error, should input serv name");
        exit(1);
    }
    struct servent * psvn = getservbyname(argv[1], argv[2]);
    printf("official service name %s, port %d \n", psvn->s_name, ntohs(psvn->s_port));
    return 0;
}
