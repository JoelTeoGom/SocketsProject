client : client.c 
	gcc -Wall client.c -o client 

servidor : servidor.c
	gcc -Wall servidor.c -o servidor 

clean : 
	rm -f client servidor