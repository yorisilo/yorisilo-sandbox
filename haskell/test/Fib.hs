main :: IO ()
main = putStrLn $ fibTable 10

fibTable :: Integer -> String
fibTable 1 = fibLine 1
fibTable n = fibTable (n-1) ++ "\n" ++ fibLine n

fibLine :: Integer -> String
fibLine n = "fib " ++ show n ++ " = " ++ show (fib n)

fib :: Integer -> Integer
fib 1 = 1
fib 2 = 1
fib n = fib(n-1) + fib(n-2)
