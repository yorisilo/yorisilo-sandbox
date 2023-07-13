open Term

let rec formula_print = function
  | WffAtom x -> Printf.sprintf "%s" x
  | WffArrow (x,y) -> Printf.sprintf "(%s -> %s)" (formula_print x) (formula_print y)
  | WffOr (x,y) -> Printf.sprintf "(%s or %s)" (formula_print x) (formula_print y)
  | WffAnd (x,y) -> Printf.sprintf "(%s and %s)" (formula_print x) (formula_print y)
  | WffNot x -> Printf.sprintf "(not %s)" (formula_print x)

let pp x = print_endline (formula_print x)

let () =
  let lexbuf = Lexing.from_channel stdin in
  let formula = Parser.main Lexer.token lexbuf in
  pp formula
