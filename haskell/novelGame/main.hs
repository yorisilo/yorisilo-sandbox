data Script a = Text String (Script a)
              | Serif String String (Script a)
              | Return a

run :: Script a -> IO a
run (Return a) = return a
run (Text str next) = putStrLn str >> run next
run (Serif str1 str2 next) = putStrLn (str1 ++ ": " ++ str2) >> run next

run' :: Script a -> IO a
run' s
    |(Return a) = return a
    |(Text str next) = putStrLn str >> waitN >> run' next
    |(Serif str1 str2 next) = putStrLn (str1 ++ ": " ++ str2) >> waitN >> run' next

waitChar :: Char -> IO ()
waitChar c = getChar >>= \ipt -> if c == ipt then return () else waitChar c

waitN :: IO ()
waitN = waitChar '\n'

scr1 :: Script ()
scr1 =
    Text "鬼がいた．" $
    Serif "鬼" "おにだよ" $
    Serif "男" "はい" $
    Text "完" $
    Return ()


scr2 :: Script ()
scr2 =
    Text "鬼がいた．" $
    Serif "鬼" "おにだよ" $
    Serif "鬼" "おにだよ" $
    Serif "鬼" "おにだよ！" $
    Serif "男" "はい" $
    Text "完" $
    Return ()

scr3 :: Script ()
scr3 =
    Serif "娘" "お父さんスイッチ 『う』！" $
    Serif "父" "うんちをする" $
    Text "完" $
    Return ()


scr4 :: Script ()
scr4 =
    Serif "医者" "「こ…これは…チンカスペロペロ病…！？」" $
    Serif "妹" "「っ！？」" $
    Serif "医者" "「お兄さん、妹さんからチ○カスを舐めさせてほしいと訴えられたことはありませんか？」" $
    Serif "兄" "「うーん…たぶん無かったと思います…」 " $

    Serif "妹" "「あっ、あるわけないでしょっ！！」 " $

    Serif "医者" "「しかしこの瞳孔の開き方、下腹部のシコリ、胸部の膨らみかけ…」 " $

    Serif "兄" "「お医者様！！やはり妹の胸部は膨らみかけなのですね！？」 " $

    Serif "医者" "「ええ…残念ですが…未発達のようです…」 " $

    Serif "妹" "「うっ、うるさいっ///」 " $

    Serif "医者" "「今はまだ自覚症状が出ていないだけかもしれません」 " $

    Serif "兄" "「うぅ…」 " $

    Serif "医者" "「妹さんを十分注意して見ておいてあげてください」 " $

    Serif "兄" "「はい…」 " $

    Serif "妹" "「大丈夫だってあたしはっ」 " $
    Text "...続く" $
    Return ()

main :: IO ()
main = do
  run' scr4
