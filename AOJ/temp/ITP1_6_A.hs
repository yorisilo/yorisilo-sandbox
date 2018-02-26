import Control.Applicative

main = do
  getLine
  xs <- map (read :: String -> Int) . words <$> getLine
  putStrLn $ unwords $ show <$> reverse xs
