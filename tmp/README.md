### 既存のssh keyを確認する

```
jenkins@6c6fd35a9dba:~/workspace$ ls -l ~/.ssh/
total 20
-rw------- 1 jenkins jenkins 1675 Aug  8 13:57 id_rsa
-rw-r--r-- 1 jenkins jenkins  402 Aug  8 13:57 id_rsa.pub
-rw-r--r-- 1 jenkins jenkins 1768 Aug  8 14:20 known_hosts
```

### Jenkinsユーザで鍵を生成する

```
# 鍵生成
$ ssh-keygen -t rsa
(省略)
# 名前が衝突しないように設定する
Enter file in which to save the key (/var/jenkins_home/.ssh/id_rsa): /var/jenkins_home/.ssh/id_rsa_jenkins
# パスフレーズはjenkinsで統一
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
(省略)

# 鍵が生成されていることを確認
$ ls -l ~/.sss/*jenkins*
-rw------- 1 jenkins jenkins 1766 Aug  8 14:15 /var/jenkins_home/.ssh/id_rsa_jenkins
-rw-r--r-- 1 jenkins jenkins  402 Aug  8 14:15 /var/jenkins_home/.ssh/id_rsa_jenkins.pub

# 公開鍵をGitの適当なリポジトリへ登録
$ cat /var/jenkins_home/.ssh/id_rsa_jenkins.pub
```

### GitHubへ登録

(省略)

### Gitサーバをknown_hostsへ登録

```
$ ssh -i ~/.ssh/id_rsa_jenkins -T git@github.com
# パスフレーズは前項で指定したものを入力
$ ssh -i ~/.ssh/id_rsa_jenkins -T git@github.com
Enter passphrase for key '/var/jenkins_home/.ssh/id_rsa_jenkins':
Hi ryuichi1208/lodge! You've successfully authenticated, but GitHub does not provide shell access.
```

### Jenkinsへリポジトリを登録

(省略)
