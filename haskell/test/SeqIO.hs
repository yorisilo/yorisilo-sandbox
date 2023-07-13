seqIO :: [IO a] -> IO ()
seqIO [] = return ()
seqIO (a:as) = a >> seqIO as
