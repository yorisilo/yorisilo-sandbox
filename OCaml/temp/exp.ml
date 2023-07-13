(* ocamlのデータ型の定義 *)
(* 式の型 *)
type exp =
  | IntLit of int (* リテラル *)
  | Plus of exp * exp (* 足し算 *)
  | Times of exp * exp (* 掛け算 *)
  | Minus of exp * exp (* 引き算 *)
  | Div of exp * exp (* 割り算 *)
  | BoolLit of bool (* 真理値リテラル，true false *)
  | If of exp * exp * exp (* if-then-else式 *)
  | Eq of exp * exp (* e1 == e2 : equal*)
  | Greater of exp * exp (* e1 > e2 のとき trueを返す *)
  | Var of string
  | Let of string * exp * exp

(* E というexp型の式をもらうと、Plus(E, IntLit 2) という式を返す関数 *)
(* 関数：exp -> exp *)
(* let plus2 x = Plus(x, IntLit 2);; *)
(* eval1: exp -> int *)
let rec eval1 e =
  match e with
  | IntLit(n) -> n
  | Plus(e1,e2) -> (eval1 e1) + (eval1 e2)
  | Times(e1,e2) -> (eval1 e1) * (eval1 e2)
  | Minus(e1,e2) -> (eval1 e1) - (eval1 e2)
  | Div(e1,e2) -> (eval1 e1) / (eval1 e2)
  | _ -> failwith "unknown expression"

(* 値の型 *)
type value =
  | IntVal of int (* 整数の型 *)
  | BoolVal of bool (* 真理値の型 *)

(* eval2 : exp -> value *)
let rec eval2 e =
  match e with
  | IntLit(n) -> IntVal(n)
  | Plus(e1, e2) ->
     begin
       match (eval2 e1, eval2 e2) with
       | (IntVal(n1), IntVal(n2)) -> IntVal(n1 + n2)
       | _ -> failwith "integer values expected"
     end
  | Times(e1, e2) ->
     begin
       match (eval2 e1, eval2 e2) with
       | (IntVal(n1), IntVal(n2)) -> IntVal(n1 * n2)
       | _ -> failwith "integer values expected"
     end
  | Eq(e1, e2) ->
     begin
       match (eval2 e1, eval2 e2) with
       | (IntVal(n1), IntVal(n2)) -> BoolVal(n1 = n2)
       | (BoolVal(b1), BoolVal(b2)) -> BoolVal(b1 = b2)
       | _ -> failwith "wrong value"
     end
  | BoolLit(b) -> BoolVal(b)
  | If(e1, e2, e3) ->
     begin
       match (eval2 e1) with
       | BoolVal(true) -> eval2 e2
       | BoolVal(false) -> eval2 e3
       | _ -> failwith "wrong value"
     end
  | Greater(e1, e2) ->
     begin
       match (eval2 e1, eval2 e2) with
       | (IntVal(n1), IntVal(n2)) -> BoolVal(n1 > n2)
       | _ -> failwith "integer values expected"
     end
  | _ -> failwith "integer expression e"
(* eval2は後で追加する *)

(* eval2a : exp -> value *)
(* binop : int -> exp -> exp -> value *)
let rec eval2a e =
  match e with
  | IntLit n -> IntVal n
  | Plus(e1, e2) -> binop 1 e1 e2
  | Times(e1, e2) -> binop 2 e1 e2
  | _ -> failwith "unknown expression"
  and binop flag e1 e2 =
    match (eval2a e1, eval2a e2) with
    | (IntVal n1, IntVal n2) ->
       if flag = 1 then IntVal(n1 + n2)
       else IntVal(n1)
    | _ -> failwith "integer values expected"

let rec eval2b e =
  let binop f e1 e2 =
    match (eval2b e1, eval2b e2) with
    | (IntVal n1, IntVal n2) -> IntVal(f n1 n2)
    | _ -> failwith "integer values expected"
  in
  match e with
  | IntLit n -> IntVal n
  | Plus(e1,e2) -> binop (+) e1 e2
  | Times(e1,e2) -> binop ( * ) e1 e2
  | _ -> failwith "unknown expression"


(* テスト *)
let _ = eval2(IntLit 1)
let _ = eval2(IntLit 11)
let _ = eval2 (Plus (IntLit 1, Plus (IntLit 2, IntLit 11)))
let _ = eval2 (If (Eq(IntLit 2, IntLit 11),
                   Times(IntLit 1, IntLit 2),
                   Times(IntLit 1, Plus(IntLit 2,IntLit 3))))
let _ = eval2(Greater(IntLit 2, IntLit 3))

let emptyenv () = []

let ext env x v = (x,v)::env
(* extはenvというリストの先頭に(x,v)という組を追加する関数 *)

let rec lookup x env =
  match env with
  | [] -> failwith("unbound variable:" ^ x)
  | (y,v)::tl -> if x=y then v else lookup x tl

(* eval3 : exp -> (string * value) list -> value *)
(* let と変数、環境の導入 *)

let rec eval3 e env =
  let binop f e1 e2 env =
    match (eval3 e1 env, eval3 e2 env) with
    | IntVal n1, IntVal n2 -> IntVal(f n1 n2)
    | _ failwith "integer value expected"
  in
  match e with
  | Var x -> lookup x env
  | IntLit n -> IntVal n
  | Plus(e1,e2) -> binop (+) e1 e2 env
  | Times(e1,e2) -> binop ( * ) e1 e2 env
  | BoolLit(b) -> BoolVal(b)
  | Eq(e1,e2) ->
     begin
       match (eval3 e1, eval3 e2) with
       | (IntVal(n1), IntVal(n2)) -> BoolVal(n1 = n2)
       | (BoolVal(b1), BoolVal(b2)) -> BoolVal(b1 = b2)
       | _ -> failwith "wrong value"
     end
  | If(e1,e2,e3) ->
     begin
       match (eval3 e1 env) with
       | BoolVal(true)  -> eval3 e2 env
       | BoolVal(false) -> eval3 e3 env
       | _ -> failwith "wrong value"
     end
  | Let(x,e1,e2) ->
     let env1 = ext env x (eval3 e1 env) in eval3 e2 env1
  | _ -> failwith "unknown expression"
