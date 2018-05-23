#include "socket.h"

//子プロセス関数
void child_func(int clitSock) {
	char recvBuffer[BUFSIZE];
	int recvMsgSize, sendMsgSize;

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
}

int main(int argc, char* argv[]) {

    int pid;
    int servSock;
    int clitSock;
    struct sockaddr_in servSockAddr;
    struct sockaddr_in clitSockAddr;
    unsigned short servPort;
    unsigned int clitLen;

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

    //自ホストネームの取得
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        puts("error");
        return 0;
    }

    //自サーバの情報表示
    fprintf(stdout, "PROTCOL : %d\n", servSockAddr.sin_family);
    fprintf(stdout, "HOST    : %s\n", hostname);
    fprintf(stdout, "PORT    : %d\n", servSockAddr.sin_port);

    int fork_cnt;
    while(1) {
        clitLen = sizeof(clitSockAddr);
	//
        if ((clitSock = accept(servSock, (struct sockaddr *) &clitSockAddr, &clitLen)) < 0) {
            perror("accept() failed.");
            exit(EXIT_FAILURE);
        }
        printf("connected from %s.\n", inet_ntoa(clitSockAddr.sin_addr));

	//通信は子プロセスで実行
	if (pid = fork() == 0) {
		close(servSock);
		child_func(clitSock);
	}
	fork_cnt++;
	fprintf(stdout,"child proc connect %d\n", fork_cnt);
        close(clitSock);
    }

    close(servSock);

    return EXIT_SUCCESS;
}
