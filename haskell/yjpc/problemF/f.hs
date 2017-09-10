main :: IO ()
main = do
  l <- getLine
  let t = string2int l
  loop 0 t

string2int :: String -> Int
string2int str = read str

loop i t
  | i < t = do
      --l <- words <$> getLine
      --let (n:m:[]) = l
      l <- getLine
      let (n:m:[]) = map read $ words l :: [Int]
          putStrLn $ "Case " ++ (show $ i + 1) ++ ": " ++ (show $ harimaChange n m) ++ " " ++ (show $ matsuyamaChange n m)
      loop (i + 1) t
  | otherwise = return ()

sumMap :: [String] -> Int
sumMap = sum . map string2int


harimaChange n m = m - 100 * n
matsuyamaChange n m = m - 100 * n
