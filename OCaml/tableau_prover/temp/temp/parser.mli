type token =
  | IDENT of (string)
  | EOF
  | LPAREN
  | RPAREN
  | ARROW
  | EQUIV
  | AND
  | OR
  | NOT
  | BOT
  | TOP

val main :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> Term.pnterm
