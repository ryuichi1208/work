### アーキテクチャ

- Pod
  - 1つ以上のコンテナで作られる
  - 1つずつIPアドレスを所持する
- Replicaset
  - Podを複数へまとめたもの
- Deployment
  - 1つ以上のReplicasetを管理する単位

- Servise (レイヤー4)
  - Podの起動停止に合わせてサービスディスカバリ
  - Podあてのトラフィックをロードバランシング
  - クラスタ内DNSへの自動登録
- Ingress (レイヤー7)
  - HTTPSレイヤーのロードバランサー

``` yaml
apiVersion: extensions/v1beta1
kind: Ingress
metadata:
  name: test
spec:
  tls:
  - secretName: foo-bar-tls
    hosts:
    - foo.bar.com
  rules:
  - host: foo.bar.com
    http:
      paths:
      - backend:
          serviceName: s1
          servicePort: 80
  - host: bar.foo.com
    http:
      paths:
      - backend:
          serviceName: s2
          servicePort: 80
```
