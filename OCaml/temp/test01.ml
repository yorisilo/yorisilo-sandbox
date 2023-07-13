(* 目的：所持金を与えると126円のチョコレートをいくつ買えるかを求める *)
(* chocolate : int -> int *)
let chocolate x = x/126
let test1 = (chocolate 100 = 0)
let test2 = (chocolate 252 = 2)
let test3 = (chocolate 500 = 3)
let test4 = (chocolate 253 = 2)
let test5 = (chocolate 251 = 1)

let rec get_last list =
  match list with
  | [] -> None
  | [x] -> Some x
  | _ :: t -> get_last t

type num_list =
  | IntList of int list
  | FloatList of float list
  | NoneList

let rec print_list list =
  match list with
  | NoneList -> print_int 0
  | IntList i -> List.iter print_int i
  | FloatList f -> List.iter print_float f

(* let print_num x = *)
(*   match x with *)
(*   |  ->  *)

let times_element n list =
  List.map (fun x -> n * x) list

let f x = x


let foo n = fun x -> n * x
let foo10 = foo 10
let fo n x = n * x
let fo10 = fo 10

let compose f g x = f(g x)
let hoge x = 2*x + 1
let hogehoge y = y*y + 3*y
let h = compose hogehoge hoge

let sum list =
let rec sum' list res =
  match list with
  | [] -> 0
  | x::xs -> sum' xs (2 + x) in
    sum' list 2

(* int list の表示 *)
let print_intList xs =
  List.iter (fun x -> print_int x; print_string " ") xs;
  print_newline()

(* リストから要素xを除いたリストを返す関数 *)
let rec remove x = function
  | [] -> []
  | y :: ys -> if x = y then remove x ys
               else y :: remove x ys

let distance ((x1,y1),(x2,y2)) =
  let dx = abs_float (x1 -. x2) in
  let dy = abs_float (y1 -. y2) in
  sqrt (dx *. dx +. dy *. dy)

let distance2 ((x1,y1),(x2,y2)) =
  let dx = abs_float (x1 -. x2) and dy = abs_float (y1 -. y2) in
  sqrt (dx *. dx +. dy *. dy)


(* 普通の再帰バージョンの階乗関数 *)
let rec fact n =
  if n = 0 then 1 else n * fact(n-1)

(* 末尾再帰バージョンの階乗関数 *)
let rec facti (n,a) =
  if n = 0 then a else facti (n-1, a*n)
let fact_i n = facti(n,1)

(* 末尾再帰バージョンの階乗関数 局所的な関数を利用した場合 *)
let super_fact n =
  let rec facti (n, a) =
    if n = 0 then a else facti (n-1, a*n) in
  facti (n,1)

type num =
  | NumInt of int
  | NumFloat of float

let rec power (x,y) =
  match (x,y) with
  | (_,0) -> 1
  | (_,_) -> x * power(x,y-1)
(* 末尾再帰バージョンの n から m までの和を求める関数 *)
let sum_of_integer (n, m) =
  let rec sum_of_integeri (n, m, a) =
    if n > m then a
    else sum_of_integeri (n+1, m, a+n) in
  sum_of_integeri (n, m, 0)

(* リストの要素が1つか調べる関数 *)
let single = function
  | [_] -> true
  |  _ -> false

(* リストの要素が1つ以上あるか調べる関数 *)
let pair = function
  | _::_ -> true
  | _ -> false

(* リストにxがあれば，そのリストを返し，無ければ，[]を返す関数 *)
let rec member x = function
  | [] -> []
  | (y::ys) as orig_list when x=y -> orig_list
  | (y::ys) -> member x ys

(* マッピング関数 for List *)
let rec mapcar f = function
  | [] -> []
  | x::xs -> f x :: mapcar f xs

(* リストから関数fが真を返すxを除く *)
(* フィルター (filter) はリストの要素に関数を適用し、関数が真を返す要素をリストに格納して返す関数です。 *)
let rec remove_if f = function
  | [] -> []
  | x::xs -> if f x then remove_if f xs else x::remove_if f xs

(* リストから関数fが真を返すxのみをリストへ *)
let rec move_if f = function
  | [] -> []
  | x::xs -> if f x then x::move_if f xs else move_if f xs

let test_func1 = fun x -> fun y -> x+y;;
let test_func2 = fun x y -> x+y;;

(* リストxsはxyより長いか *)
let rec longer xs xy =
  match (xs, xy) with
  | (_,[]) -> true
  | ([],_) -> false
  | (_::xs1, _::ys1) -> longer xs1 ys1

(* リストの最後尾の要素を求める *)
let rec last = function
  | [] -> failwith "Empty_set"
  | [_] as xs -> xs
  | x::xs -> last xs

let rec last = function
  | [] -> failwith "Empty_set"
  | [_] as xs -> xs
  | x::xs -> last xs

(* リストの先頭からn個の要素を取り出す *)
let rec take xs n =
  match (xs, n) with
  | (_, 0) | ([], _) -> []
  | (y::ys, _) -> y :: take ys (n - 1)

(* リストの先頭から n 個の要素を削除する *)
let rec drop xs n =
  match (xs, n) with
  | (_, 0) -> xs
  | ([], _) -> []
  | (_::ys, _) -> drop ys (n-1)

(* 多相関数 *)
type 'a tree =
  | Leaf
  | Node of 'a * 'a tree * 'a tree

(* tree の深さを計算する関数 *)
let rec depth t =
  match t with
  | Leaf -> 0
  | Node(_, t1, t2) -> let (d1, d2) = (depth t1, depth t2) in
                       1 + (if d1>d2 then d1 else d2)

(* リストの連結 *)
let rec append l1 l2 =
  match l1 with
  | [] -> []
  | [] -> l2
  | hd::l'1 -> hd :: append l'1 l2

(* 判定関数とリストを受け取り元のリストの内条件を満たす要素だけからなるリストを生成 *)
let rec filter f_bool list =
  match list with
  | [] -> []
  | x::xs -> if f_bool x then x :: filter f_bool xs else filter f_bool xs

(* 奇数判定 *)
let odd = function
  | x -> if x mod 2 == 0 then false else true


(* 接頭辞の判定 lsはxsの接頭辞か？*)
let rec prefix xs ls =
  match (xs,ls) with
  | (_,[]) -> true
  | ([],_) -> false
  | (x::xs,y::ys) -> if x = y then prefix xs ys else false

let my_list = [1;2;3;4;5;6;7]
let hage elem =
  Printf.printf "I'm looking at element %d now\n" elem

(* pってのは述語 fってのは関数 *)
let rec exists p = function
  | [] -> false
  | x::_ when p x -> true
  | _::xs -> exists p xs
