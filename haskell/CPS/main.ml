let x = 1 in
let f = fun y -> x + y in
(* ここでのfはクロージャとなっている *)
(* クロージャ = 関数の引数本体に環境を追加したもの *)
let x = 2 in
f (x + 3);;

type denval = THUNK of unit -> expval
type expval = FUNCT of denval -> expval
