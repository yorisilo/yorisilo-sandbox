open Term
open Printf
(* wff -> probable_wff *)
(* はじめにだけ呼ぶ関数 *)
let init = function
  | WffAtom form -> PrvblWff ( 0, false, WffAtom form)
  | WffNot form -> PrvblWff ( 0, false, WffNot form)
  | WffArrow (form1, form2) -> PrvblWff ( 0, false, WffArrow (form1, form2))
  | WffOr (form1, form2) -> PrvblWff ( 0, false, WffOr (form1, form2))
  | WffAnd (form1, form2) -> PrvblWff ( 0, false, WffAnd (form1, form2))

(* リストの最後にaを加える リストの長さ分の線形時間かかる *)
let rec add_last l a =
  match l with
  | [] -> [a]
  | x::xs -> x::(add_last xs a)

(* リストの最後にaを加える ひっくり返して先頭へそれをまたひっくり返す*)
let add_lastkai l a =
  let rev_l = (List.rev l) in
  let list = a::rev_l in
  List.rev list

let rec exists_prop_pair list =
  match list with
  | WffAtom p :: ps -> if List.exists (fun x -> x = WffNot (WffAtom p)) list then true else exists_prop_pair ps
  | WffNot (WffAtom p) :: ps -> if List.exists (fun x -> x = (WffAtom p)) list then true else exists_prop_pair ps
  | _ -> false

(* 枝の中にp,~pがあればtrue を返す *)
let contradiction l =
  if (exists_prop_pair l) then true else false

(* リストの中が全てatomまたはnot atomであるとtrueを返す *)
let only_atom l =
  let rec is_only_atom_proplist = function
    | [WffAtom p] -> true
    | [WffNot (WffAtom p)] -> true
    | WffAtom p :: ps -> is_only_atom_proplist ps
    | WffNot (WffAtom p) :: ps -> is_only_atom_proplist ps
    | _ -> false
  in
  if (is_only_atom_proplist l) && not(exists_prop_pair l) then true else false

let rec prove_proplist (y:Term.wff list) =
  begin
    match y with
    | _ when only_atom y -> sprintf " -branch provable- "
    | (WffAtom x)::xs as y -> if contradiction y then sprintf " -not provable branch- " else prove_proplist (add_lastkai xs (WffAtom x))
    (* if xs == [] then sprintf "provable" else prove_proplist xs *)
    | (WffNot (WffAtom x))::xs -> if contradiction y then sprintf " -not provable branch- " else prove_proplist (add_lastkai xs (WffNot (WffAtom x)))
    | (WffNot (WffOr (x,y)))::xs -> prove_proplist (let l = add_lastkai xs (WffNot x) in add_lastkai l (WffNot y))
    | (WffNot (WffAnd (x,y)))::xs -> prove_proplistlist ([ add_lastkai xs (WffNot x); add_lastkai xs (WffNot y)])
    | (WffNot (WffArrow (x,y)))::xs -> prove_proplist ( let l = add_lastkai xs x in add_lastkai l (WffNot y))
    | (WffNot (WffNot x ))::xs -> prove_proplist (add_lastkai xs x)
    | (WffArrow (x,y))::xs -> prove_proplistlist ([add_lastkai xs (WffNot x); add_lastkai xs y ])
    | (WffAnd (x,y))::xs -> prove_proplist (let l = add_lastkai xs x in add_lastkai l y)
    | (WffOr (x,y))::xs -> prove_proplistlist ([add_lastkai xs x; add_lastkai xs y])
    | [] -> sprintf "error"
  end
  and
    prove_proplistlist (ys:Term.wff list list) =
    match ys with
    | [] -> sprintf " finish "
    | y::ys -> prove_proplist y ^ prove_proplistlist ys
