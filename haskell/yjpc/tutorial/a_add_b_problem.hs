main :: IO ()
main = do
  sn <- getLine
  let n = string2int sn
  loop 0 n

string2int :: String -> Int
string2int str = read str

loop i n
  | i < n = do
      ss <- words <$> getLine
      putStrLn $ "Case " ++ (show $ i + 1) ++ ": " ++ (show $ sum $ map string2int ss)
      loop (i + 1) n
  | otherwise = return ()
