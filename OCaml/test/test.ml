(* 実行時間の測定
 * 一部の演習やミニプロジェクトでは，OCamlプログラムの実行時間を測定する必要があります．実行時間を測定する際には，以下のtime関数を利用してください．time関数は関数fを引数に取り，f ()を実行した結果と経過時間（秒単位）の組を返します． *)

(* 時間測定用の関数 *)
let time : (unit -> 'a) -> 'a * float =
  fun f ->
    let start = Sys.time () in
    let res   = f () in
    let end_  = Sys.time () in
    (res, end_ -. start)

(* 実行時間を測定したい関数の例 *)
let rec fib : int -> int = function
  | 0 -> 1
  | 1 -> 1
  | n -> fib (n - 1) + fib (n - 2)

(* 利用例 *)
let ex1 = time (fun () -> fib 10)
(* val ex1 : int * float = (89, 5.99999999999906164e-06) *)
let ex2 = time (fun () -> fib 35)
(* val ex2 : int * float = (14930352, 0.417528) *)
(* 多倍長演算のようにf ()の計算結果が巨大なリストになる場合，time関数の結果をOCamlトップレベル上で表示するとリストの後ろの方や経過時間が...で省略されてしまうことがあります．この場合，経過時間を確認するにはsnd (time (fun () -> bi_fact 1000))のように，組の2番目の値を返す関数sndを使ってください． *)
