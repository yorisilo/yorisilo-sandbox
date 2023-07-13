# Haskell 練習問題

## 準備

この練習問題では、REPL ではなくテキストエディタを使った方が良い問題がほとんどですので、次のようなスクリプトを用意しておくことをおすすめします。

```haskell
#!/usr/bin/env runghc

main :: IO ()
main = do
  print "hello"
```

`main` の詳しい意味については説明しませんが、最初のうちは `main = do` のあとに 1 つ以上の `print` を並べてください。

```haskell
#!/usr/bin/env runghc

add10 :: Int -> Int
add10 n = n + 10

main :: IO ()
main = do
  print (add10 100)
  print (add10 1000)
```


## 1

### 1-1. 簡単な演算

GHCi を利用し、C 言語の `(1 + 2 * 3) / 4` と同等な計算をしてください。

<details>
<summary>解答例</summary>

Prelude の `/` が実数のための演算子であることに注意すれば、C とほぼ同じように書くことができます。

```haskell
(1 + 2 * 3) `div` 4
```

</details>

### 1-2. 関数適用

`const` という関数の型は `const :: a -> b -> a` です。（とりあえず、型だけに注目し、関数の意味は考えないことにします）

GHCi で `const` に好きな 2 つの異なる型の値を渡し、最初に渡した値と同じ型の値が得られることを確認してください。

確認ができたら、`const` の意味を考えてみてください。

<details>
<summary>解答例</summary>

以下を実行すると `1` が得られます。

```haskell
const 1 "abc"
```

`const` は定数関数を作るための関数で、`const x` のようにしてどんな引数に対しても同じ値 `x` を返す関数を作ることができます。

今回のように引数を 2 つ与えるのは無意味です。

</details>

### 1-3. 関数の定義

文字列を 2 回繰り返すような関数 `f :: String -> String` を定義してください。（`f "abc"` が `"abcabc"` になるような関数です。）

`String` は `[Char]` の別名なので `(++) :: [a] -> [a] -> [a]` で結合が可能です。

<details>
<summary>解答例</summary>

```haskell
f :: String -> String
f s = s ++ s
```

`f :: String -> String` のような型注釈がなくてもコンパイルは可能ですが、これがあることで可読性が大幅に向上し、型検査も強力になるので、毎回書くようにすると開発効率が上がります。

</details>

### 1-4. 中置記法

以下の `isMultipleOf :: Int -> Int -> Bool` の定義で、左辺の `isMultipleOf` と右辺の `mod` を中置記法で書き直し、可読性を向上させてください。

```haskell
isMultipleOf :: Int -> Int -> Bool
isMultipleOf m n = mod m n == 0
```

<details>
<summary>解答例</summary>

```haskell
isMultipleOf :: Int -> Int -> Bool
m `isMultipleOf` n = m `mod` n == 0
```

</details>

### 1-5. 演算子

以下の `+.` に `Double -> Double -> Double` 型の型注釈を追記し、`Double` 専用の加算演算子としてください。

```haskell
m +. n = m + n
```

<details>
<summary>解答例</summary>

```haskell
(+.) :: Double -> Double -> Double
m +. n = m + n
```

</details>

### 1-6. 前置記法

前問の `+.` の定義で、`+.` と `+` を前置記法で書き直してください。

<details>
<summary>解答例</summary>

```haskell
(+.) :: Double -> Double -> Double
(+.) m n = (+) m n
```

この記法を使うと以下のように書くこともできます。

```haskell
(+.) :: Double -> Double -> Double
(+.) = (+)
```

</details>

### 1-7. if 式

`if` 式を利用し、与えられた値が偶数なら `"even"`、奇数なら `"odd"` を返す関数 `f :: Int -> String` を定義してください。

<details>
<summary>解答例</summary>

```haskell
f :: Int -> String
f n = if n `mod` 2 == 0 then "even" else "odd"
```

</details>


## 2

### 2-1. 型

次の値の型を示してください。

コンテキスト（`Eq a =>` のような制約）が必要な場合は忘れずに記述してください。

1. `1 :: Int`
2. `1`
3. `f x = x` の `f`
4. `f x = x + 1` の `f`
5. `f x = (x :: Int) + 1` の `f`
6. `(+)`
7. `f a b c d = if a == b then c else d` の `f`
8. `s x y z = x z (y z)` の `s`

<details>
<summary>解答例</summary>

1. `Int`
2. `Num a => a`
3. `a -> a`
4. `Num a => a -> a`
5. `Int -> Int`
6. `Num a => a -> a -> a`
7. `Eq a => a -> a -> b -> b -> b`
8. `(a -> b -> c) -> (a -> b) -> a -> c`

</details>

### 2-2. 型推論

次のプログラムについて考えます。

```haskell
f :: Int -> Double
f x = fromIntegral (x + 1) + const 2 3
```

このプログラムにおける次の項の型を示してください。

1. `1`
2. `2`
3. `3`
4. `fromIntegral`
5. `const`
6. `const 2 3`

ただし、いくつかの項の型は決定できません。

<details>
<summary>解答例</summary>

1. `Int`
2. `Double`
3. 決定できない（`Int`、`Integer`、`Double` などの可能性があります）
4. `Int -> Double`
5. 決定できない（`Int -> a -> Int` までは決まりますが、`a` が決まりません）
6. `Double`

</details>

### 2-3. 型クラスのインスタンス定義

次のコードはコンパイルできません。

```haskell
print (+)
```

型 `a -> b` に対する `Show` のインスタンスを定義し、実行できるようにしてください。

実行結果は問いません。

<details>
<summary>解答例</summary>

```haskell
instance Show (a -> b) where
  show _ = "function!"
```

</details>

### 2-4. 型クラスの応用 1

型クラス `Default` を定義することで `defaultValue :: Int` は `0`、`defaultValue :: Double` は `0.0`、`defaultValue :: [a]` は `[]` になるような `defaultValue :: Default a => a` を定義してください。

また、これを利用して `if cond then 100 else 0` の代わりに `ifOrDefault cond 100` とできる（`else` を省略できる）ような `ifOrDefault :: Default a => Bool -> a -> a` を定義してください。

<details>
<summary>解答例</summary>

```haskell
class Default a where
  defaultValue :: a

instance Default Int where
  defaultValue = 0

instance Default Double where
  defaultValue = 0

instance Default [a] where
  defaultValue = []
```

```haskell
ifOrDefault :: Default a => Bool -> a -> a
ifOrDefault cond value = if cond then value else defaultValue
```

</details>

### 2-5. 型クラスの応用 2

型クラス `Default` のインスタンスを追加することで `(Int, Double)` や `(Int, [Int])`、`(Int, (Int, Int))` などの 2 要素のタプルにも対応してください。

返す値は `(0, 0.0)`、`(0, [])`、`(0, (0, 0))` のように `defaultValue` の値を入れ子にしてください。

<details>
<summary>解答例</summary>

```haskell
instance (Default a, Default b) => Default (a, b) where
  defaultValue = (defaultValue, defaultValue)
```

</details>


## 3

### 3-1. let

以下の関数 `f` で `(x - a)` が複数回現れているのを、`let` を利用して集約してください。

```haskell
f :: Num a => a -> a -> a
f a x = (x - a) ^ 3 + (x - a) ^ 2 + (x - a) + 1
```

<details>
<summary>解答例</summary>

数値と関数のどちらに注目するかで、2 通りの解答が考えられます。

```haskell
f :: Num a => a -> a -> a
f a x = let x' = x - a in x' ^ 3 + x' ^ 2 + x' + 1
```

```haskell
f :: Num a => a -> a -> a
f a x = let f' x' = x' ^ 3 + x' ^ 2 + x' + 1 in f' (x - a)
```

</details>

### 3-2. パターンマッチ

パターンマッチを利用して `...` で `fizzbuzzMod` を定義し、FizzBuzz 問題を解く関数 `fizzbuzz` を完成させてください。

```haskell
fizzbuzz :: (Integral a, Show a) => a -> String
fizzbuzz n = fizzbuzzMod (n `mod` 3) (n `mod` 5)
  where
    ...
```

`fizzbuzz` は以下のような仕様です。

- `n` が 3 の倍数のときは `"Fizz"` を返す
- `n` が 5 の倍数のときは `"Buzz"` を返す
- `n` が 15 の倍数のときは `"FizzBuzz"` を返し、`"Fizz"` や `"Buzz"` とはしない
- `n` が 3 の倍数でも 5 の倍数でもない場合は `n` を文字列化して返す

<details>
<summary>解答例</summary>

```haskell
fizzbuzz :: (Integral a, Show a) => a -> String
fizzbuzz n = fizzbuzzMod (n `mod` 3) (n `mod` 5)
  where
    fizzbuzzMod 0 0 = "FizzBuzz"
    fizzbuzzMod 0 _ = "Fizz"
    fizzbuzzMod _ 0 = "Buzz"
    fizzbuzzMod _ _ = show n
```

</details>


## 4

### 4-1. 単純な再帰

リストのすべての要素の間に指定した値を挟み込む関数 `intersperse' :: a -> [a] -> [a]` を定義してください。

この関数は以下のような動作をします。

- `intersperse' 0 []` は `[]` を返す
- `intersperse' 0 [1]` は `[1]` を返す
- `intersperse' 0 [1, 2, 3]` は `[1, 0, 2, 0, 3]` を返す
- `intersperse' ',' "abc"` は `"a,b,c"` を返す

<details>
<summary>解答例</summary>

```haskell
intersperse' :: a -> [a] -> [a]
intersperse' _ [] = []
intersperse' _ [x] = [x]
intersperse' sep (x:xs) = x : sep : intersperse' sep xs
```

</details>

### 4-2. 相互再帰

与えられた値が偶数であることを判定する関数 `isEven :: Integral a => a -> Bool` と、奇数であることを判定する関数 `isOdd :: Integral a => a -> Bool` を定義してください。

ただし、以下の法則を利用することで、剰余演算やビット演算は使わずに再帰によって定義してください。

- `0` は偶数である
- `0` は奇数ではない
- `n` が奇数なら `n + 1` は偶数
- `n` が偶数なら `n + 1` は奇数

負数について考慮する必要はありません。

<details>
<summary>解答例</summary>

```haskell
isEven :: Integral a => a -> Bool
isEven 0 = True
isEven n = isOdd (n - 1)

isOdd :: Integral a => a -> Bool
isOdd 0 = False
isOdd n = isEven (n - 1)
```

可読性は落ちますが `||` と `&&` を利用することもできます。

```haskell
isEven :: Integral a => a -> Bool
isEven n = n == 0 || isOdd (n - 1)

isOdd :: Integral a => a -> Bool
isOdd n = n /= 0 && isEven (n - 1)
```

</details>

### 4-3. 余再帰

`succ :: Enum a => a -> a` と再帰を利用し、与えられた初期値 `x` に対して `[x, succ x, succ (succ x), ...]` を返す関数 `enumFrom' :: Enum a => a -> [a]` を定義してください。

<details>
<summary>解答例</summary>

```haskell
enumFrom' :: Enum a => a -> [a]
enumFrom' x = x : enumFrom' (succ x)
```

</details>

### 4-4. 効率的な再帰

以下のプログラムは、リストを反転する関数 `reverse'` の素朴な定義です。

```haskell
reverse' :: [a] -> [a]
reverse' [] = []
reverse' (x:xs) = reverse' xs ++ [x]
```

しかし、この実装には問題があり、`xs ++ [x]` の計算量は `O(length xs)` で、`reverse' xs` 全体の計算量は `O((length xs) ^ 2)` に及び、非常に低速です。

計算量が `O(1)` の `:` のみを利用して、`reverse' xs` の効率を `O(length xs)` に改善してください。

<details>
<summary>解答例</summary>

```haskell
reverse' :: [a] -> [a]
reverse' = aux []
  where
    aux acc [] = acc
    aux acc (x:xs) = aux (x:acc) xs
```

</details>


## 5

### 5-1. ラムダ式

`let f x y = x * y + 1 in f` と等価な式をラムダ式で表現してください。

<details>
<summary>解答例</summary>

```haskell
\x -> \y -> x * y + 1
```

次のように略記することもできます。

```haskell
\x y -> x * y + 1
```

</details>

### 5-2. 高階関数

4-3 の `enumFrom'` を抽象化（汎用化）し、`succ` の代わりに `f :: a -> a` を指定できる関数 `iterate'` を定義してください。

関数 `f` と初期値 `x` のどちらを最初の引数にするのが適切かを判断し、型注釈も記述してください。

また、`iterate'` を利用して `enumFrom'` を書き直してください。

<details>
<summary>解答例</summary>

```haskell
iterate' :: (a -> a) -> a -> [a]
iterate' f x = x : iterate' f (f x)
```

初期値 `x` を固定したまま関数 `f` を取り替えたいケースはほとんどなく、関数を先に渡した方が再利用性は高くなります。

この順序を採用すると `enumFrom'` の定義も簡単で、「`enumFrom'` が `iterate'` の特殊例に過ぎない」という意味も明確になります。

```haskell
enumFrom' :: Enum a => a -> [a]
enumFrom' = iterate' succ
```

</details>
