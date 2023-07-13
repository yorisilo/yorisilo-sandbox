import Control.Monad (replicateM_)
import Control.Concurrent (threadDelay)
import Data.List (intercalate)

---------------------------
-- Comonad
---------------------------

class Functor w => Comonad w where
  extract :: w a -> a
  extend :: (w b -> a) -> w b -> w a
  duplicate :: w a -> w (w a)

  duplicate = extend id
  extend f = fmap f . duplicate

---------------------------
-- List Zipper
---------------------------

data Z a = Z [a] a [a]

left, right :: Z a -> Z a
left (Z (l:ls) c rs) = Z ls l (c:rs)
right (Z ls c (r:rs)) = Z (c:ls) r rs

iterate1 :: (a -> a) -> a -> [a]
iterate1 f = tail . iterate f

instance Functor Z where
  fmap f (Z ls c rs) = Z (fmap f ls) (f c) (fmap f rs)

instance Comonad Z where
  extract (Z _ a _) = a
  duplicate z = Z (iterate1 left z) z (iterate1 right z)
  extend f z = Z (fmap f $ iterate1 left z) (f z) (fmap f $ iterate1 right z)

toZ :: a -> [a] -> Z a
toZ a xs = Z (repeat a) a (xs ++ repeat a)

---------------------------
-- 2D List Zipper
---------------------------

newtype Z2 a = Z2 (Z (Z a))

instance Functor Z2 where
  fmap f (Z2 zz) = Z2 (fmap (fmap f) zz)

instance Comonad Z2 where
  extract (Z2 zz) = extract (extract zz)
  duplicate (Z2 zz) = fmap Z2 . Z2 . roll $ roll zz where
    roll zz = Z (iterate1 (fmap left) zz) zz (iterate1 (fmap right) zz)

toZ2 :: a -> [[a]] -> Z2 a
toZ2 a xss = Z2 $ toZ (toZ a []) (map (toZ a) xss)

---------------------------
-- Life Game
---------------------------

countNeighbours :: Z2 Bool -> Int
countNeighbours (Z2 (Z
  (Z (n0:_) n1 (n2: _):_)
  (Z (n3:_) _  (n4:_))
  (Z (n5:_) n6 (n7: _):_))) =
    length $ filter id [n0, n1, n2, n3, n4, n5, n6, n7]

life :: Z2 Bool -> Bool
life z = (a && (n == 2 || n == 3)) || (not a && n == 3) where
  a = extract z
  n = countNeighbours z

showZ2 :: Int -> Int -> Z2 Char -> IO ()
showZ2 w h (Z2 (Z _ _ rows)) = do
  flip mapM_ (take h rows) $ \(Z _ _ row) -> do
    putStrLn . intercalate " " . map pure $ take w row

main :: IO ()
main = do
  let c2b c = if c == ' ' then False else True
      b2c b = if b then '#' else ' '
      (w, h) = (10, 10)
      field = [ " # "
              , "  #"
              , "###"
              ]
      initState = fmap c2b $ toZ2 ' ' field
      loop state = do
        let state' = extend life state
        replicateM_ h $ putStr "\ESC[A\ESC[2K" -- clear terminal
        showZ2 w h (fmap b2c state)
        threadDelay 300000
        loop state'

  replicateM_ h $ putStrLn ""
  loop initState
