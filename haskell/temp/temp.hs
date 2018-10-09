
zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' f [] _          = []
zipWith' f _ []          = []
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys

map' :: (a -> b) -> [a] -> [b]
map' f []     = []
map' f (x:xs) = f x : map' f xs

-- 値を関数へ持ち上げる functor
actions :: [IO ()]
actions =
  [ putStrLn "1"
  , putStrLn "2"
  , putStrLn "3"
  ]

-- main :: IO ()
-- main = head actions

main :: IO ()
main = do
  head actions
  --sequence_ actions

-- mapM を作ってみるのをやる

ns_sequence :: [IO ()] -> IO()
ns_sequence [] = do
  return ()
ns_sequence (x:xs) = do
  x
  ns_sequence xs
