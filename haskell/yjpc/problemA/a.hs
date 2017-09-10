main :: IO ()
main = do
  l <- getLine
  let t = string2int l
  loop 0 t

loop i t
  | i < t = do
      l <- words <$> getLine
      let (nstr : mstr : []) = l
      let n = string2int nstr
      let m = string2int mstr
      putStrLn $ "Case " ++ (show $ i + 1) ++ ": " ++ (show $ harimaChange n m) ++ " " ++ (show $ matsuyamaChange n m)
      loop (i + 1) t
  | otherwise = return ()

string2int :: String -> Int
string2int str = read str

sumMap :: [String] -> Int
sumMap = sum . map string2int

harimaChange n m = 100 * n - m

matsuyamaChange n m = if m `mod` 100 == 0 then 100 * c - m else (100 * (c + 1)) - m
  where c = floor $ fromIntegral m / 100
