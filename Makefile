all: ser client
ser: hash.o list.o sds.o server.o cmdparse.o call.o  
	gcc -o ser  server.o  hash.o list.o sds.o cmdparse.o call.o 
server.o:
	gcc -o server.o -c server.c 
client: 
	gcc -o client  tcpsocket_client.c
cmdparse.o:
	gcc -o cmdparse.o -c cmd_parse.c
call.o:
	gcc -o call.o  -c call.c
hash.o: list.o sds.o 
	gcc -o hash.o -c hash.c 
list.o: sds.o
	gcc -o list.o  -c list.c
sds.o: sds.h sds.c 
	gcc -o sds.o -c  sds.c
clean:
	rm *.o
