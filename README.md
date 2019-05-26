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
