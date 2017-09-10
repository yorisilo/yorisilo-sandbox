(* test.ml *)
open Term

(* 与えられた文字列の字句解析と構文解析だけを行う関数 *)
(* parse : string -> formula *)

let parse str =
  Parser.main Lexer.token (Lexing.from_string str)

let start_solve p =
  let p = parse p in
  let (p,env,num) = convert_name p in
  let p' = swffif p in
  Tb_proof.solve num p'

let test_solve str =
  let wff = parse str in
  let (t,env,num) = convert_name wff in
  Solver.solve num t


let convert_name_list l =
  let s = List.map convert_name l in
  let rec f s = match s with
    | [] -> []
    | (p,env,num) :: l -> SwffiT(p) :: f l in
  f s
