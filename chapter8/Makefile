SHELL := /bin/bash
all:serv cli serv01 cli01
	
serv01: serv01.o
	gcc serv01.o -o serv01 -lunp

serv01.o: udpserv01.c
	gcc -c ./udpserv01.c -o serv01.o -lunp

cli01: cli01.o
	gcc cli01.o -o cli01 -lunp

cli01.o: udpcli01.c
	gcc -c ./udpcli01.c -o cli01.o -lunp
	
serv: serv.o
	gcc serv.o -o serv -lunp

serv.o: udpserv.c
	gcc -c udpserv.c -o serv.o -lunp

cli: cli.o
	gcc cli.o -o cli -lunp

cli.o: udpcli.c
	gcc -c udpcli.c -o cli.o -lunp

clean:
	bash -c "if [ -f serv ]; then rm serv; fi"
	bash -c "if [ -f cli ]; then rm cli; fi"
	bash -c "if [ -f serv01 ]; then rm serv01; fi"
	bash -c "if [ -f cli01 ]; then rm cli01; fi"
	for flo in ./*.o; do rm "$$flo"; done
