##### リスト内包表記

``` python
# リスト内包表記
L = [i for i in range(1000000)]

# if形式
L = [i if i % 2 == 0 else i**2 for i in range(10)]
```

##### LRUキャッシュ使用

``` python
# @lru_cacheを使うと同じ引数での関数呼び出しがキャッシュを読む

@lru_cache(maxsize=None)
def calc_add(x, y):
  retrun x+y
```

##### ジェネレート関数

``` python
#yield あり
def iterate(number):
    for i in range(number):
        yield i * 2
```

##### マルチプロセス

``` python
def _sleep(n: int) -> int:
     time.sleep(n)
     return n


def _current_calcuration(cores: int):
     numbers = [1, 2, 3, 4]
     with concurrent.futures.ProcessPoolExecutor(max_workers=cores) as executor:
         results = executor.map(_sleep, numbers)
         for result in results:
             print(result,datetime.datetime.now())
```
