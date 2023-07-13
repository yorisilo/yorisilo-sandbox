import Control.Monad
newtype Parser a = Parser (String -> [(a,String)])

item :: Parser Char
item = Parser (\cs -> case cs of
                        "" -> []
                        (c:cs) -> [(c,cs)])

parse :: Parser a -> String -> [(a,String)]
parse (Parser f) = f

instance Monad Parser where
    return a = Parser (\cs -> [(a,cs)])
    p >>= f  = Parser (\cs -> concat [parse (f a) cs' | (a,cs') <- parse p cs])

p :: Parser (Char,Char)
p = do { c <- item; item; d <- item; return (c,d)}

instance MonadPlus Parser where
    mzero = Parser (\cs -> [])
    p `mplus` q = Parser (\cs -> parse p cs ++ parse q cs)

(+++) :: Parser a -> Parser a -> Parser a
p +++ q = Parser (\cs -> case parse (p `mplus` q) cs of
                           [] -> []
                           (x:xs) -> [x])

sat :: (Char -> Bool) -> Parser Char
sat p = do {c <- item; if p c then return c else mzero}

char :: Char -> Parser Char
char c = sat (c ==)

string :: String -> Parser String
string "" = return ""
string (c:cs) = do {char c; string cs; return (c:cs)}

many :: Parser a -> Parser [a]
many p = many1 p +++ return []

many1 :: Parser a -> Parser [a]
many1 p = do {a <- p; as <- many p; return (a:as)}

sepby :: Parser a -> Parser b -> Parser [a]
p `sepby` sep = (p `sepby1` sep) +++ return []

sepby1 :: Parser a -> Parser b -> Parser [a]
p `sepby1` sep = do a <- p
                    as <- many (do {sep; p})
                    return (a:as)
