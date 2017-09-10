(* 直観主義命題論理におけるタブロー法によるprover *)
open Syntax
open Printf
(* formula -> probable_formula *)
(* はじめにだけ呼ぶ関数 *)
let init = function
  | FormAtom form -> TabFrm (PrvblFrm (WldAtom 0, false, FormAtom form), false)
  | FormNot form -> TabFrm (PrvblFrm (WldAtom 0, false, FormNot form), false)
  | FormArrow (form1, form2) -> TabFrm (PrvblFrm (WldAtom 0, false, FormArrow (form1, form2)), false)
  | FormOr (form1, form2) -> TabFrm (PrvblFrm (WldAtom 0, false, FormOr (form1, form2)), false)
  | FormAnd (form1, form2) -> TabFrm (PrvblFrm (WldAtom 0, false, FormAnd (form1, form2)), false)

                                     (* PrvblRrmをtableau_formへ *)
                                     (* let rec prove = function *)
                                     (*   |  -> *)
