import IO

fhead n filename = bracket (openFile filename ReadMode)
                   hClose
                   (\h -> do hSetBuffering h LineBuffering
                             take_line 0 h)
    where take_line i h' | i == n = return ()
                         | otherwise = do str <- hGetLine h'
                                          putStrLn str
                                          take_line (i+1) h'
