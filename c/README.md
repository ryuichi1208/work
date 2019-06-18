## C

#### プリプロセッサ

```
// ヘッダインクルード
#include <stdio.h>

// マクロ
#define	_MY_DEBUG(x) printf("val = %d\n",x);

// 2重インクルードガード
#ifndef INCLUDED_DATE
#define INCLUDED_DATE

// 文字列置き換え取り消し
#undef <識別子名>
```

#### ポインタ

```
// 普通の使い方
int val;
int *pointer_of_val = &val;
*pointer_of_val = 10;

// 下記の書き方だとotherはint型
int* pointer1, other;

// 配列のポインタ
// intポインタ型の要素が10個の配列
int *array_of_pointer[10];

// int型の10個の配列へのポインタ
int (*pointer_of_array)[10];

// 戻り値なし引数なしの関数型の変数pfunc
void (*pfunc)();

// 関数ポインタはtypedefしとくと便利
typedef int (*MYFUNC)(int n);
```

#### 構造体

```
// 基本形
typedef struct person {
	char *name;
	char sex;
	int age;
	char *add;
	char *job;
} person;

// ポインタとして利用
person *p = malloc(sizeof(person) * 10)
fprintf(stdout, "p->job = %s", p->job)
```

#### 共用体

メモリの使用を制限して型の違う変数を使用したい場合に使う

``` c
union staff {
  char id[8 + 1]; ---- 値全体
  char branch[2]; ---- 先頭から2バイト分
  char sect[4]; ------ 先頭から4バイト分
  char pos[6]; ------- 先頭から6バイト分
};
```

#### カーネルディレクトリ構造

- arch
  - arch サブディレクトリにはアーキテクチャ(architecture)固有の カーネルコードが含まれている。

- include
  - include サブディレクトリにはカーネルコードをビルドするのに必要なインクルードファイル(include files)の大部分が含まれている。

- init
  - カーネルの初期化(initialization)コードが含まれている
  - カーネルの動作の仕組みをこれから見ようとする場合はよい出発点になる。

- mm
  - メモリ管理(memory management)コードのすべてが含まれている。

- drivers
  - システム上のデバイスドライバ(device drivers)はすべてこのディレクトリに置かれ ている。

- ipc
  - カーネルのプロセス間通信(inter-process communications)に 関するコードが含まれている。

-  modules
  - このディレクトリはビルドされたモジュール(module)を保存するためだけに使用され ている。

- fs
  - ファイルシステム(file system)コードのすべてはここに置かれている。

- kernel
  - 主要なカーネル(kernel)コードが置かれている。ここでもアーキテクチャ固有の カーネルコードは、arch/*/kernel にある。

- net
  - カーネルのネットワーク(network)関係のコードが置かれている。

- lib
  - カーネルのライブラリ(library)コードが含まれている。

- scripts
  - カーネルを設定するときに使用されるスクリプト

#### ソケット通信
