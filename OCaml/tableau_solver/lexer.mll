{
  open Parser
}

let space = [' ' '\t' '\n' '\r']
let digit = ['0'-'9']
let alphabet = ['A'-'U' 'W'-'Z' 'a'-'z' '_']

(* | 正規表現 -> { そのトークンを表すOCamlの式 } *)
rule token = parse
  | space+ { token lexbuf }
  | "(*" { in_comment lexbuf; token lexbuf }
  | alphabet(alphabet|digit)* { IDENT (Lexing.lexeme lexbuf) }
  | "=>" { ARROW }
  | "->" { ARROW }
  | "→" { ARROW }
  | "⇒" { ARROW }
  | "<=>" { EQUIV }
  | "<->" { EQUIV }
  | "=" { EQUIV }
  | "⇔" { EQUIV }
  | "&&" { AND }
  | "&" { AND }
  | "＆" { AND }
  | "*" { AND }
  | "/\\" { AND }
  | "∧" { AND }
  | "||" { OR }
  | "|" { OR }
  | "｜" { OR }
  | "+" { OR }
  | "\\/" { OR }
  | "∨" { OR }
  | "V" { OR }
  | "~" { NOT }
  | "!" { NOT }
  | "-" { NOT }
  | "￢" { NOT }
  | "¬" { NOT }
  | "(" { LPAREN }
  | "（" { LPAREN }
  | ")" { RPAREN }
  | "）" { RPAREN }
  | _ { STRAY }
  | eof { EOF }
and in_comment =
  parse "(*" { in_comment lexbuf; in_comment lexbuf }
  | "*)" { () }
  | _ { in_comment lexbuf }
