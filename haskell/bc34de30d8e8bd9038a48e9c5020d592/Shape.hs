data Shape =
    Circle Float Float Float
  | Rctangle Float Float Float

area :: Shape -> Float
area (Circle _ _ r) = pi * r ^ 2
