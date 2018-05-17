#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

#define QUEUELIMIT 5
#define MSGSIZE 1024
#define BUFSIZE (MSGSIZE + 1)

int main(int argc, char* argv[]) {

    int servSock;
    int clitSock;
    struct sockaddr_in servSockAddr;
    struct sockaddr_in clitSockAddr;
    unsigned short servPort;
    unsigned int clitLen;
    char recvBuffer[BUFSIZE];
    int recvMsgSize, sendMsgSize;

    if ( argc != 2) {
        fprintf(stderr, "argument count mismatch error.\n");
        exit(EXIT_FAILURE);
    }

    //ポート番号の整合性確認
    if ((servPort = (unsigned short) atoi(argv[1])) == 0) {
        fprintf(stderr, "invalid port number.\n");
        exit(EXIT_FAILURE);
    }

    //ソケット作成
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ){
        perror("socket() failed.");
        exit(EXIT_FAILURE);
    }

    //構造体初期化
    memset(&servSockAddr, 0, sizeof(servSockAddr));
    servSockAddr.sin_family      = AF_INET;
    servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servSockAddr.sin_port        = htons(servPort);

    //ソケットに対しポート番号とIPアドレスをバインド
    if (bind(servSock, (struct sockaddr *) &servSockAddr, sizeof(servSockAddr) ) < 0 ) {
        perror("bind() failed.");
        exit(EXIT_FAILURE);
    }

    //クライアントからの通信待受
    if (listen(servSock, QUEUELIMIT) < 0) {
        perror("listen() failed.");
        exit(EXIT_FAILURE);
    }

    while(1) {
        clitLen = sizeof(clitSockAddr);
        if ((clitSock = accept(servSock, (struct sockaddr *) &clitSockAddr, &clitLen)) < 0) {
            perror("accept() failed.");
            exit(EXIT_FAILURE);
        }
        printf("connected from %s.\n", inet_ntoa(clitSockAddr.sin_addr));

        while(1) {
            //メッセージ受信
            if ((recvMsgSize = recv(clitSock, recvBuffer, BUFSIZE, 0)) < 0) {
                perror("recv() failed.");
                exit(EXIT_FAILURE);
            } else if(recvMsgSize == 0){
                fprintf(stderr, "connection closed by foreign host.\n");
                break;
            }
            
            //受信したメッセージをそのままエコー
            if((sendMsgSize = send(clitSock, recvBuffer, recvMsgSize, 0)) < 0){
                perror("send() failed.");
                exit(EXIT_FAILURE);
            } else if(sendMsgSize == 0){
                fprintf(stderr, "connection closed by foreign host.\n");
                break;
            }
        }

        close(clitSock);
    }

    close(servSock);

    return EXIT_SUCCESS;
}
