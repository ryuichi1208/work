## よく使うライブラリ

[Requests](https://2.python-requests.org/en/master/)
[Beautiful Soup](https://www.crummy.com/software/BeautifulSoup/bs4/doc/)
[Selenium](https://kurozumi.github.io/selenium-python/)

## 基本形

``` python
import requests
from bs4 import BeautifulSoup as bs

# スクレイピング対象のURL
url = "https://news.livedoor.com/"

# URLからHTMLを取得
html = requests.get(url).text

# BeautifulSoupで扱えるようにパース
soup = bs(html, "lxml")
```

## requests

``` python
# GET
requests.get('URL')

# POST
requests.post('URL')

# PUT
requests.put('URL')

# DELETE
requests.delete('URL')

# header の取得
requests.head('URL')

# リクエストに情報を入れる
payload = {'key1': 'value1', 'key2': 'value2'}
r = requests.get('URL', params=payload)

# レスポンスをjsonで取得
requests.get('http://ci.nii.ac.jp/ncid/BB08796640.json').json()
```

## BSライブラリ

``` python
# クラスを指定して特定のタグ要素を全て取得
soup.find_all("ul", attrs={"class", "list-main-news"})

# 
```
