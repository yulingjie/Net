#include <unp.h>

int main(int argc, char *argv[])
{
    if(argv[1] == NULL)
    {
        printf("should input host name\n");
        exit(1);
    }
  
    struct hostent * phn = gethostbyname(argv[1]);
    if(phn == NULL)
    {
        printf("cannot find host info\n");
        exit(1);
    }
    char** ppaddr;
    switch(phn->h_addrtype)
    {
        case AF_INET:
            {
               printf("official host name: %s\n", phn->h_name); 
               ppaddr = phn->h_aliases; 
               for(;*ppaddr != NULL; ++ppaddr)
               {
                   printf("\talias name: %s", *ppaddr);
               }
               char str[128];
               ppaddr = phn->h_addr_list;
               for(; *ppaddr != NULL; ++ppaddr)
               {
                   bzero(str, 128);
                   Inet_ntop(AF_INET, *ppaddr, str, 128);
                   printf("\taddress: %s\n", str);
               }
            }
            break;
        default:
            {
                printf("unknow host type");
            }
    }

    return 0;
}
