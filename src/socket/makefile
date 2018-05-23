all:socket_cli.c socket_srv.c
	gcc -Wall -O2 -o socket_cli socket_cli.c
	gcc -Wall -O2 -o socket_srv socket_srv.c
	gcc -Wall -O2 -o broadcast broadcast.c

clean:socket_cli socket_srv
	rm -rf socket_cli socket_srv
