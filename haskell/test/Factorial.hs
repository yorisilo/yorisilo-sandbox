main :: IO ()
main = putStrLn (show (factorial 10))

factorial :: Integer -> Integer
factorial 0 = 1
factorial n = n * factorial (n-1)

fact :: Integer -> Integer
fact n = go 1 n
  where go acc 0 = acc
        go acc n = go (n * acc) (n-1)

f5 l = go [] l
  where go acc []     = acc
        go acc (x:xs) = go (acc ++ [x*2]) xs

-- f5 [1,2,3] ~> go [] [1,2,3] ~> go acc 1:[2,3] ~> go ([1*2] ++ acc) [2,3]
-- ~> go ([2*2] ++ [2]) [3] ~> go ([3*2] ++ [4,2])...

f1 x = go 0 x
  where go acc 0 = 0
        go acc n = go (acc * n) (n-1)

f3 x = go [] x
  where go acc 0 = acc
        go acc x = go (acc ++ [x]) (x-1)

f4 l = go 0 l
  where go acc []     = acc
        go acc (x:xs) = go (acc + 1) xs

mymax :: [Int] -> Int
mymax [] = error "mymax"
mymax x:xs = go x xs
