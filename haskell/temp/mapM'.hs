main = do
  mapM_' print [1..10]
  return ()

mapM_' :: Monad m => (a -> m b) -> [a] -> m ()
mapM_' m [] = return ()
mapM_' m (x:xs) = do
  m x
  mapM_' m xs

-- mapM' :: Monad m => (a -> m b) -> [a] -> m ([b])
-- mapM' m [] =
-- mapM' m (x:xs) = do
--   m x

sequenceA' :: Applicative f => t (f a) -> f (t a)
sequenceA' = traverse' id

traverse' :: Applicative f => (a -> f b) -> t a -> f (t b)
traverse' f = sequenceA' . fmap f
