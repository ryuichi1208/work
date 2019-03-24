#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <errno.h>
#include <stdbin.h>

#define QUEUELIMIT 5
#define MSGSIZE 1024
#define BUFSIZE (MSGSIZE + 1)
#define MAXRECVSTRING 255
#define MINRECVSTRING 1
