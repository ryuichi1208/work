#!/bin/bash


PROGNAME=$(basename $0)
VERSION="1.0"
HELP_MSG="'$PROGNAME -h'と指定することでヘルプを見ることができます"

# ヘルプメッセージ
usage() {
  echo "Usage: $PROGNAME -a arg [-b arg] param"
  echo 
  echo "オプション:"
  echo "  -h, --help"
  echo "      --version"
  echo "  -a, --long-a <ARG>     <必須>"
  echo "  -b, --long-b <string>  [任意] *オプション指定時は引数を設定"
  echo "  -c, --long-c           オプション指定のみ"
  echo
  exit 1
}

# オプション解析
for OPT in "$@"
do
  case "$OPT" in
    # ヘルプメッセージ
    '-h'|'--help' )
      usage
      exit 1
      ;;
    # バージョンメッセージ
    '--version' )
      echo $VERSION
      exit 1
      ;;
    # オプション-a、--long-a
    '-a'|'--long-a' )
      FLG_A=1
      if [[ -z "$2" ]] || [[ "$2" =~ ^-+ ]]; then
        echo "$PROGNAME:「$1」オプションには引数が必要です" 1>&2
        exit 1
      fi
      ARG_A="$2"
      shift 2
      ;;
    # オプション-b、--long-b
    '-b'|'--long-b' )
      FLG_B=1
      if [[ -z "$2" ]] || [[ "$2" =~ ^-+ ]]; then
        echo ARG_B 1
        shift
      else
        echo ARG_B 2
        ARG_B="$2"
        shift 2
      fi
      ;;
    # オプション-c
    '-c'|'--long-c' )
      FLG_C=1
      shift 1
      ;;
    '--'|'-' )
      shift 1
      param+=( "$@" )
      break
      ;;
    -*)
      echo "$PROGNAME: 「$(echo $1 | sed 's/^-*//')」オプションは存在しません。'$PROGNAME -h'で確認してください" 1>&2
      exit 1
      ;;
    *)
      if [[ ! -z "$1" ]] && [[ ! "$1" =~ ^-+ ]]; then
        param+=( "$1" )
        shift 1
      fi
      ;;
  esac
done

if [ -z $FLG_A ]; then
  echo "$PROGNAME:「-a」オプションは必須です。正しいオプションを指定してください" 1>&2
  echo $HELP_MSG 1>&2
  exit 1
fi

if [ -z $param ]; then
  echo "$PROGNAME:コマンド 引数がありません。正しい引数を指定してください" 1>&2
  echo $HELP_MSG 1>&2
  exit 1
fi

LOG()
{
  # ログファイル
  LOG_DATE=`date '+%Y-%m-%d'`
  LOG_TIME=`date '+%H:%M:%S'`
  LOGFILE="${LOG_DATE}_test.log"

  # 引数展開
  FILENM=`basename $0`
  TITLE=$1
  MSG=$2

  # ログ出力実行
  printf "%-10s %-8s %-14s %-50s\n" \
  "${TITLE} ${LOG_DATE}" "${LOG_TIME}" "${FILENM}" "${MSG}" >>${LOGFILE}
}
