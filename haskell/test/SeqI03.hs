seqIO3 :: IO a -> IO b -> IO c -> IO c
seqIO3 a1 a2 a3 = a1 >> a2 >> a3
