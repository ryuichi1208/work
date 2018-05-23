#include "socket.h"

//ブロードキャスト時に必要な情報を持つ構造体
struct broadcast_info {
    unsigned short port;
    int sd;
    struct sockaddr_in addr;
};
typedef struct broadcast_info bc_info_t;

//ブロードキャストの受信
static int broadcast_receive(bc_info_t *info, char *errmsg) {
    char recv_msg[MAXRECVSTRING+1];
    int recv_msglen = 0;

    recv_msglen = recvfrom(info->sd, recv_msg, MAXRECVSTRING, 0, NULL, 0);
    if(recv_msglen < 0){
        sprintf(errmsg, "(line:%d) %s", __LINE__, strerror(errno));
        return(-1);
    }

    recv_msg[recv_msglen] = '\0';
    printf("Received: %s\n", recv_msg);

    return(0);
}

//ソケットの初期化
static int socket_initialize(bc_info_t *info, char *errmsg) {
    int rc = 0;

    //ソケットの初期化 プロトコルはUDPを指定
    info->sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(info->sd < 0){
        sprintf(errmsg, "(line:%d) %s", __LINE__, strerror(errno));
        return(-1);
    }

    info->addr.sin_family = AF_INET;
    info->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    info->addr.sin_port = htons(info->port);

    /* ブロードキャストポートにバインドする*/
    rc = bind(info->sd, (struct sockaddr *)&(info->addr),
              sizeof(info->addr));
    if(info->sd < 0){
        sprintf(errmsg, "(line:%d) %s", __LINE__, strerror(errno));
        return(-1);
    }

    return(0);
}

static void socket_finalize(bc_info_t *info) {
    /* ソケット破棄 */
    if(info->sd != 0) close(info->sd);

    return;
}

static int broadcast_receiver(bc_info_t *info, char *errmsg) {
    int rc = 0;

    /* ソケットの初期化 */
    rc = socket_initialize(info, errmsg);
    if(rc != 0) return(-1);

    /* ブロードキャストを送信する */
    rc = broadcast_receive(info, errmsg);

    /* ソケットの終期化 */
    socket_finalize(info);

    return(0);
}

static int initialize(int argc, char *argv[], bc_info_t *info, char *errmsg) {
    if(argc != 2){
        sprintf(errmsg, "Usage: %s <port>", argv[0]);
        return(-1);
    }

    memset(info, 0, sizeof(bc_info_t));
    //ポート番号の妥当性判断
    info->port = atoi(argv[1]);

    return(0);
}

//第一引数にポート番号を指定
int main(int argc, char *argv[]) {
    int rc = 0;
    bc_info_t info = {0};
    char errmsg[BUFSIZ];

    rc = initialize(argc, argv, &info, errmsg);
    if(rc != 0){ 
        fprintf(stderr, "Error: %s\n", errmsg);
        return(-1);
    }   

    rc = broadcast_receiver(&info, errmsg);
    if(rc != 0){ 
        fprintf(stderr, "Error: %s\n", errmsg);
        return(-1);
    }

    return(0);
}

