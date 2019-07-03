##  Ansible

[ansible/ansible](https://github.com/ansible/ansible)

## モジュール

#### base.yml

```
- hosts: linux
  gather_facts: no
  become: yes
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

```
  tasks:
    - name: ensure a list of packages installed
      yum:
        name: "{{ packages }}"
      vars:
        packages:
          - git
          - wget
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
