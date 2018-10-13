#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

/* ノードの構造体 */
typedef struct _n {
  int id;              /* 添字 */
  int num;             /* 数値 */
  struct _n *left;     /* 左 -- 自己参照 */
  struct _n *right;    /* 右 -- 自己参照 */
} _node;

/* 配列生成:探索先の配列 */
int arry[] = {3, 6, 2, 7, 1, 4, 8, 12};

/* 探索先表示関数 探索処理 */
void showarray() {
	int i;

	printf("探索先 :");
	for (i=0; i<7; i++) {
		printf("%d ", arry[i]);
	}
	printf("¥n");
}

/* 木生成関数*/
void maketree(_node *p1, int id, int num) {
	_node *p2;

	/* 値の大小によって左右に振り分ける */
	if (p1->num <= num) {    /* 主ノードより大きいとき */
		/* 右がNULLならそこに新たなノードをぶら下げる */
		if (p1->right == NULL) {
			p2 = malloc(sizeof(_node));
			p2->id = id;
			p2->num = num;
			p2->left = NULL;
			p2->right = NULL;
			p1->right = p2;
		} else {  /* NULLでなければ右側のノードに移動 */
			maketree(p1->right, id, num);
		}
	} else {
		/* 左がNULLならそこに新たなノードをぶら下げる */
		if (p1->left == NULL) {
			p2 = malloc(sizeof(_node));
			p2->id = id;
			p2->num = num;
			p2->left = NULL;
			p2->right = NULL;
			p1->left = p2;
		} else {
			maketree(p1->left, id, num);
		}
	}
}

/* バイナリサーチ */
int search(_node *p, int n) {
	while (p != NULL) {
		if (n == p->num) {
			printf("%d は %d 番目に見付かりました。¥n", n, p->id + 1);
			return(0);  /* 値が見付かれば終了 */
		} else if (n <= p->num) {
			p = p->left;
		} else {
			p = p->right;
		}
	}

	printf("%d は見付かりませんでした。¥n", n);
	return -1;
}

int main() {
	_node *start, *p1;
	int i, n;

	showarray();

	/* search number input */
	printf("input number : ");
	scanf("%d", &n);

	printf("¥n");

	start = malloc(sizeof(_node));
	start->id = 0;
	start->num = arry[0];
	start->left = NULL;
	start->right = NULL;
	p1 = start;

	/* 残る値から木構造を生成 */
	for (i=1; i<7; i++) {
		maketree(p1, i, arry[i]);
	}

	/* 木構造をたどって探索 */
	return (search(p1, n));
}
