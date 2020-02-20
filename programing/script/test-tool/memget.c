#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int num;
	char *str;
} strct;

int main(int argc, char *argv[]) {
	//構造体の生成
	strct *entity;

	int getmemsize = atoi(argv[1]);

	//メモリ確保
	entity = (strct*)malloc(sizeof(getmemsize));

	//メンバの初期化
	entity->num = 0;
	entity->str = (char*)malloc(sizeof(32));

	//確保したメモリにデータをセット
	memset(entity->str, 'a', sizeof(32));

	//メモリの開放
	free(entity->str);
	free(entity);
}
