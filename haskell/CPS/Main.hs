{-# LANGUAGE BangPatterns #-}
-- practice for CPS
-- http://pllab.is.ocha.ac.jp/zemi_2.html
import           Control.Monad.State
import           Data.List


fact :: Int -> Int
fact 0 = 1
fact n = n * fact (n-1)

-- tail-recursible
fact' :: Int -> Int -> Int
fact' 0 ans = ans
fact' n ans = fact' (n-1) (n*ans)

power :: Int -> Int -> Int
power 0 x = 1
power n x = x * power (n-1) x

--tail-recursible
power' :: Int -> Int -> Int -> Int
power' 0 x ans = ans
power' n x ans = power' (n-1) x (x*ans)

fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = fib (n-1) + fib (n-2)

-- tail recursive by using accumulator agument for state passing
fib' n = go n (0,1)
  where
    go !n (!a, !b) | n==0      = a
                   | otherwise = go (n-1) (b, a+b)

-- Monadic style
fibM n = flip evalState (0,1) $ do
  forM [0..(n-1)] $ \_ -> do
    (a,b) <- get
    put (b,a+b)
  (a,b) <- get
  return a

fibs = 0 : (go 0 1)
  where go a b = b : go b (a+b)

-- tail recursive
fib1 :: Int -> Int
fib1 n = go n 0 1 -- ここの1の位置のアキュムレータを更新しつつ，最後にアキュムレータを返す関数go
  where go :: Int -> Int -> Int -> Int -- クロージャ
        go 0 a b = a -- n = 0 の時だけここが評価される
        go 1 a b = b -- n>1のときはここで止まる
        go n a b = go (n-1) b (a+b) -- ここの(a+b)の位置の値がアキュムレータ

hello :: Bool -> String
hello loud = "Hello"

mean :: [Double] -> Double
mean xs = s / fromIntegral l
  where
    (s, l) = foldl' step (0,0) xs
    step (!s, !l) a = (s + a, l + 1)

addCPS x y = k $ x + y
  where
    k = (\x -> x)

hoge :: (Num a, Num b) => a -> (a -> b) -> b
hoge s f = f s

zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' _ [] _          = []
zipWith' _ _ []          = []
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys

-- cps
kplus a b k = k $ a+b
-- このkplusの定義の仕方がCPS
-- kが継続

add1 :: Int -> Int -> Int
add1 x y = x + y

-- add1 のクロージャ変換(クロージャ化) add2 ~ add5
add2 :: Int -> Int -> Int
add2 x y = f
  where f = x + y -- closure
-- f は外側のadd2関数(エンクロージャ)の中で定義された一時関数(クロージャ)になる．
-- クロージャはエンクロージャより外からは参照できない
-- fからは，エンクロージャの値 x y を参照する事ができる

add3 :: Int -> Int -> Int
add3 x y = f x y
  where f a b = a + b -- 引数付きの関数としてのクロージャも作成可能

add4 :: Int -> (Int -> Int)
add4 x = f
  where
    f :: Int -> Int -- 部分適用 値を(一部)固定した関数を作ることができる
    f y = x + y     -- これもクロージャの一種

add5 :: Int -> (Int -> Int) -- add5関数の中で，引数yを取るlambda関数を返す
add5 x = (\y -> x + y) -- (\y -> x + y)これもクロージャの一種

-- クロージャを用いると，状態を保持する関数をつくることができるようになる．
derivative f delta = \x -> (f (x+delta) - f x) / delta

-- べき集合
powerSet :: [a] -> [[a]]
powerSet []     = [[]]
powerSet (x:xs) = [x:ys | ys <- powerSet xs] ++ powerSet xs
