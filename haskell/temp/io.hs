
main = do
  let a = 10  -- (a)
  b <- return 10  -- (b)
  return ()
-- (a) と (b) は同じ意味
