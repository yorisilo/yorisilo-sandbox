(* 式の型 *)
type exp = IntLit of int         (* リテラル *)
         | Plus of exp * exp     (* 足し算 *)
         | Times of exp * exp    (* かけ算 *)
         | Minus  of exp * exp
         | Div of exp * exp
         | E of exp
         | BoolLit of bool        (* 追加分; 真理値リテラル, つまり trueや false  *)
         | If of exp * exp * exp  (* 追加分; if-then-else式 *)
         | Eq of exp * exp        (* 追加分; e1 = e2 *)

(* 値の型 *)
type value =
  | IntVal  of int          (* 整数の値 *)
  | BoolVal of bool         (* 真理値の値 *)

let f = function
  | E(e)  -> Plus(E(e), IntLit 2)
  | _ as exp -> exp

let rec map_abs = function
  | IntLit e -> IntLit (abs(e))
  | E(Plus(e1,e2)) -> E(Plus(map_abs(e1),map_abs(e2)))
  | E(Times(e1,e2)) -> E(Times(map_abs(e1),map_abs(e2)))
  | E(Minus(e1,e2)) -> E(Minus(map_abs(e1),map_abs(e2)))
  | E(Div(e1,e2)) -> E(Div(map_abs(e1),map_abs(e2)))
  | a -> a

(* eval1 : exp -> int *)
let rec eval1 e =
  match e with
  | IntLit(n)    -> n
  | Plus(e1,e2)  -> (eval1 e1) + (eval1 e2)
  | Times(e1,e2) -> (eval1 e1) * (eval1 e2)
  | Div(e1,e2) -> if e2 != IntLit 0
    then (eval1 e1) / (eval1 e2)
    else failwith "Nooooooo you can't eval when e2 == 0"
  | Minus(e1,e2) -> (eval1 e1) - (eval1 e2)
  | _ -> failwith "unknown expression"


(* eval2 : exp -> value *)
let rec eval2 e =
  match e with
  | IntLit(n)  -> IntVal(n)
  | Plus(e1,e2) ->
    begin
      match (eval2 e1, eval2 e2) with
      | (IntVal(n1),IntVal(n2)) -> IntVal(n1+n2)
      | _ -> failwith "integer values expected"
    end
  | Times(e1,e2) ->
    begin
      match (eval2 e1, eval2 e2) with
      | (IntVal(n1),IntVal(n2)) -> IntVal(n1*n2)
      | _ -> failwith "integer values expected"
    end
  | Eq(e1,e2) ->
    begin
      match (eval2 e1, eval2 e2) with
      | (IntVal(n1),IntVal(n2)) -> BoolVal(n1=n2)
      | (BoolVal(b1),BoolVal(b2)) -> BoolVal(b1=b2)
      | _ -> failwith "wrong value"
    end
  | BoolLit(b) -> BoolVal(b)
  | If(e1,e2,e3) ->
    begin
      match (eval2 e1) with
      | BoolVal(true) -> eval2 e2
      | BoolVal(false) -> eval2 e3
      | _ -> failwith "wrong value"
    end
  | _ -> failwith "unknown expression"


(* テスト *)
let _ = eval2 (IntLit 1)
let _ = eval2 (IntLit 11)
let _ = eval2 (Plus (IntLit 1, Plus (IntLit 2, IntLit 11)))
let _ = eval2 (Times (IntLit 1, Plus (IntLit 2, IntLit 11)))
let _ = eval2 (If (Eq(IntLit 2, IntLit 11),
                   Times(IntLit 1, IntLit 2),
                   Times(IntLit 1, Plus(IntLit 2,IntLit 3))))
let _ = eval2 (Eq (IntLit 1, IntLit 1))
let _ = eval2 (Eq (IntLit 1, IntLit 2))
let _ = eval2 (Eq (BoolLit true, BoolLit true))
let _ = eval2 (Eq (BoolLit true, BoolLit false))
