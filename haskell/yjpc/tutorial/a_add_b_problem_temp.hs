main :: IO ()
main = do
 sn <- getLine
 let n = string2int sn
 let loop i | i < n = do
                ss <- words <$> getLine
                putStrLn $ show $ sum $ map string2int ss
                loop $ i + 1
     loop _ = return ()
 loop 0

string2int :: String -> Int
string2int str = read str :: Int

loopGetLine = do
  ss <- words <$> getLine
  putStrLn $ show $ sum $ map string2int ss

-- sum = foldr (+) 0


-- http://qiita.com/7shi/items/85afd7bbd5d6c4115ad6
-- http://qiita.com/siquare/items/ec0c01c81c22ce060405
