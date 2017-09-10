(* タブロー法による証明 *)
open Term

(*
 * R = succedent
 * L = antecedent
 * T = top
 * B = bottom
 * C = conjunction かつ
 * D = disjunction または
 * I = implication ならば
 * P = atomic proposition
 *)


(* expansion rule
 * T_conj
 * F_conj
 * Fc_conj
 * T_disj
 * F_disj
 * Fc_disj
 * T_impl_atom
 * F_impl
 * Fc_impl
 * T_not
 * F_not
 * Fc_not
 * T_impl_conj
 * T_impl_not
 * T_impl_disj
 * T_impl_impl
 *)

type tb_proof =
  | T_conj of swffi list * swffi
  | F_conj of swffi list * swffi
  | Fc_conj of swffi list * swffi
  | T_disj of swffi list * swffi
  | F_disj of swffi list * swffi
  | Fc_disj of swffi list * swffi
  | T_impl_atom of swffi list * swffi
  | F_impl of swffi list * swffi
  | Fc_impl of swffi list * swffi
  | T_not of swffi list * swffi
  | F_not of swffi list * swffi
  | Fc_not of swffi list * swffi
  | T_impl_conj of swffi list * swffi
  | T_impl_not of swffi list * swffi
  | T_impl_disj of swffi list * swffi
  | T_impl_impl of swffi list * swffi

(* 展開規則を適用した h = swffi *)
let tb_type = function
  | T_conj (_,h) -> h
  | F_conj (_,h) -> h
  | Fc_conj (_,h) -> h
  | T_disj (_,h) -> h
  | F_disj (_,h) -> h
  | Fc_disj (_,h) -> h
  | T_impl_atom (_,h) -> h
  | F_impl (_,h) -> h
  | Fc_impl (_,h) -> h
  | T_not (_,h) -> h
  | F_not (_,h) -> h
  | Fc_not (_,h) -> h
  | T_impl_conj (_,h) -> h
  | T_impl_not (_,h) -> h
  | T_impl_disj (_,h) -> h
  | T_impl_impl (_,h) -> h

type proof_list =
  | TB of tb_proof
  | SW of swffi


let rec mem_atom_arrow p s =
  match s with
  | [] -> false
  | SwffiT(WffiArrow (p',_)) :: hs -> if p' = p then true else mem_atom_arrow p hs
  | h::hs -> mem_atom_arrow p hs

(* sから SwffiT(WffiArrow (p1,p2) を除去して，SwffiT(p2)を加えたs_1を返す*)
let rec remove_atom_arrow_plus_atom p s =
  match s with
  | [] -> []
  | SwffiT(WffiArrow (p1,p2)) :: s when p1 = p -> SwffiT(p2)::s
  | h::s -> h :: remove_atom_arrow_plus_atom p s

let rec member_for_C1_rule s =
  match s with
  | SwffiT(WffiAnd(p1, p2)) :: s -> true
  | SwffiF(WffiOr(p1, p2)) :: s -> true
  | SwffiFc(WffiOr(p1, p2)) :: s-> true
  | SwffiT(WffiArrow(WffiAtom p1, p2)) :: s when List.mem (SwffiT(WffiAtom(p1))) s = true -> true
  | SwffiT(WffiAtom p) :: s when mem_atom_arrow (WffiAtom p) s -> true
  | SwffiT(WffiNot p) :: s -> true
  | SwffiT(WffiArrow(WffiAnd(p1,p2),p3)) :: s -> true
  | SwffiT(WffiArrow(WffiOr(p1,p2),p3)) :: s-> true
  | _ :: s -> member_for_C1_rule s
  | [] -> false

let rec member_for_C2_rule s =
  match s with
  | SwffiF(WffiAnd(p1,p2)) :: s -> true
  | SwffiT(WffiOr(p1,p2)) :: s -> true
  | _ :: s -> member_for_C2_rule s
  | [] -> false

let rec member_for_C3_rule s =
  match s with
  | SwffiF(WffiArrow(p1,p2)) :: s -> true
  | SwffiF(WffiNot p) :: s -> true
  | _ :: s -> member_for_C3_rule s
  | [] -> false

let rec member_for_C4_rule s =
  match s with
  | SwffiT(WffiArrow(WffiNot p1,p2)) :: s -> true
  | SwffiT(WffiArrow(WffiArrow(p1,p2),p3)) :: s -> true
  | _ :: s -> member_for_C4_rule s
  | [] -> false


(* sリストの中にCiルールに適用できるh=swffiがあれば，そのhを削除して，hs = 適用結果をsに代入させる s:swff list h:swff hs:swff list *)
(* let hoge s = *)
(*   match s with *)
(*   | h :: s -> *)

(* 集合の生成 xsから重複要素を取り除く *)
let set_of_list xs =
  let rec iter a = function
    | [] -> (List.rev a)
    | y::ys -> if List.mem y ys then iter a ys else iter (y::a) ys
  in
  iter [] xs

let rec s_to_sc = function
  | [] -> []
  | SwffiF(p) :: hs -> s_to_sc hs
  | h :: hs -> h :: s_to_sc hs

(* Rule *)
let rec t_conj = function
  | [] -> []
  | SwffiT(WffiAnd(p1, p2)) :: s -> (SwffiT p1 :: SwffiT p2 :: s)
  | h::hs -> h :: t_conj hs

let rec f_disj = function
  | [] -> []
  | SwffiF(WffiOr(p1, p2)) :: s -> (SwffiF p1 :: SwffiF p2 :: s)
  | h::hs -> h :: f_disj hs

let rec fc_disj = function
  | [] -> []
  | SwffiFc(WffiOr(p1, p2)) :: s -> (SwffiFc p1 :: SwffiFc p2 :: s)
  | h::hs -> h :: fc_disj hs

let rec t_imp_atom = function
  | [] -> []
  | SwffiT(WffiArrow(WffiAtom p1, p2)) :: s when List.mem (SwffiT(WffiAtom(p1))) s = true -> (SwffiT p2 :: s)
  | SwffiT(WffiAtom p) :: s as ss when mem_atom_arrow (WffiAtom p) s -> (remove_atom_arrow_plus_atom (WffiAtom p) ss)
  | h::hs -> h :: t_imp_atom hs

let rec t_not = function
  | [] -> []
  | SwffiT(WffiNot p) :: s -> ((SwffiFc p)::s)
  | h::hs -> h :: t_not hs

let rec t_imp_conj = function
  | [] -> []
  | SwffiT(WffiArrow(WffiAnd(p1,p2),p3)) :: s -> (SwffiT(WffiArrow(p1,WffiAnd(p1, p2))) :: s)
  | h::hs -> h :: t_imp_conj hs

(* num+1すべし *)
let rec t_imp_disj num = function
  | [] -> []
  | SwffiT(WffiArrow(WffiOr(p1,p2),p3)) :: s -> (SwffiT(WffiArrow(p1,WffiAtom num))::SwffiT(WffiArrow(p2,WffiAtom num))::SwffiT(WffiArrow(WffiAtom num,p3)) :: s)
  | h::hs -> h :: t_imp_disj num hs

let rec f_conj = function
  | [] -> []
  | SwffiF(WffiAnd(p1,p2)) :: s ->   (SwffiF p1 :: s) @ (SwffiF p2  :: s)
  | h::hs -> h :: f_conj hs

let rec t_disj = function
  | [] -> []
  | SwffiT(WffiOr(p1,p2)) :: s -> (SwffiT(p1) :: s) @ (SwffiT(p2) :: s)
  | h::hs -> h :: t_disj hs

let rec f_imp = function
  | [] -> []
  | SwffiF(WffiArrow(p1,p2)) :: s -> let sc = s_to_sc s in (SwffiT(p1) :: SwffiF(p2) :: sc)
  | h::hs -> h :: f_imp hs

(* let rec c1 num s = if member_for_C1_rule s then *)
(*                      let s1 = t_conj s *)
(*                      in let s2 = f_disj s1 *)
(*                         in let s3 = fc_disj s2 *)
(*                            in let s4 = t_imp_atom s3 *)
(*                               in let s5 = t_not s4 *)
(*                                  in let s6 = t_imp_conj s5 *)
(*                                     in let s7 = t_imp_disj s6 *)

let c2 num s = if member_for_C2_rule s then
                 let s1 = f_conj s
                 in let s2 = t_disj s1
                    in num,s2
               else num,s


(* aと同じ要素を削除する（ただしひとつだけ） *)
let rec remove a = function
  | [] -> []
  | h::s -> if a = h then s else h :: remove a s

(* hs内の要素と同じ要素を削除する （ただしひとつずつ）*)
let rec removes hs s = match hs with
  | [] -> s
  | h::hs -> removes hs (remove h s)

(* let rec decide function = *)
(*   | pr::prs when pr = -> *)

let comp_pair s =
  let rec f s = match s with
    | [] -> false
    | SwffiT p :: s -> if (List.mem (SwffiF p) s) || (List.mem (SwffiFc p) s)
                       then true
                       else f s
    | _::s -> f s
  in let rs = List.rev s
     in (f s) || (f rs)

(* リストの中に特定のswffがあるかどうかを調べる *)

let rec member_for_Ci_rule s =
  match s with
  | SwffiT(WffiAnd(p1, p2)) :: s -> true
  | SwffiF(WffiOr(p1, p2)) :: s -> true
  | SwffiFc(WffiOr(p1, p2)) :: s-> true
  | SwffiT(WffiArrow(WffiAtom p1, p2)) :: s when List.mem (SwffiT(WffiAtom(p1))) s = true -> true
  | SwffiT(WffiAtom p) :: s when mem_atom_arrow (WffiAtom p) s -> true
  | SwffiT(WffiNot p) :: s -> true
  | SwffiT(WffiArrow(WffiAnd(p1,p2),p3)) :: s -> true
  | SwffiT(WffiArrow(WffiOr(p1,p2),p3)) :: s-> true
  | SwffiF(WffiAnd(p1,p2)) :: s -> true
  | SwffiT(WffiOr(p1,p2)) :: s -> true
  | SwffiF(WffiArrow(p1,p2)) :: s -> true
  | SwffiF(WffiNot p) :: s -> true
  | SwffiT(WffiArrow(WffiNot p1,p2)) :: s -> true
  | SwffiT(WffiArrow(WffiArrow(p1,p2),p3)) :: s -> true
  | SwffiFc(WffiArrow(p1,p2)) :: s -> true
  | SwffiFc(WffiNot p) :: s  -> true
  | SwffiFc(WffiAnd(p1,p2)) :: s -> true
  | _ :: s -> member_for_Ci_rule s
  | [] -> false

(* let rec opt1 *)

let rec delta_s = function
  | [] -> []
  | SwffiT(WffiAtom p)  as h :: s -> h :: delta_s s
  | SwffiF(WffiAtom p)  as h :: s -> h :: delta_s s
  | SwffiFc(WffiAtom p) as h :: s -> h :: delta_s s
  | _ :: s -> delta_s s

(* let rec sigma = function *)
(*   | SwffiT(WffiAtom p)::s -> (p,true) *)
(*   | _ -> *)


let rec solve_contra wffnum s =
  let s = set_of_list s in
  begin
    match s with
    | [] -> failwith "no include s"
    | s when comp_pair s -> true (* Format.printf "close s " *) (* failwith "closed s" *)
    | s -> solve_C1 wffnum s
  end


and solve_C1 wffnum s =
  let s = set_of_list s in
  begin
    match s with
    | [] -> failwith "no include s"
    | SwffiT(WffiAnd(p1, p2)) :: s -> solve_contra wffnum (SwffiT p1 :: SwffiT(p2) :: s)
    | SwffiF(WffiOr(p1, p2)) :: s  -> solve_contra wffnum (SwffiF p1 :: SwffiF(p2) :: s)
    | SwffiFc(WffiOr(p1, p2)) :: s -> solve_contra wffnum (SwffiFc p1 :: SwffiFc(p2) :: s)
    | SwffiT(WffiArrow(WffiAtom p1, p2)) :: s when List.mem (SwffiT(WffiAtom(p1))) s = true -> solve_contra wffnum (SwffiT p2 :: s)
    | SwffiT(WffiAtom p) :: s as ss when mem_atom_arrow (WffiAtom p) s -> solve_contra wffnum (remove_atom_arrow_plus_atom (WffiAtom p) ss)
    | SwffiT(WffiNot p) :: s -> solve_contra wffnum ((SwffiFc p)::s)
    | SwffiT(WffiArrow(WffiAnd(p1,p2),p3)) :: s -> solve_contra wffnum (SwffiT(WffiArrow(p1,WffiAnd(p1, p2))) :: s)
    | SwffiT(WffiArrow(WffiOr(p1,p2),p3)) :: s -> solve_contra (wffnum+1) (SwffiT(WffiArrow(p1,WffiAtom wffnum))::SwffiT(WffiArrow(p2,WffiAtom wffnum))::SwffiT(WffiArrow(WffiAtom wffnum,p3)) :: s)
    | hs -> solve_C2 wffnum hs
  end

and solve_C2 wffnum s =
  let s = set_of_list s in
  begin
    match s with
    | [] -> failwith "no include s"
    | SwffiF(WffiAnd(p1,p2)) :: s -> solve_contra wffnum (SwffiF(p1) :: s) &&
                                     solve_contra wffnum (SwffiF(p2) :: s)
    | SwffiT(WffiOr(p1,p2)) :: s -> solve_contra wffnum (SwffiT(p1) :: s) &&
                                    solve_contra wffnum (SwffiT(p2) :: s)
    | hs -> solve_C3 wffnum hs
  end

and solve_C3 wffnum s =
  let s = set_of_list s in
  begin
    match s with
    | [] -> failwith "no include s"
    | SwffiF(WffiNot p) :: s -> let sc = s_to_sc s in solve_contra wffnum ((SwffiT p) :: sc)
    | SwffiF(WffiArrow(p1,p2)) :: s -> let sc = s_to_sc s in solve_contra wffnum (SwffiT(p1) :: SwffiF(p2) :: sc)
    | hs -> solve_C4 wffnum hs
  end

and solve_C4 wffnum s =
  let s = set_of_list s in
  begin
    match s with
    | [] -> failwith "no include s"
    | SwffiT(WffiArrow(WffiNot p1,p2)) :: s -> let sc = s_to_sc s in
                                               solve_contra wffnum (SwffiT p1 :: sc) &&
                                               solve_contra wffnum (SwffiT p2 :: s)
    | SwffiT(WffiArrow(WffiArrow(p1,p2),p3)) :: s -> let sc = s_to_sc s in
                                                     solve_contra (wffnum+1) (SwffiT(p1)::SwffiF(WffiAtom wffnum)::SwffiT(WffiArrow(WffiAtom wffnum,p3))::SwffiT(WffiArrow(p2,WffiAtom wffnum)):: sc) && solve_contra wffnum (SwffiT p3 :: s)
    | hs -> solve_C5 wffnum hs
  end

and solve_C5 wffnum s =
  let s = set_of_list s in
  begin
    match s with
    | [] -> failwith "no include s"
    | SwffiFc(WffiArrow(p1,p2)) :: s -> let sc = s_to_sc s in
                                        solve_contra wffnum (SwffiT p1 :: SwffiFc p2 :: sc)
    | SwffiFc(WffiNot p) :: s -> let sc = s_to_sc s in
                                 solve_contra wffnum (SwffiT p :: sc)
    | hs -> solve_C6 wffnum hs
  end

and solve_C6 wffnum s =
  let s = set_of_list s in
  begin
    match s with
    | [] -> failwith "no include s"
    | SwffiFc(WffiAnd(p1,p2)) :: s -> let sc = s_to_sc s in
                                      solve_contra wffnum (SwffiFc p1 :: sc) &&
                                      solve_contra wffnum (SwffiFc p2 :: sc)
    | h :: s -> backtrack wffnum (s @ [h])
    (* | hs -> backtrack wffnum hs *)
  end

and backtrack wffnum s =
  let s = set_of_list s in
  begin
    if member_for_Ci_rule s then solve_contra wffnum s else false(* failwith "not provable" *) (* Format.printf "null " *)
  end


(* 新しいatomはwffnumにする *)
let solve wffnum swffi =
  let swffilist = [swffi] in
  solve_contra wffnum swffilist

let t_conj (s:int * wff list) (swff:int * wff) =
  match swff with
  | (0,WffAnd(p,q)) -> [(0,p);(0,q)]
  | _ -> raise (Invalid_argument "not given SwffAnd T")

let f_conj (s:int * wff list) (swff:int * wff) =
  match swff with
  | (1,WffAnd(p,q)) -> [[(1,p)];[(1,q)]]
  | _ -> raise (Invalid_argument "not given SwffAnd F")

let fc_conj (s:int * wff list) (swff:int * wff) =
  match swff with
  | (2,WffAnd(p,q)) -> [(2,p);(2,q)]
  | _ -> raise (Invalid_argument "not given SwffAnd Fc")


               (* let f_conj swff = *)


               (* [swff] -> tableau_tree *)
               (* let proof s =  *)

               (* let decide s *)
               (* proof:swffの集合Sを引数に取り証明図を返す *)
               (* 展開規則:swffの集合S と そのSから選んだ1つのswffのH を引数に取り，*)
