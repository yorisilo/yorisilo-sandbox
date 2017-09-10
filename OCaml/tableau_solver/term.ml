(* 論理式の型 *)
type wff =
  | WffAtom of string
  | WffArrow of wff * wff
  | WffOr of wff * wff
  | WffAnd of wff * wff
  | WffNot of wff

(* 世界 *)
type world =
  | WldAtom of int

(* 到達可能な世界 *)
type accessibility_for_world =
  | AcsWld of world * world     (* 0<1 : 0から1へ到達可能 *)

(* ある世界で実現可能または不可能な論理式 0 ||- A -> B こういうのを表してる*)
type provable_wff =
  | PrvblFrm of world * bool * wff

(* 式に展開規則を適用済みかどうか *)
type taked_expansion = bool

(* タブロー法での証明図における式たち ex. 0<1 とか 0 ||- A->B とか，そして式が展開規則を適用済みかどうかの情報を持っておく*)
type tableau_form =
  | TabFrm of provable_wff * taked_expansion
  | TabAcs of accessibility_for_world * taked_expansion

(* タブロー法での証明図 *)
type tableau_tree =
  | Empty
  | Node2 of tableau_form * tableau_tree * tableau_tree
  | Node1 of tableau_form * tableau_tree

type branch =
  | Empty
  | Branch of wff list
  | BranchList of branch list
