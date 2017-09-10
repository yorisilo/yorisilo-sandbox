-- jannkenn.hs
-- do rock, paper, scissors

{- scleen shot

D:\doc\05-03\haskell>runhugs jannkenn.hs
Jannkenn Pon:
p                            -- give g (Guu), c (Choki), or p (Paa)
I picked Paa
Aiko de syo:
g
I picked Guu
Aiko de syo:
g
I picked Paa
I won.

-}

module Main where

import Time
import Char
import Random

data Jannkenn = Guu
              | Choki
              | Paa
                deriving (Eq, Show)

isIwon :: Jannkenn -> Jannkenn -> Bool
isIwon Guu Choki  = True
isIwon Choki Paa  = True
isIwon Paa Guu    = True
isIwon _ _        = False


-- making a seed for randomR
the_sec :: IO Int
the_sec = do tm <- getClockTime
             return $ sum $ zipWith (*)
                              (map read $ split_str ':' ((words $ show tm) !! 3))
                              [3600,60,1]

-- split a string
split_str :: Char -> String -> [String]
split_str _ [] = []
split_str c str = w : split_str c (case rest of{"" -> ""; _ -> tail rest})
  where (w, rest) = break (==c) str

gcp_read :: String -> Jannkenn
gcp_read str = case toLower $ head str of
                        'g' -> Guu
                        'c' -> Choki
                        'p' -> Paa

jannkenn :: [Int] -> String -> IO()
jannkenn ls say = do putStrLn say
                     str <- getLine
                     let mine = case (mod (head ls) 3) of
                             0 -> Guu
                             1 -> Choki
                             2 -> Paa
                         yours = gcp_read str
                     putStrLn $ "I picked " ++ show mine
                     if mine == yours
                         then jannkenn (tail ls) "Aiko de syo: "
                         else if isIwon mine yours
                                  then putStrLn "I won."
                                  else putStrLn "You won."

main :: IO()
main = do sec <- the_sec
          setStdGen (mkStdGen sec)
          g <- getStdGen
          let rls = randoms g
          jannkenn rls "Jannkenn Pon: "
