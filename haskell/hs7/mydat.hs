-- for haskell7.html
module Mydat where

data Vector a = Vec [a]

instance Show a => Show (Vector a) where
    show (Vec xs) = 'V' : show xs

instance Eq a => Eq (Vector a) where
    Vec xs == Vec ys = xs == ys

--    Num((+), (-), (*), negate, abs, signum, fromInteger),
instance Num a => Num (Vector a) where
     Vec xs + Vec ys = Vec $ zipWith (+) xs ys
     Vec xs - Vec ys = Vec $ zipWith (-) xs ys
     negate (Vec xs) = Vec $ map negate xs

-- inner product
ipro :: (Num a) => Vector a -> Vector a -> a
ipro (Vec xs) (Vec ys) = sum $ zipWith (*) xs ys

-- length of vector
vabs :: Vector Double -> Double
vabs (Vec xs) = sqrt $ sum $ map (^2) xs

{------------------------------------------
 -- Binary state tree
data BST a = Eot
           | Node Int a (BST a) (BST a) -- key, val, left, right
 deriving Eq

instance Show a => Show (BST a) where
    show Eot = "Null"
    show node@(Node _ _ _ _) = "BST" ++ (show $ bst2alist node)

-- find a record in a BST
bst_find :: BST a -> Int -> Maybe (Int, a)
bst_find Eot _ = Nothing
bst_find (Node key0 val0 left right) key
    | key0 == key = Just (key0, val0)
    | key0 < key  = bst_find right key
    | otherwise   = bst_find left  key

-- insert a record into a BST
bst_insert :: BST a -> (Int, a) -> BST a
bst_insert Eot (key, val) = Node key val Eot Eot
bst_insert (Node key0 val0 left right) (key, val)
    | key0 == key = Node key0 val left right                             -- if same key value, replace val
    | key0 < key  = Node key0 val0 left (bst_insert right (key, val))
    | otherwise   = Node key0 val0 (bst_insert left  (key, val)) right

-- traverse
bst_map :: (a -> b) -> BST a -> [(Int,b)]
bst_map _ Eot = []
bst_map f (Node key val left right) = bst_map f left ++ (key, f val) : bst_map f right

-- convert to an association list
bst2alist :: BST a -> [(Int, a)]
bst2alist  = bst_map id

-- test data
bst1 = foldl bst_insert Eot [(5, "five"), (6,"six"), (4,"four"),
                              (3, "three"), (7, "seven"), (1,"One"), (10, "ten") ]
------------------------------------------}

-- Binary state tree
data BST a = Eot
           | Node {
                    node_key :: Int,
                    node_val ::  a,
                    node_left :: BST a,
                    node_right :: BST a
                  }
 deriving Eq

instance Show a => Show (BST a) where
    show Eot = "Null"
    show node = "BST" ++ (show $ bst2alist node)

-- find a record in a BST
bst_find :: BST a -> Int -> Maybe (Int, a)
bst_find Eot _ = Nothing
bst_find node key
    | key0 == key = Just (key0, node_val node)
    | key0 < key  = bst_find (node_right node) key
    | otherwise   = bst_find (node_left node)  key
 where key0 = node_key node

-- insert a record into a BST
bst_insert :: BST a -> (Int, a) -> BST a
bst_insert Eot (key, val) = Node{
                                  node_key = key,
                                  node_val = val,
                                  node_left = Eot,
                                  node_right =  Eot
                                }
bst_insert node (key, val)
    | key0 == key = node                                        -- if same key value, replace val
    | key0 < key  = node{node_right = bst_insert right0 (key, val)}
    | otherwise   = node{node_left = bst_insert left0  (key, val)}
 where key0 = node_key node
       left0 = node_left node
       right0 = node_right node

-- traverse
bst_map :: (a -> b) -> BST a -> [(Int,b)]
bst_map _ Eot = []
bst_map f node = bst_map f (node_left node) ++
                 (node_key node, f (node_val node)) : bst_map f (node_right node)

-- convert to an association list
bst2alist :: BST a -> [(Int, a)]
bst2alist  = bst_map id

-- test data
bst1 = foldl bst_insert Eot [(5, "five"), (6,"six"), (4,"four"),
                              (3, "three"), (7, "seven"), (1,"One"), (10, "ten") ]

--
class Area a where
    area :: a -> Double
--
data Circle = Circle Double

instance Area Circle where
    area (Circle r) = pi * r * r
--
data Rectangular = Rectangular Double Double

instance Area Rectangular where
    area (Rectangular w h) = w * h
