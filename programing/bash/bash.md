#### 特殊変数

$#	実行時に指定された引数の数を表す変数
$@	シェルスクリプト実行時、もしくは set コマンド実行時に指定された全パラメータが設定される変数。
$*	シェルスクリプト実行時、もしくは set コマンド実行時に指定された全パラメータが設定される変数。
$0	実行時のコマンド名が設定される変数。

#### 実行ユーザがrootかどうか

``` bash
if [[ $(whoami) == 'root' ]] ; then
  echo user root
else
  echo user is not root
fi
```

#### オプション解析

``` bash
while getopts ab:c: OPT
do
  case $OPT in
    "a" ) FLG_A="TRUE" ;;
    "b" ) FLG_B="TRUE" ; VALUE_B="$OPTARG" ;;
    "c" ) FLG_C="TRUE" ; VALUE_C="$OPTARG" ;;
  esac
done
```

#### 文字列が含んでいるか確認

``` bash
if [ "`echo $STR | grep HOGE`" ]; then echo 'FOUND!!!'; fi

tel='09012345678'

if [[ $tel =~ [0-9]{3}-?[0-9]{4}-?[0-9]{4} ]] ;
then
  echo match
fi
```

#### usageの書き方

``` bash
function usage() {
cat <<_EOT_
Usage:
  $0 [-a] [-b] [-f filename] arg1 ...

Description:
  hogehogehoge

Options:
  -a    aaaaaaaaaa
  -b    bbbbbbbbbb
  -f    ffffffffff

_EOT_
exit 1
}
```
