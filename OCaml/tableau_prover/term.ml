open Format
(* 論理式の型 *)
type wff =
  | WffAtom of string
  | WffArrow of wff * wff
  | WffOr of wff * wff
  | WffAnd of wff * wff
  | WffNot of wff
  | WffTop
  | WffBot

(* 符号付き論理式
 *)
type swff =
  | SwffT  of wff
  | SwffF  of wff
  | SwffFc of wff

(* eprintf "wff is %a@." (print_wff 5) (parse "A -> B -> ~A")*)
let rec print_wff pr ppf = function
  | WffAtom s ->
     fprintf ppf "%s" s
  | WffArrow (t1,t2) ->
     fprintf ppf "@[";
     if pr < 4 then fprintf ppf "(";
     fprintf ppf "%a@ ->@ %a"
             (print_wff 3) t1
             (print_wff 4) t2;
     if pr < 4 then fprintf ppf ")";
     fprintf ppf "@]"
  | WffAnd (WffArrow (t1,t2),WffArrow (t2t,t1t))
       when t1=t1t && t2=t2t ->
     fprintf ppf "@[";
     if pr < 5 then fprintf ppf "(";
     fprintf ppf "%a@ <->@ %a"
             (print_wff 4) t1
             (print_wff 4) t2;
     if pr < 5 then fprintf ppf ")";
     fprintf ppf "@]"
  | WffAnd (t1,t2) ->
     fprintf ppf "@[";
     if pr < 2 then fprintf ppf "(";
     fprintf ppf "%a@ /\\@ %a"
             (print_wff 1) t1
             (print_wff 2) t2;
     if pr < 2 then fprintf ppf ")";
     fprintf ppf "@]"
  | WffOr (t1,t2) ->
     fprintf ppf "@[";
     if pr < 3 then fprintf ppf "(";
     fprintf ppf "%a@ \\/@ %a"
             (print_wff 2) t1
             (print_wff 3) t2;
     if pr < 3 then fprintf ppf ")";
     fprintf ppf "@]"
  | WffTop ->
     fprintf ppf "True"
  | WffBot ->
     fprintf ppf "False"
  | WffNot t ->
     fprintf ppf "@[~%a@]"
             (print_wff 1) t

(* eprintf "Swff is %a@." (print_swff tn) *)
(* let rec print_swff ppf = function *)
(*   | SwffT(p) -> fprintf ppf "@[" *)
(*                         fprintf ppf "T:(%a" *)
(*                         (print_wff 5) p *)
(*                         fprintf ppf ")" *)
(*                         fprintf ppf "@]" *)


(* 論理式の型 *)
type wffi =
  | WffiAtom of int
  | WffiArrow of wffi * wffi
  | WffiOr of wffi * wffi
  | WffiAnd of wffi * wffi
  | WffiNot of wffi
  | WffiTop
  | WffiBot

(* 符号付き論理式
 *)
type swffi =
  | SwffiT  of wffi
  | SwffiF  of wffi
  | SwffiFc of wffi
  | Null

let swffit (t:wffi) =
  match t with
  | _ as t -> SwffiT(t)

let swffif (t:wffi) =
  match t with
  | _ as t -> SwffiF(t)

let swffifc (t:wffi) =
  match t with
  | _ as t -> SwffiFc(t)

type name_env = {
    dict : (string,int) Hashtbl.t;
    reverse_dict : (int,string) Hashtbl.t
  }

let new_name_env () = {
    dict = Hashtbl.create 10;
    reverse_dict = Hashtbl.create 100
  }
let empty_env = {
    dict = Hashtbl.create 10;
    reverse_dict = Hashtbl.create 100
  }

let rec convert_name_impl env num = function
  | WffAtom s ->
     begin try
         WffiAtom (Hashtbl.find env.dict s)
       with Not_found ->
         let t = WffiAtom !num in
         Hashtbl.add env.dict s !num;
         Hashtbl.add env.reverse_dict !num s;
         num := !num + 1;
         t
     end
  | WffArrow (t1,t2) ->
     WffiArrow (convert_name_impl env num t1,
                convert_name_impl env num t2)
  | WffAnd (WffArrow (t1,t2),WffArrow(t2t,t1t))
       when t1=t1t && t2=t2t ->
     let ct1 = convert_name_impl env num t1 in
     let ct2 = convert_name_impl env num t2 in
     WffiAnd (WffiArrow (ct1,ct2),WffiArrow(ct2,ct1))
  | WffAnd (t1,t2) ->
     WffiAnd (convert_name_impl env num t1,
              convert_name_impl env num t2)
  | WffOr (t1,t2) ->
     WffiOr (convert_name_impl env num t1,
             convert_name_impl env num t2)
  | WffNot t -> WffiNot (convert_name_impl env num t)
  | WffTop -> WffiTop
  | WffBot -> WffiBot

let convert_name tn =
  let env = new_name_env () in
  let num = ref 0 in
  let t = convert_name_impl env num tn in
  t, env, !num

(* eprintf "wff is %a@." (pp_print_pterm env 5) t *)
let rec print_wffi env pr ppf = function
  | WffiAtom n ->
      begin try
        fprintf ppf "%s" (Hashtbl.find env.reverse_dict n)
      with Not_found ->
        fprintf ppf "?%d" n
      end
  | WffiArrow (t1,t2) ->
      fprintf ppf "@[";
      if pr < 4 then fprintf ppf "(";
      fprintf ppf "%a@ ->@ %a"
        (print_wffi env 3) t1
        (print_wffi env 4) t2;
      if pr < 4 then fprintf ppf ")";
      fprintf ppf "@]"
  | WffiAnd (t1,t2) ->
      fprintf ppf "@[";
      if pr < 2 then fprintf ppf "(";
      fprintf ppf "%a@ /\\@ %a"
        (print_wffi env 1) t1
        (print_wffi env 2) t2;
      if pr < 2 then fprintf ppf ")";
      fprintf ppf "@]"
  | WffiOr (t1,t2) ->
      fprintf ppf "@[";
      if pr < 3 then fprintf ppf "(";
      fprintf ppf "%a@ \\/@ %a"
        (print_wffi env 2) t1
        (print_wffi env 3) t2;
      if pr < 3 then fprintf ppf ")";
      fprintf ppf "@]"
  | WffiNot t ->
     fprintf ppf "@[~%a@]"
             (print_wffi env 1) t
  | WffiTop ->
     fprintf ppf "\\top"
  | WffiBot ->
     fprintf ppf "\\bot"

(* 世界 *)
(* type world = *)
(*   | Wld of int *)

(* 到達可能な世界 *)
type accessibility_for_world =
  | AcsWld of int * int     (* 0<1 : 0から1へ到達可能 *)

(* ある世界で実現可能または不可能な論理式 0 ||- A -> B こういうのを表してる*)
type provable_wff =
  | PrvblWff of int * bool * wff

(* 式に展開規則を適用済みかどうか *)
(* type taked_expansion = bool *)

(* タブロー法での証明図における式たち ex. 0<1 とか 0 ||- A->B とか，そして式が展開規則を適用済みかどうかの情報を持っておく*)
type tab_form =
  | TabFrm of provable_wff * bool
  | TabAcs of accessibility_for_world
  | Maru
  | Batsu

(* タブロー法での証明図 *)
type tab_tree =
  | Empty
  | Node of tab_form * tab_tree * tab_tree

type branch =
  | Branch of wff list
  | BranchList of branch list
