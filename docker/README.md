## Dockerとは

#### 概要

コンテナ型の仮想環境を作成、配布、実行するためのプラットフォーム。
Dockerは、Linuxのコンテナ技術を使っている(namespace, cgroups, overlayfsなど)
dotCloud社（現Docker社）が開発

#### 用語

- Docker Engine
  - Dockerを利用するための常駐プログラム
-  イメージ(Image)
  - コンテナ(=アプリケーションの実行環境)を起動するのに必要な設定ファイルをまとめたもの
- コンテナ
  - イメージからコンテナを起動する

###### docker run オプション

``` bash
docker run [オプション] イメージ[:タグ|@ダイジェスト値] [コマンド] [引数...]

# コンテナ名を指定
docker run --name "test" centos

# バックグランド実行
docker run -d centos

# コンソールに結果を出力
docker run -it --name "test" centos /bin/cal

# ポートフォワーディング
docker run -d -p 8080:80 httpd

# ホスト名とIPを指定
docker run -it --add-host=test.com:192.168.1.1 centos

# DNSサーバを指定
docker run --dns=192.168.1.1 httpd

# ボリュームマウント
docker run -v $(pwd):/var/www/html httpd

# 環境変数を指定
docker run -it -e foo=bar centos /bin/bash

# WORKDIR指定
docker run -it -w=/tmp/work centos /bin/bash
```

###### 稼働中のコンテナ操作

``` bash
# コンテナ一覧
docker ps [オプション]

# コンテナのステータスを表示
docker stats コンテナID

# コンテナ起動
docker start コンテナID

# コンテナ停止
docker stop コンテナID

# コンテナ再起動
docker restart コンテナID

# コンテナ削除
docker rm コンテナID

# コンテナ一括削除
docker rm $(docker ps -a -q)

# 古いコンテナを一括削除
docker ps -a | grep 'weeks ago' | awk '{print $1}' | xargs docker rm

# イメージの一括削除
docker rmi $(docker images -a -q)
```

###### ローカルにあるDockerイメージを確認したい

``` bash
docker images [オプション名] [リポジトリ名]

# ローカル環境のDockerイメージの一覧表示
docker images
# ローカル環境のDockerイメージのダイジェスト表示
docker images --digests asashiho/dockersample
```

###### イメージをDockerHubからダウンロード

``` bash
docker pull [オプション] イメージ名[:タグ名]

# CentOSのDockerイメージ取得
docker pull centos:7
# CentOSのすべてのタグのDockerイメージ取得
docker pull -a centos
# 取得先URLを指定してCentOSのDockerイメージ取得
docker pull registry.hub.docker.com/centos:7
```

###### イメージの詳細情報を取得

``` bash
docker inspect [オプション] コンテナ識別子またはイメージ識別子 [コンテナ識別子またはイメージ識別子]

# Dockerイメージの詳細表示
docker inspect centos
# OS情報の取得
docker inspect --format="{{.Os}}" centos
```

###### Dockerfileからイメージを作成

``` bash
docker build -t [イメージ名]:[タグ名] [Dockerfileのあるディレクトリパス]
```
