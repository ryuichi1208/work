#### tmpfsをコンテナ内へマウントする

```
$ docker container run -it --mount type=tmpfs,dst=/tmpfs,tmpfs-mode=1770 centos:7.6 /bin/bash
```

#### ホストOSノディレクトリを書き込み不可でマウント

```
$ docker container run -it --mount type=volume,src=src,dst=/home/dst,readonly
```

#### コンテナの状態の特定要素を取得

```
$ docker container inspect RB_rest --format='{{.State.Status}}'
```
