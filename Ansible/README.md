##  Ansible

[ansible/ansible](https://github.com/ansible/ansible)

## モジュール

#### base.yml

``` yaml
- hosts: linux
  gather_facts: no
  become: yes
  
  # 変数
  vars:
    document_root: "/var/www/html"
    httpd_conf: "/etc/httpd/conf/httpd.conf"
```

#### 便利系

``` yaml
# ipアドレスを取得
 - name: get remote host ip address
   command: echo {{ ansible_eth0.ipv4.address }}

# sleep
  - name: pause
    pause:
      seconds: 5

# リブート
    - name: restart machine
      shell: sleep 2 && shutdown -r now
      async: 1
      poll: 0
      become: true
      ignore_errors: true

    - name: wait for reboot
      wait_for_connection:
        delay: 30
        timeout: 300

    - name: connect check
      ping:
      
# SELinux off
- name: SELinuxの無効化
  selinux: state=disabled
  register: selinux
```

#### if系

|     |対象が<br>ファイル|対象が<br>ディレクトリ|対象が<br>存在しない|
|:----|:--------------|:-----------------|-----------|
|chk_file.stat.isreg == true|実行|スキップ|失敗|
|chk_file.stat.isdir == true|スキップ|実行|失敗|
|chk_file.stat.exists == true|実行|実行|スキップ|
|chk_file.stat.exists == true and chk_file.stat.isreg == true|実行|スキップ|スキップ|
|chk_file.stat.exists == true and chk_file.stat.isdir == true|スキップ|実行|スキップ|

#### yum

``` yaml
  tasks:
    - name: ensure a list of packages installed
      yum:
        name: "{{ packages }}"
      vars:
        packages:
          - git
          - wget

# パッケージ削除
- name: remove the Apache package
  yum:
    name: httpd
    state: absent

# すべてのパッケージをアップグレードする
- name: upgrade all packages
  yum:
    name: '*'
    state: latest
```

#### file

``` yaml
# ファイル作成 / パーミッション変更
  tasks:
    - file:
        path: /etc/foo.conf
        owner: kingyo
        group: kingyo
        # when specifying mode using octal numbers, add a leading 0
        mode: 0644

# ディレクトリ作成
  tasks:
    - file:
        path: /etc/some_directory
        state: directory
        mode: 0755

# ディレクトリ削除
  tasks:
    - file:
        path: /etc/foo.conf
        state: absent
```

#### template

``` yaml
# 管理対象ホストへローカルから転送
- name: Copy(template) Config File
  template:
    src: httpd.conf
    dest: /etc/httpd/conf
    mode: 0644
    backup: yes
```

#### replace

``` yaml
- name: "設定の修正"
  replace: >-
    dest='/path/to/file'
    regexp='AllowOverride None'
    replace='AllowOverride All'
    
# 行削除
  tasks:
    - lineinfile:
        path: /etc/sudoers
        state: absent
        regexp: '^%wheel'
```

#### その他

```
# git
- git: repo=ssh://git@github.com/mylogin/hello.git dest=/home/mylogin/hello

# get_url
- get_url: url=http://example.com/path/file.conf dest=/etc/foo.conf mode=0440
```
