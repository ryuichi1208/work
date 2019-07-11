## 特殊変数

FS  : フィールド セパレータ
OFS : 出力フィールドのセパレータ
RS  : レコードセパレータ
NF  : カレントレコードのフィールド数
NR  : カレントレコード


## パターンマッチ

##### grep風に使い行番号も一緒に出力

``` bash
$ cat /etc/passwd | awk 'BEGIN {print "list"} /ti/ {print NR, $0} END {print "END"}'
```

##### 偶数の行だけn文字目からm文字目までを抜き出す

``` bash
$ cat /etc/passwd | awk -F":" 'BEGIN {OFS=","} NR%2==0 && /\d/ && $3==265  {print substr($0,5)}'
```

##### ユーザIDの合計数と平均値を出力する

``` bash
$ cat /etc/passwd | awk -F":" 'BEGIN {OFS=":"}{sum += $3} END {printf "%d:%d\n",sum,sum/NR}'
```
