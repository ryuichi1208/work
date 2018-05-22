#include "socket.h"

int main(int argc, char* argv[]) {

    int sock; //local socket descripter
    struct sockaddr_in servSockAddr; //server internet socket address
    unsigned short servPort; //server port number
    char recvBuffer[BUFSIZE];//receive temporary buffer
    char sendBuffer[BUFSIZE]; // send temporary buffer

    if (argc != 3) {
        fprintf(stderr, "argument count mismatch error.\n");
        exit(EXIT_FAILURE);
    }

    //構造体初期化
    memset(&servSockAddr, 0, sizeof(servSockAddr));

    //TCP/IPを指定
    servSockAddr.sin_family = AF_INET;

    if (inet_aton(argv[1], &servSockAddr.sin_addr) == 0) {
        fprintf(stderr, "Invalid IP Address.\n");
        exit(EXIT_FAILURE);
    }

    if ((servPort = (unsigned short) atoi(argv[2])) == 0) {
        fprintf(stderr, "invalid port number.\n");
        exit(EXIT_FAILURE);
    }
    servSockAddr.sin_port = htons(servPort);

    //ソケット作成
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ){
        perror("socket() failed.");
        exit(EXIT_FAILURE);
    }

    //サーバ通信開始
    if (connect(sock, (struct sockaddr*) &servSockAddr, sizeof(servSockAddr)) < 0) {
        perror("connect() failed.");
        exit(EXIT_FAILURE);
    }

    printf("connect to %s\n", inet_ntoa(servSockAddr.sin_addr));

    while(1){
        //任意の文字入力
        printf("please enter the characters:");
        if (fgets(sendBuffer, BUFSIZE, stdin) == NULL){
            fprintf(stderr, "invalid input string.\n");
            exit(EXIT_FAILURE);
        }

        //データ送信
        if (send(sock, sendBuffer, strlen(sendBuffer), 0) <= 0) {
            perror("send() failed.");
            exit(EXIT_FAILURE);
        }

        int byteRcvd  = 0;
        int byteIndex = 0;
        while (byteIndex < MSGSIZE) {
            //返ってきたメッセージをバッファーへ読み出し
            byteRcvd = recv(sock, &recvBuffer[byteIndex], 1, 0);
            if (byteRcvd > 0) {
                if (recvBuffer[byteIndex] == '\n'){
                    recvBuffer[byteIndex] = '\0';
                    if (strcmp(recvBuffer, "quit") == 0) {
                        close(sock);
                        return EXIT_SUCCESS;
                    } else {
                        break;
                    }
                }
                byteIndex += byteRcvd;
            } else if(byteRcvd == 0){
                perror("ERR_EMPTY_RESPONSE");
                exit(EXIT_FAILURE);
            } else {
                perror("recv() failed.");
                exit(EXIT_FAILURE);
            }
        }
        printf("server return: %s\n", recvBuffer);
    }

    return EXIT_SUCCESS;
}
