mapIO :: (a -> IO b) -> [a] -> IO ()
mapIO f [] = return ()
mapIO f (x:xs) = f x >> mapIO f xs
