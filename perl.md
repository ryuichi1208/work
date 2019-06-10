# Perl よく使うTips

### 三項サイト

- [perldoc.jp](https://perldoc.jp/)
- [Perl入門ゼミ](https://tutorial.perlzemi.com/)
- [(GitHub)[Perl/perl5]](https://github.com/Perl/perl5)
- [(GitHub)[AnaTofuZ]](https://github.com/AnaTofuZ)
- [(GitHub)[OGATA Tetsuji]](https://github.com/xtetsuji)
- [(GitHub)[Nobutaka Wakabayashi]](https://github.com/nqounet)

### 基礎

##### スカラ変数

``` perl
# 数値
my $num = 20;

# 文字列
my $str = "aaa";

# リファレンス
my $ref = \$num;

# デリファレンス
my $num = $$ref
```

##### 配列

``` perl
# 基本
my @arr = (1, 2, 3, 4, 5);

# 要素数取得
my $arr_num = $arr;

# 先頭取得
my $first = shift @arr;

# 先頭へ要素追加
unshift @arr, 123;

# 要素取得
$arr[1];

# 昇順並び替え
@arr = sort {$a <=> $b} @arr;

# 逆順へ
@arr = reverse @arr;

# リファレンス
my $ref = \@arr;

# デリファレンス
my @arr = $@arr;

# 要素ループ
forearch (@arr) {
  print;
}

# 無名配列へのリファレンス
my @arr_ref = [1, 2, 3, 4];

# 無名配列参照
my $arr_ref->[0]

# grepで任意の要素取り出し
my @arr = (10, 20, 30.0, 40);
my @arr = grep {/^\d+/} @arr;
##=> 10, 20, 40
```

##### ハッシュ

``` perl
# 初期化
my %hash = (a=>20, b=>30, c=>40);

# 要素取得
$hash{'a'};

# 要素代入
$hash{'d'} = 50;

# すべてのキーを取得
my @keys = keys %hash;

# すべての値を取得
my @valuse = values %hash;

# すべてのキーと値を取得
# (キー, 値)のペアを順番に取得
my %age = (Ken => 19, Mike => 34);
while (my ($name, $age) = each %age) {
  ...
}

# リファレンス
my $ref = \%hash;

# ハッシュのリファレンスから要素にアクセス
$ref->{a};
#複雑だと $ref->{a}->{b}->methof(\@arr);のような

# デリファレンス
my %hash = %$ref;

# ハッシュスライス
@age{ qw(tom mike kent nancy) } = (21,19,25,17);

# ハッシュネスト
%hash = (
    A => { a => 1, b => 2, c => 3 },
    B => { d => 4, e => 5, f => 6 },
);

foreach my $tmp ( keys %hash ) {
    while ( my ($key, $val) = each %{$hash{$tmp}} ) {
        print "$key : $val\n";
    }
}
```

##### ループ

``` perl
next # ループをスキップ
last # ループを終了
redo # ループを先頭の位置までやり直す
```

##### 三項演算子

``` perl
$age = 18;
print $age >= 20 ? "成人\n" : "未成年\n";
```
