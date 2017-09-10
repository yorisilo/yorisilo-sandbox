(* test.ml *)

(* 構文定義ファイル syntax.ml で定義された formula型を使う *)
open Term

(* 与えられた文字列の字句解析と構文解析だけを行う関数 *)
(* parse : string -> formula *)

let parse str =
  Parser.main Lexer.token (Lexing.from_string str)
