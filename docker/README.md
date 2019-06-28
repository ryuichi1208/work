index.docker.ioから指定したイメージを取り込む

```bash
docker pull REPOSITORY[:TAG]
docker image pull REPOSITORY[:TAG]
```

イメージ一覧を得る

```bash
docker images
docker image list
```

イメージからコンテナを起動する

```bash
docker run -itd IMAGE
docker container run -itd IMAGE
```

イメージからコンテナを起動して、接続する。コンテナに名前をつける

```bash
docker run -it IMAGE bash
docker container run -it IMAGE bash

docker run -it --name NAME IMAGE bash
docker container run -it --name NAME IMAGE bash
```

ホストの/var/wwwを、コンテナ内の/var/htmlからアクセスできるように共有する

```bash
docker run -it -v /var/www:/var/html IMAGE bash
docker container run -it -v /var/www:/var/html IMAGE bash
```

ホスト8080番portへの通信をコンテナ80番portへ転送する

```bash
docker run -it -p 8080:80 IMAGE bash
docker container run -it -p 8080:80 IMAGE bash
```
ゲストのPRIVATE_PORTに指定したPortがホストのどのPortにポートフォワードしてるかを調べる

```bash
docker port CONTAINER
docker container port CONTAINER

docker port CONTAINER PRIVATE_PORT
docker container port CONTAINER PRIVATE_PORT
```

イメージからコンテナを作る

```bash
docker create IMAGE
docker container create IMAGE


docker create IMAGE
docker container create --name NAME IMAGE
```

コンテナを起動する

```bash
docker start CONTAINER
docker container start CONTAINER
```

コンテナを停止する

```bash
docker stop CONTAINER
docker container stop CONTAINER
```

コンテナを再起動する

```bash
docker restart CONTAINER
docker container restart CONTAINER
```

コンテナを削除する


```bash
docker rm CONTAINER [CONTAINER...]
docker CONTAINER rm CONTAINER [CONTAINER...]
```

コンテナをすべて削除する

```bash
docker rm $(docker ps -aq)
```

イメージを削除する

```bash
docker rmi IMAGE [IMAGE...]
```

タグなしのイメージをすべて削除する

```bash
docker rmi $(docker images | grep '<none>' | awk '{print$3}')
```

起動しているコンテナに接続する

```bash
# exitするとコンテナが終了してしまう
# コンテナを終了せずに抜ける「Ctrl + p, Ctrl + q」
docker attach CONTAINER

# exitしてもコンテナは終了しない
docker exec -it CONTAINER /bin/bash
```

リポジトリにタグを貼る（:TAGを省略すると、latestになる）

```bash
docker tag IMAGE REPOSITORY[:TAG]
```

./にあるDockerfileをビルドして、イメージを作成する

```bash
docker build  ./
docker build -t REPOSITORY[:TAG] ./
```

ビルドを最初からやりなおす

```bash
docker build --no-cache .
```

起動中のコンテナ一覧を得る

```bash
docker ps
docker container list
```

指定したコンテナ名にマッチした一覧を得る

```bash
docker container list -f "Name=<container_name>"
docker container list -f "Name=<container_name_prefix>*"
```

停止中のコンテナも含めすべての一覧を得る

```bash
docker ps -a
docker container list -a
```

コンテナのハッシュリストを得る

```bash
docker ps -aq
docker container list -aq
```

コンテナのサイズを得る

```bash
docker ps -s
docker container list -s
```

hub.docker.comからイメージを検索する

```bash
docker search TERM
```

イメージをビルドした際のコマンドリストを得る。Dockerfileに記述したもののみ

```bash
docker history IMAGE
```

イメージをファイル出力する

```bash
docker save IMAGE > filename.tar
```

ファイルをイメージとして取り込む

```bash
docker load < filename.tar
```

コンテナをファイル出力する

```bash
docker export CONTAINER > filename.tar
```

コンテナからイメージを作成する

```bash
docker commit CONTAINER REPOSITORY[:TAG]
```

URLを指定してイメージを取り込む

```bash
docker import url REPOSITORY[:TAG]
```

ファイルからイメージを取り込む

```bash
cat filename.tar | docker import - REPOSITORY[:TAG]
```

コンテナの標準出力を見る

```bash
docker logs CONTAINER
```

コンテナ内のファイルをホストにコピーする

```bash
docker cp CONTAINER:filename ./
```

イメージがコンテナ化されてから変更されたファイル差分を得る

```bash
docker diff CONTAINER
```

URLのファイルをイメージ内のPATHに生成する

```bash
docker insert IMAGE URL PATH
```

コンテナの実行中のプロセス一覧を見る

```bash
docker top CONTAINER
```

dockerの現在インストールしているバージョンと最新のバージョンを得る

```bash
docker version
```

コンテナ内のイベントを監視する（コンテナが作られた、起動した、停止したなど)

```bash
docker events
```

コンテナの詳細な情報を得る。formatオプションで情報の絞り込みができる

```bash
docker inspect CONTAINER
docker inspect CONTAINER --format '{{ json . }}'
```

コンテナ内でコマンドを実行する

```bash
docker exec CONTAINER コマンド
docker exec CONTAINER bash -c "コマンド"
```

イメージ、コンテナ、ボリュームで消費しているファイルサイズを確認する

```bash
docker system df --verbose | grep -B -1 'Build cache usage'
```

CPU使用率、メモリ使用量などを確認する

```bash
docker stats
```
