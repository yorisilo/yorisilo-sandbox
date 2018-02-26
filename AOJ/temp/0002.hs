-- http://www.mikunimaru.com/entry/2017/11/11/174011
import System.IO
import Control.Applicative

main = do
  -- "L M N" ---> [L,M,N]
  n <- fmap (read :: String -> Int) . words <$> getLine
  -- ns <- fmap (fmap (read :: String -> Int) . words) . lines <$> getContents
  print $ digit $ foldl (+) 0 n
  eof <- isEOF
  if eof
    then return ()
    else do main

digit :: Int -> Int
digit = length . show
