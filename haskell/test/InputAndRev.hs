greeting :: IO ()
greeting =
  (putStr "input name:" >>
  getLine) >>= (\str ->
               putStrLn $ "hello " ++ str)

inputInt :: IO ()
inputInt =
  putStr "input number1:" >>
  getLine >>= \str1 ->
  putStr "input number2:" >>
  getLine >>= \str2 ->
  putStrLn $ ("sum: " ++) . show $ read str1 + read str2


getInt :: IO Int
getInt =
  getLine >>= \str ->
               return $ read str
-- getLine >>= return . read

myinputInt :: IO ()
myinputInt =
  putStr "input number1:">>
  getInt >>= \int1 ->
  putStr "input number2:">>
  getInt >>= \int2 ->
  putStrLn $ ("sum: " ++) . show $ int1 + int2

repeatIO :: Int -> IO a -> IO [a]
repeatIO 0 ac = return []
repeatIO n ac =
  ac >>= \x ->
  repeatIO (n-1) ac >>= \xs ->
  return (x:xs)

myrepeatIO :: Int -> IO a -> IO [a]
myrepeatIO 0 ac = return []
myrepeatIO n ac = ac `iocons` myrepeatIO (n-1) ac
  where iocons = liftIO3 (:)

liftIO :: (a -> b) -> IO a -> IO b
liftIO f ac = ac >>= return . f

liftIO3 :: (a -> b -> c) -> IO a -> IO b -> IO c
liftIO3 f ac1 ac2 =
  ac1 >>= \x ->
  ac2 >>= \y ->
  return (f x y)
