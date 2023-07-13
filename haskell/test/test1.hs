{- test1.hs -}
fact :: Integer -> Integer
fact 0 = 1
fact n = n * fact (n-1)

double :: Integer -> Integer
double x = x * x

rev :: [a] -> [a]
rev [] = []
rev (x:xs) = rev xs ++ [x]

mygcd :: Integer -> Integer -> Integer
mygcd m n
  | m < n = mygcd n m
  | n == 0 = m
  | otherwise = mygcd n (m `mod` n)

qsort [] = []
qsort (x:xs) =
  qsort smaller ++ [x] ++ qsort larger
  where
    smaller = [a | a <- xs, a <= x]
    larger  = [b | b <- xs, b > x ]

fib = fib' 0 1
  where
    fib' x y 0 = y
    fib' x y n = fib' y (x + y) (n - 1)

mysum :: [Integer] -> Integer
mysum [] = 0
mysum (x:xs) = x + mysum xs

mysumtc :: [Integer] -> Integer
mysumtc = mysumtc' 0
  where
    mysumtc' acc [] = acc
    mysumtc' acc (x:xs) = mysumtc' (acc + x) xs

fromBin :: [Bool] -> Integer
fromBin = fromBin' 0
  where
    fromBin' acc [] = acc
    fromBin' acc (True:bs) = fromBin' (acc * 2 + 1) bs
    fromBin' acc (False:bs) = fromBin' (acc * 2) bs


fromBinN :: [Bool] -> Integer
fromBinN = fromBinN' . reverse
  where
    fromBinN' [] = 0
    fromBinN' (True:bs) = fromBinN' bs * 2 + 1
    fromBinN' (False:bs) = fromBinN' bs * 2

myfromBin :: [Bool] -> Integer
myfromBin [] = 0
myfromBin (True:bs)  = myfromBin bs + 2 ^ length bs
myfromBin (False:bs) = myfromBin bs + 0


fromBinM :: [Bool] -> Integer
fromBinM bs =  sum $ map2 (*) intlist binlist
  where
    map2 :: (a -> b -> c) -> [a] -> [b] -> [c]
    map2 f (x:xs) (y:ys) = f x y : map2 f xs ys
    map2 _ _      _      = []

    booltoInt True  = 1
    booltoInt False = 0
    intlist = map booltoInt (reverse bs)
    binlist = map (2^) [0..]

data Tree a = Branch (Tree a) a (Tree a)
            | Empty

test1 = Branch (Branch Empty 2 Empty) 1 (Branch Empty 3 Empty)
test2 = Branch (Branch Empty 2 (Branch Empty 4 Empty)) 1 (Branch Empty 3 Empty)


size :: Tree a -> Integer
size Empty = 0
size (Branch l1 r l2) = 1 + size l1 + size l2

depth :: Tree a -> Integer
depth Empty = 0
depth (Branch l1 r l2) = 1 + max (depth l1) (depth l2)

--preorder :: Tree a -> [a]
--preorder
