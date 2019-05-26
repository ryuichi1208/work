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

#### リストソート

``` python
# 昇順
l.sort()
l.sort(key=lambda x:x[1])
l.sort(key=lambda x:(x[1],x[2]))

# 降順
l.sort(reverse=True)
l.sort(key=lambda x:x[1], reverse=True)
l.sort(key=lambda x:(x[1],x[2]) reverse=True)
```

#### 数学関連(基礎)

``` python
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
# 最大公約数
def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

# 最小公倍数
def lcm(a, b):
    return a * b // gcd (a, b)

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
```

#### 累積和/動的計画法

``` python
# 累積和
a=list(range(1,30))
a2=[0]
for i in a:a2.append(a2[-1]+i)

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
