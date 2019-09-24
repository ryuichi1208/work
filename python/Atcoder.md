## python　よく使うTips

#### 入力処理

``` python
# 1行1列
s = input()
n = int(input())
x = float(input())

# 1行 / R列
l = list(map(int, input().split()))
n, m = input().split()
n, m = map(int, input().split())

# C行 / 1列
n = int(input())
l = [input() for i in range(n)]
l = [int(input()) for i in range(n)]

# C行 / R列
n = int(input())
l = [input().split() for i in range(n)]
l = [list(map(int, input().split())) for i in range(n)]
```

#### 基本形

``` python
# カウント/要素存在性
L.count()
if ("a" in L):
if ("a" not in L):

# 正規表現(複数回使用を前提として事前コンパイル)
import re
regex = r'ab+'
text = "abbabbabaaabb"
pattern = re.compile(regex)
matchObj = pattern.match(text)

# lisnの各項へ操作
map(lambda x: x**2, L)

def add(x):
    return x + 2

map(add, [1,2,3,4])

# ビット演算

# 大文字/小文字変換
Text="this is a pen."
print(Text.upper())
print(Text.lower())
```

#### リストソート

``` python
# 昇順
l.sort()
l.sort(key=lambda x:x[1])
l.sort(key=lambda x:(x[1],x[2]))

# 特定の要素は降順へ
l.sort(key=lambda x:(x[0],-x[1]))

# 降順
l.sort(reverse=True)
l.sort(key=lambda x:x[1], reverse=True)
l.sort(key=lambda x:(x[1],x[2]) reverse=True)
```

#### 数学関連(基礎)

``` python
import math
from math import ceil,floor

# 切り上げ
math.ceil(num)

# 切り捨て
math.floor(num)

# 絶対値
abs(num)

# 最大値/最小値
max(l)
max(l, key=lambda x:x[1])
min(l)
max(l, key=lambda x:x[1])

# 整数の商と余りを同時取得
a, b = divmod(10, 3)
```

#### 数学関連(応用)

``` python
# 平均値
def avg(l):
    return sum(l)/len(l)

# 最大公約数
def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

# 最小公倍数
def lcm(a, b):
    return a * b // gcd (a, b)

# フィボナッチ数列
def fib(n):
    a, b = 0, 1
    for i in range(n):
        a, b = b, a + b
    return b

# 約数の列挙
def prime_decomposition(n):
  i = 2
  table = []
  while i * i <= n:
    while n % i == 0:
      n /= i
      table.append(i)
    i += 1
  if n > 1:
    table.append(n)
  return table

# 素因数分解
def is_prime(n):
    for i in range(2, n + 1):
        if i * i > n:
            break
        if n % i == 0:
            return False
    return n != 1

# 素数リスト取得
def get_prime_number(num):
    primes = set(range(2, num+1))
    for i in range(2, int(num**0.5+1)):
        primes.difference_update(range(i*2, num+1, i))
    return list(primes)

print(get_prime_number(100))
```

#### 累積和/動的計画法

``` python
# 累積和
L = [1, 4, 5, 9, 2, 3]
s = [0]

for i,a in enumerate(L):
    s.append(s[i]+a)

ans = 0
for i in range(len(L)-2):
    ans = max(ans, s[i+2]-s[i])

print(s)
print(ans)

#DP1
n=6
w=8
weight=[2,1,3,2,1,5]
value=[3,2,6,1,3,85]

dp=[[0 for i in range(w+1)] for j in range(n+1)]
for i in range(n):
    for j in range(w+1):
        if j>=weight[i] : dp[i+1][j]=max(dp[i][j-weight[i]]+value[i],dp[i][j])
        else: dp[i+1][j]=dp[i][j]
    print(dp[:i+2])
print(dp[n][w])
```

#### Que/優先付きQue

``` python
import heapq

# ヒープキューへ値追加
heapq.heappush(heap, item)

# ヒープキューから値取得
heapq.heappop(heap)
```

#### DP

``` python
def max_sum(N,a):
  dp=[0]*(N+1)
  for i in range(N):
    dp[i+1]=max(dp[i],dp[i]+a[i])
  return dp[N]
```

#### 内包表記

``` python
# 偶数のリスト
[i for i in range(10) if i%2==0]

# 辞書内包表記
{str(i):i for i in range(10)}

# zipと連携
label = ["kinoko", "takenoko", "suginoko"]
feature = ["yama", "sato", "mura"]
{i:j for i,j in zip(label,feature)}
#>>> {'kinoko': 'yama', 'suginoko': 'mura', 'takenoko': 'sato'}

# key value 反転
{value:key for key,value in D.items()}
```

#### ディレクトリ構成

##### 同じディレクトリにあるファイル
```
.
├── brother.py
└── main.py
```

```brother.py
def hi():
    print("Hi! I'm your brother.")
```

```main.py
import brother
brother.hi()
```


##### ひとつ下のディレクトリにある個別のファイル
```
.
├── children
│   └── tom.py
└── main.py
```

```tom.py
def hi():
    print("Hi! I'm Tom.")
```

``` python
from children import tom
tom.hi()

import children.tom
children.tom.hi()
```

##### jsonの文字列だけを取り出す

``` python
data = [
   "a",
   ["b", 1, [[["c", 2], 3], 4], "d"],
   ["e"]
]

def get_str(arg, type_instance):
    str_res = []
    int_res = []
    if isinstance(arg, str):
        str_res.append(arg)
    if isinstance(arg, int):
        int_res.append(arg)
    if isinstance(arg, list):
        for item in arg:
            res = get_str(item, type_instance)
            str_res += res
            int_res += res
    if type_instance == "int":
        return int_res
    else:
        return str_res

if __name__ == "__main__":
    print(get_str(data,"str"))
```

##### Labda

``` python
# 配列の各項を2乗
l = [i for i in range(10)]
print(list(map(lambda x :x**2,l)))
```

##### アスタリスク

``` python
# 「*」を使った呼び出し
# 「*」を使用して関数を呼び出すと変数がアンパックして呼び出される
# 関数定義として使用すると以降は可変長引数として受け取りタプルとして
def func(n1, n2, n3, *n4):
    print(n1, n3, n4) #=> 1 3 (4, 5)

L = [1,2,3,4,5]
func(*L)
```

##### 累積和(簡易版)

``` python
from itertools import *

L = [110, 20, 30, 40, 250, 20, 40, 90, 20, 10, 1110]
K = list(accumulate(L))
K.insert(0, 0)

ans = 0
for i in range(len(K)-3):
    if ans < K[i+3] - K[i]:
        ans = K[i+3] - K[i]

print(ans)
```
