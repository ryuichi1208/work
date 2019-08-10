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
