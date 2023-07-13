open Term
(* [val_vars] is an associative list containing the truth value of
   each variable.  For efficiency, a Map or a Hashtlb should be
   preferred. *)

let rec eval val_vars = function
  | WffAtom x -> List.assoc x val_vars
  | WffNot e -> not(eval val_vars e)
  | WffAnd(e1, e2) -> eval val_vars e1 && eval val_vars e2
  | WffOr(e1, e2) -> eval val_vars e1 || eval val_vars e2
  | WffArrow(e1, e2) -> not (eval val_vars e1) || eval val_vars e2

(* Again, this is an easy and short implementation rather than an
     efficient one. *)
let rec table_make val_vars vars expr =
  match vars with
  | [] -> [(List.rev val_vars, eval val_vars expr)]
  | v :: tl ->
     table_make ((v, true) :: val_vars) tl expr
     @ table_make ((v, false) :: val_vars) tl expr

let table vars expr = table_make [] vars expr;;
