helloN :: Int -> IO ()
helloN 0 = return ()
helloN 1 = putStrLn "hello"
helloN n = putStrLn "hello" >> helloN (n-1)
