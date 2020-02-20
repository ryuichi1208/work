## Python Tips

### スニペット

``` python
from collections import defaultdict, deque
from heapq import heappush, heappop
from bisect import bisect_left, bisect_right
from fractions import gcd

import sys
import random
import itertools
import math
sys.setrecursionlimit(10**6)
```

### 基本

#### 入力系

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

#### ソート系

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

#### 最大/最小値

``` python
# 多次元配列のキーを指定した最大/最小値
max(l, key=lambda x:x[1])
max(l, key=lambda x:x[1])

# 辞書(キーの最大値)
max(k)

# 辞書(値の最大値)
max(k.values())

# 値が最大値となるときのキーと値を同時に取得
max_kv = max(d.items(), key=lambda x: x[1])
```

#### ライブラリ

``` python
# 優先度付きキュー
## 最小値（最大値）をO(logN)で取り出す

## キャスト
heapq.heapify(リスト)

## 最小値取り出し
heapq.heappop(優先度付きキュー)

## キューへ要素を挿入
heapq.heappush(優先度付きキュー)

## 最大値を取り出す際は全ての要素へ「-1」をかける
list(map(lambda x: x*(-1), a))

# キュー/スタック/デック
# 両端操作がO(1)で可能

```

### 数学系

#### 基本形

``` python
# 切り上げ/切り捨て
math.ceil(num)
math.floor(num)

# 逆関数(角度算出)
math.degrees(math.asin(1))
math.degrees(math.acos(1))
math.degrees(math.atan(1))

# 最大公約数(gcd)
gcd(x, y)

# 最小公倍数(lcm)
(x * y) // gcd(x, y)

# リストの最小公倍数 -> int
def lcm(lst):
    from fractions import gcd
    x = a[0]
    for i in range(1, len(a)-1):
        x = (x * a[i]) // gcd(x, a[i])
    return x

# 約数のリストを生成 -> list
def make_divisors(n):
    div = []
    for i in range(1, int(n**0.5)+1):
        if n % i == 0:
            div.append(i)
            if i != n // i:
                div.append(n//i)
    return div


# 素因数分解のリスト -> list
def prime_decomposition(n):
    i = 2 ; table = []
    while i * i <= n:
        while n % i == 0:
            n //= i ; table.append(i)
        i += 1
    if n > 1:
      table.append(n)
    return table


# 素数判定 -> boolean
def is_prime(n):
    for i in range(2, n + 1):
        if i * i > n:
            break
        if n % i == 0:
            return False
        return n != 1


# フィボナッチ数列 -> list
def fib(n):
    a, b = 0, 1
    for i in range(n):
        a, b = b, a + b
    return b


# 素数のリストを取得 -> list
def get_prime_number(num):
    primes = set(range(2, num+1))
    for i in range(2, int(num**0.5+1)):
        primes.difference_update(range(i*2, num+1, i))
    return list(primes)
```

#### 順列/組み合わせ

``` python
# 順列(Permutation):重複選択有
list(itertools.permutations(seq, 3))


# 組み合わせ(Combinations)
list(itertools.combinations(seq,3))


# 累積和
list(itertools.accumulate(l))


# 累積和(積)
list(itertools.accumulate(l), operator.mul)
```


#### DP

``` python
# 任意の個数の最大
def max_sum(N,a):
  dp=[0]*(N+1)
  for i in range(N):
    dp[i+1]=max(dp[i],dp[i]+a[i])
  return dp[N]

# 任意の個数の最小
def min_sum(N,a):
  dp=[0]*(N+1)
  for i in range(N):
    dp[i+1]=min(dp[i],dp[i]+a[i])
  return dp[N]
 ```
