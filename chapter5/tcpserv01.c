#include <unp.h> 


Sigfunc* mysignal(int signo, Sigfunc * func)
{
    struct  sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(signo == SIGALRM){
        act.sa_flags |= SA_INTERRUPT;
    }
    else {
        act.sa_flags |= SA_RESTART;
    }
        
    if(sigaction(signo, &act, &oact)<0)
        return (SIG_ERR);
    return (oact.sa_handler);
}
void sig_child(int signo);
int main(int argc, char** argv)
{
     int fdListen, fdConn;
     pid_t pidChild;
     socklen_t lenChildren;
    struct sockaddr_in addrClient, addrSvr;

     fdListen = Socket(AF_INET, SOCK_STREAM,0);

     bzero(&addrSvr, sizeof(addrSvr));
     addrSvr.sin_family = AF_INET;    
     addrSvr.sin_addr.s_addr = htonl(INADDR_ANY);   
     addrSvr.sin_port = htons(SERV_PORT);
     
     Bind(fdListen, (SA*) &addrSvr, sizeof(addrSvr));

     Listen(fdListen, LISTENQ);
     signal(SIGCHLD, sig_child);

     for(; ;){
        lenChildren = sizeof(addrClient); 
        fdConn = Accept( fdListen, (SA*) &addrClient,&lenChildren);
        if(fdConn <0)
        {
            if(errno == EINTR)
                continue;
            else
                err_sys("accept error");
        }
        

        if((pidChild = Fork() ) ==0 ){
            Close(fdListen);
            str_echo(fdConn);
            exit(0);
        }
     }
     

}
