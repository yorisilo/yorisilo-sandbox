-- import Prelude hiding (Maybe,Just,Nothing)
data Expr = Int Integer
          | Add Expr Expr
          | Sub Expr Expr
          | Mul Expr Expr
          | Div Expr Expr
          deriving Show

--data Maybe a = Nothing | Just a deriving Eq

eval :: Expr -> Maybe Integer
eval (Int n) = Just n
eval (Add e1 e2) = lift (+) (eval e1) (eval e2)
eval (Sub e1 e2) = lift (-) (eval e1) (eval e2)
eval (Mul e1 e2) = lift (*) (eval e1) (eval e2)
eval (Div e1 e2)
  | v2 == Just 0 = Nothing
  | otherwise = lift div (eval e1) v2
  where v2 = eval e2

lift :: (a -> a -> a) -> Maybe a -> Maybe a -> Maybe a
lift f (Just x) (Just y) = Just (x `f` y)
lift _ _ _ = Nothing
