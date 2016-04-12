
test_read_fd: read_fd.o write_fd.o test_read_fd.o
	gcc read_fd.o write_fd.o test_read_fd.o -o test_read_fd -lunp
read_fd.o: read_fd.c
	gcc -c read_fd.c -o read_fd.o 
write_fd.o: write_fd.c
	gcc -c write_fd.c -o write_fd.o
test_read_fd.o: test_read_fd.c 
	gcc -c test_read_fd.c -o test_read_fd.o

