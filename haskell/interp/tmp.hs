-- type system
-- https://uhideyuki.sakura.ne.jp/studs/index.cgi/ja/HindleyMilnerInHaskell

module Expr where

type Id = String

data Term = Val V
          | Pred Term
          | IsZero Term
          | If Term Term Term -- if t then t else t
          deriving Show

data V = Bv B | Nv N deriving (Show, Eq)
data B = T | F deriving (Show, Eq)
data N = Zero | Succ N deriving (Show, Eq)

step :: Term -> Term
step (If (Val (Bv T)) t1 t2) = t1
step (If (Val (Bv F)) t1 t2) = t2
step (If t t1 t2)            = step t

eval :: Term -> V
eval (Val v) = v
