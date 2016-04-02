all: serv cli

serv: 
	gcc ./tcpserv.c -o serv -lunp

cli:
	gcc ./tcpcli.c -o cli -lunp

clean:
	if [ -f serv ] ; then rm serv; fi		
	if [ -f cli ] ; then rm cli; fi
