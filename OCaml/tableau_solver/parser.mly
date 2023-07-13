%{

(* ここには，構文解析で利用するための
   普通のOCamlでの定義を記述する *)

(* Termモジュール(syntax.ml)で定義した
   statement型を頻繁に使用するので，
   「Term.」を省略するためにopenしておく *)
open Term

%}

/* トークンの定義 */
%token <string> IDENT
%token EOF
%token LPAREN RPAREN
%token ARROW EQUIV AND OR NOT
%token STRAY
%nonassoc EQUIV
%right ARROW
%right OR
%right AND
%nonassoc NOT

/* 全体の構文解析の結果を表す型を指定 */
%type <Term.wff> main
%type <Term.wff> expression

/* 構文解析を開始するルールを指定 */
%start main

%%

/* 構文解析ルール */
main:
  | expression EOF { $1 }
expression:
  | IDENT { WffAtom $1}
  | LPAREN expression RPAREN { $2 }
  | expression EQUIV expression {
      let t1 = $1 in
      let t2 = $3 in
      WffAnd (WffArrow (t1, t2), WffArrow (t2, t1))
    }
  | expression ARROW expression { WffArrow ($1, $3)}
  | expression OR expression { WffOr ($1, $3)}
  | expression AND expression { WffAnd ($1, $3)}
  | NOT expression { WffNot $2}
