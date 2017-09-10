import Data.List
import Data.String.Utils

main :: IO ()
main = do
  l <- getLine
  let t = string2int l
  loop 0 t

loop i t
  | i < t = do
      n <- getLine
      let listio = createList 0 (string2int n) []
      list <- listio
      putStrLn $ "Case " ++ (show $ i + 1) ++ ": " ++ (solve (createtAndSs list []) "")
      loop (i + 1) t
  | otherwise = return ()

string2int :: String -> Int
string2int str = read str

createList i n list
  | i < n = do
      l <- words <$> getLine
      let (t:s:[]) = l
      createList (i+1) n (t:s:list)
  | otherwise = return list

createtAndSs :: [String] -> [(Int, String)] -> [(Int,String)]
createtAndSs [] acc = sort acc
createtAndSs list acc =
  let (time' : str : ll) = list in
    let time = string2int $ replace ":" "" time' in
      let ss = (time,str) : acc in
        createtAndSs ll ss

solve :: [(Int, String)] -> String -> String
solve [] acc = acc
solve ((t, s) : tAndS) acc = solve tAndS (acc ++ s)

-- [(000001,"y"),(000002,"a"),(000003,"h"),(000004,"o"),(000005,"o")]
-- ["00:00:01","y","00:00:02","a","00:00:03","h","00:00:04","o","00:00:05","o"]
