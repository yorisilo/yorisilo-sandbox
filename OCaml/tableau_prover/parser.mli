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
  | STRAY

val main :
  (Lexing.lexbuf  -> token) -> Lexing.lexbuf -> Term.wff
