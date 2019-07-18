##### 小技集

``` python
# 引数の型を指定、戻り値はint
def is_int(s : str) -> int:
    try:
        num = int(s)
    except ValueError as e:
        print(e)
        return 1
    return 0

# リストのインデックスを同時に取得
L = ["aaa", "bbb", "ccc"]
for i,st in enumerate(L):
     print(i, st)

# 寄せ
print('left  : {:<10}'.format(100))
print('center: {:^10}'.format(100))
print('right : {:>10}'.format(100))
# left  : 100
# center:    100
# right :        100

# 0埋めprint('zero padding: {:0=10}'.format(100))
print('zero padding: {:010}'.format(100))
# zero padding: 0000000100
# zero padding: 0000000100

print('zero padding: {:0=10}'.format(-100))
print('zero padding: {:010}'.format(-100))
# zero padding: -000000100
# zero padding: -000000100

# ZIPで埋め合わせ
names = ['Alice', 'Bob', 'Charlie', 'Dave']
ages = [24, 50, 18]

for name, age in zip(names, ages):
    print(name, age)
# Alice 24
# Bob 50
# Charlie 18
```

#### バイトコードを読む

``` python
import dis

def func1(a: int, b: str):
    print(f'{a:10}')
    print(sum(20, 30))

dis.dis(func1)
```

#### 読み方

```
  5           0 LOAD_GLOBAL              0 (print)
              2 LOAD_FAST                0 (a)
              4 LOAD_CONST               1 ('10')
              6 FORMAT_VALUE             4 (with format)
              8 CALL_FUNCTION            1
             10 POP_TOP

  6          12 LOAD_GLOBAL              0 (print)
             14 LOAD_GLOBAL              1 (sum)
             16 LOAD_CONST               2 (20)
             18 LOAD_CONST               3 (30)
             20 CALL_FUNCTION            2
             22 CALL_FUNCTION            1
             24 POP_TOP
             26 LOAD_CONST               0 (None)
             28 RETURN_VALUE
```
