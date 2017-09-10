open Syntax
open Printf
(* formula -> probable_formula *)
(* はじめにだけ呼ぶ関数 *)
let init = function
  | FormAtom form -> PrvblFrm (WldAtom 0, false, FormAtom form)
  | FormNot form -> PrvblFrm (WldAtom 0, false, FormNot form)
  | FormArrow (form1, form2) -> PrvblFrm (WldAtom 0, false, FormArrow (form1, form2))
  | FormOr (form1, form2) -> PrvblFrm (WldAtom 0, false, FormOr (form1, form2))
  | FormAnd (form1, form2) -> PrvblFrm (WldAtom 0, false, FormAnd (form1, form2))

let rec add_last list a =
  match (list,a) with
  | ([],a)  -> a
  | (x::xs,a) -> x::(add_last xs a)

let contradiction l =
  let rec exists_prop_pair list =
    match list with
    | FormAtom p :: ps -> if List.exists (fun x -> x = (FormNot (FormAtom p))) list then true else exists_prop_pair ps
    | FormNot (FormAtom p) :: ps -> if List.exists (fun x -> x = (FormAtom p)) list then true else exists_prop_pair ps
    | _ -> false
  in
if (exists_prop_pair l) then true else false

let only_atom l =
  let rec is_only_atom_proplist = function
    | [FormAtom p] -> true
    | [FormNot (FormAtom p)] -> true
    | FormAtom p :: ps -> is_only_atom_proplist ps
    | FormNot (FormAtom p) :: ps -> is_only_atom_proplist ps
    | _ -> false
  in
    let rec exists_prop_pair list =
      match list with
      | FormAtom p :: ps -> if List.exists (fun x -> x = (FormNot (FormAtom p))) list then true else exists_prop_pair ps
      | FormNot (FormAtom p) :: ps -> if List.exists (fun x -> x = (FormAtom p)) list then true else exists_prop_pair ps
      | _ -> false
    in
if (is_only_atom_proplist l) && not(exists_prop_pair l) then true else false

let rec prove_proplist (y:Syntax.formula list) =
  begin
    match y with
    | _ when only_atom y -> sprintf " -branch provable- "
    | (FormAtom x)::xs as y -> if contradiction y then sprintf " -not provable branch- " else prove_proplist (xs @ [(FormAtom x)])
    (* if xs == [] then sprintf "provable" else prove_proplist xs *)
    | (FormNot (FormAtom x))::xs -> if contradiction y then sprintf " -not provable branch- " else prove_proplist (xs @ [FormNot (FormAtom x)])
    | (FormNot (FormOr (x,y)))::xs -> prove_proplist ((xs @ [FormNot x; FormNot y]))
    | (FormNot (FormAnd (x,y)))::xs -> prove_proplistlist ([xs @ [FormNot x]; xs @ [FormNot y]])
    | (FormNot (FormArrow (x,y)))::xs -> prove_proplist (xs @ [x; FormNot y])
    | (FormNot (FormNot x ))::xs -> prove_proplist (xs @ [x])
    | (FormArrow (x,y))::xs -> prove_proplistlist ([xs @ [FormNot x]; xs @ [y]])
    | (FormAnd (x,y))::xs -> prove_proplist ((xs @ [x; y]))
    | (FormOr (x,y))::xs -> prove_proplistlist ([xs @ [x];xs @ [y]])
    | [] -> sprintf "error"
  end
  and
    prove_proplistlist (ys:Syntax.formula list list) =
    match ys with
    | [] -> sprintf " finish "
    | y::ys -> prove_proplist y ^ prove_proplistlist ys

(*
(* fun:let rec prove_proplistlist2 = function *)
(*   | Syntax.formura ->  *)

(* 枝の中から推論規則を適用させる論理式を選ぶ関数 *)


(* 枝の中にp,~pがあれば枝を閉じる *)
(* let rec prove_proplist_stop (pl:Syntax.formula list) = *)
(*   match pl with *)
(*   | p::ps -> List.exists *)
(* 枝が [p;q;~p] とかだったら true を返す *)
(* fun:exists_prop_pair *)

(* リストの中が全てatomまたはnot atomであるとtrueを返す *)
(* fun:is_only_atom_proplist *)
 *)

(* 枝の中で，すべての展開規則の適用が終われば枝をそれ以上伸ばさない関数 *)
