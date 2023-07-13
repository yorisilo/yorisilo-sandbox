(*
 This file is a implementation of Tableau based method intuitionistic propositional logic proover.
 Classical one is in clprv.ml
 *)
type atom = string;;    (* propositional letters *)

type formula =
  | Atom of atom
  | Or of formula * formula
  | And of formula * formula
  | If of formula * formula
  | Not of formula
;;
type swff =
  | True of formula
  | False of formula
  | Cfalse of formula
;;
type sign =
  | Pos       (* True *)
  | Neg       (* False *)
  | Cng       (* CFalse *)
;;

(* Interpretation function of a model: assignment of truth values
   to propositional letters (atoms)
*)
(* module type Interpretation = sig *)
(*   type t *)
(*   val empty : t *)
(*   (\* return None if adding a new atom leads to a contradiction, *)
(*      that is, inconsistent model *)
(*   *\) *)
(*   val insert : atom -> sign -> t -> t option *)
(*   (\* to print out the interpretation *\) *)
(*   val to_list : t -> (atom * sign) list *)
(*   val mem_pos : atom -> t -> bool *)
(*   val to_c : t -> t *)
(* end *)

(* module I : Interpretation = struct *)
module I = struct
  module S = Set.Make (struct type t = atom let compare = compare end)
  type t = {pos: S.t; neg: S.t; cng: S.t}

  let empty = {pos = S.empty; neg = S.empty; cng = S.empty}

  let insert (atom:atom) sign t = match sign with
    | Pos ->                     (* adding a positive atom *)
      if (S.mem atom t.neg) || (S.mem atom t.cng) then None     (* inconsistency *)
      else Some {t with pos = S.add atom t.pos}
    | Neg ->                     (* adding a negative atom *)
      if S.mem atom t.pos then None     (* inconsistency *)
      else Some {t with neg = S.add atom t.neg}
    | Cng ->      (* adding a strong negative atom  *)
      if S.mem atom t.pos then None     (* inconsistency *)
      else Some {t with cng = S.add atom t.cng}

  let to_list t = List.map (fun s -> (s,Pos)) (S.elements t.pos) @
                  List.map (fun s -> (s,Neg)) (S.elements t.neg) @
                  List.map (fun s -> (s,Cng)) (S.elements t.cng)

  let mem_pos x t = S.mem x t.pos

  let to_c t = {pos = t.pos; neg = S.empty; cng = t.cng}
end;;

(* module type MONADPLUS = sig *)
(*   type 'a t *)
(*   val ret : 'a -> 'a t *)
(*   val bind : 'a t -> ('a -> 'b t) -> 'b t *)
(*   val mzero : 'a t *)
(*   val mplus : 'a t -> 'a t -> 'a t *)
(*   val mrun : 'a t -> 'a option *)
(*   val to_list : 'a t -> 'a list *)
(* end *)

(* module L : MONADPLUS = struct *)
module L = struct
  type 'a streamV =
    | Nil
    | Cons of 'a * 'a stream
  and 'a stream =
    unit -> 'a streamV;;

  type 'a t = 'a stream
  let ret x = fun () -> Cons(x,(fun () ->  Nil))
  let mzero = fun () -> Nil
  let rec mplus x y =
    match x() with
    | Nil -> y
    | Cons(h,t) -> (fun () -> Cons(h, mplus t y))
  let rec bind l f =
    match l() with
    | Nil -> fun() -> Nil
    | Cons(h,t) -> mplus (f h) (bind t f)
  let mrun x =
    match x() with
    | Nil -> None
    | Cons(h, t) -> Some h
  let rec to_list x =
    match x() with
    | Nil -> []
    | Cons(h, t) -> h :: (to_list t)
end

open L;;

let maybe : 'omega -> ('a -> 'omega) -> 'a option -> 'omega =
  fun o f a ->
    match a with
    | Some x -> (f x)
    | None -> o
;;

(* Takes an interpretation, initially empty, and returns a model
   of None if none exists
*)

(* make fresh name variables *)
let t = ref 0 ;;
let newvar = fun () ->
  t := !t + 1 ;
  "x_" ^ string_of_int !t ;;

let rec simplify : I.t -> swff list -> (I.t * swff list) L.t = fun i0 fs ->
  (* Simpify the list of swff by applying rules of group 1 until none applies or contradiction is found. *)
  let rec loop : I.t -> swff list -> swff list -> (I.t * swff list) L.t = fun i acc -> function
    | [] -> if i==i0 then ret (i, acc) else simplify i acc
    | h :: t -> inner i acc t h
  and
    inner : I.t -> swff list -> swff list -> swff -> (I.t * swff list) L.t = fun i acc jq -> function
    (* Group 1 : no backtracking, no branching *)
    | True(Atom(s)) -> maybe mzero (fun i' -> loop i' acc jq) (I.insert s Pos i)
    | False(Atom(s)) -> maybe mzero (fun i' -> loop i' acc jq) (I.insert s Neg i)
    | Cfalse(Atom(s)) -> maybe mzero (fun i' -> loop i' acc jq) (I.insert s Cng i)
    | True(And(t1, t2)) -> loop i acc ( True(t1)  :: True(t2)  :: jq)
    | False(Or(t1, t2)) -> loop i acc ( False(t1) :: False(t2) :: jq)
    | Cfalse(Or(t1, t2)) -> loop i acc ( Cfalse(t1) :: Cfalse(t2) :: jq)
    | True(If(Atom(s), t2)) when (I.mem_pos s i) -> loop i acc (True(t2)::jq)
    | True(Not(t)) -> loop i acc ((Cfalse t) :: jq)
    | True(If(And(t1, t2), t3)) -> loop i acc (True(If(t1, If(t2, t3))) :: jq)
    | True(If(Or(t1, t2), t3)) ->
      let p = Atom(newvar()) in
      loop i acc ( (True(If(t1, p))) :: (True(If(t2, p))) :: (True(If(p, t3))) :: jq)
    (* default case *)
    | h -> loop i (h::acc) jq
  in
  loop i0 [] fs ;;

let rec pick_backtrack  : swff list -> (swff list * swff list) option = function
  | [] -> None
  | False(And(a, b)) :: t -> Some (False(a) :: t, False(b) :: t)
  | True(Or(a, b)) :: t -> Some (True(a) :: t, True(b) :: t)
  (* | True(If(Not(a), b)) :: t -> Some (True(a) :: t, True(b) :: t) *)
  (* | True(If(If(a, b), c)) :: t ->  *)
  (*      let p = Atom(newvar()) in *)
  (*      Some ( *)
  (*   True(a) :: False(p) :: True(If(p, c)) :: True(If(b, p)) :: t, *)
  (*   True(c) :: t *)
  (*      ) *)
  (* | True(If(Atom(s),b)) :: t -> Some (False(Atom(s)) :: t, True(Atom(s)) :: True(b) :: t)   (\* This rule is needed for only classical case. *\) *)
  | h::t -> maybe None (fun (ls1, ls2) -> Some (h::ls1, h::ls2)) (pick_backtrack t) ;;

let cleanup : I.t -> swff list -> I.t * swff list = fun i ls ->
  (* take interpretation and swff list and remove Cng atoms from i and Cfalse swff from ls. *)
  (I.to_c i,
   List.filter (function
       | False(t) -> false
       | x -> true) ls
  )

let rec find_model : I.t -> swff list -> I.t L.t = fun i ->
  function
  | [] -> ret i
  | ls -> bind (simplify i ls) @@ function
    | (i, []) -> ret i
    | (i, ls) ->
      begin
        match pick_backtrack ls with
        | None -> try_to_break i ls
        | Some(ls1, ls2) -> mplus (find_model i ls1) (find_model i ls2)
      end
and
  try_to_break : I.t -> swff list -> I.t L.t = fun i ls ->
  (* Take not empty list and pick 1 formula and apply G3-G6 searching for contradiction.
     Fail if contradiction found and otherwise return a interpretation.*)
  let rec loop : I.t -> I.t option -> swff list -> swff list -> I.t L.t = fun i io acc ->  function
    | [] -> maybe mzero ret io
    | h :: t -> inner i acc t h
  and
    inner : I.t -> swff list -> swff list -> swff -> I.t L.t = fun i acc t h ->
    match h with
    (* Group 3 *)
    | False(If(a,b)) -> check_contradiction i acc t h [True(a); False(b)]
    | False(Not(a)) -> check_contradiction i acc t h [True(a)]
    (* Group 5 *)
    | Cfalse(If(a,b)) -> check_contradiction i acc t h [True(a); Cfalse(b)]
    | Cfalse(Not(a)) -> check_contradiction i acc t h [True(a)]
    (* Group 4 *)
    | True(If(Not(a), b)) ->
    (*
   let S = t@acc
       h = True(If(Not(a), b))
       if S, T(B) has the model then S,h has the model,
       but if cleaned-S, T(a) has the model does not mean S,h has the model, so we have to keep looking
   *)
      begin
        match mrun (find_model i (True(b)::(t@acc))) with
        | Some i' -> ret i'
        | None -> check_contradiction i acc t h [True(a)]
      end
    | True(If(If(a, b), c)) ->
      begin
        match mrun (find_model i (True(c)::(t@acc))) with
        | Some i' -> ret i'
        | None ->
          let p = Atom(newvar()) in
          check_contradiction i acc t h (True(a)::False(p)::True(If(p, c))::True(If(b, p))::(t@acc))
      end
    (* Group 6 *)
    | Cfalse(And(a, b)) ->
      (* Most ambiguous case
         let S = t@acc
          h = Cfalse(And(a,b))
          if cleaned-S,Cfalse(b) has the model does not mean S,h has the model and same for contradiction, we need to search more.
      *)
      let (i', ls') = cleanup i (acc@t) in
      begin
        match mrun (mplus (find_model i' (Cfalse(a)::ls')) (find_model i' (Cfalse(b)::ls'))) with
        | None -> mzero
        | Some i2 -> loop i (Some i2) (h::acc) t (* We need to backtrack for another formulas using interpretation whicn contains information of CF(And(a,b)).  *)
      end
    (* Exceptional pattern *)
    | True(If(Atom(s), b)) ->
      assert (Pervasives.not (I.mem_pos s i));
      (* Satisfactory solution but this solution lost information to construct kripke model *)
      maybe mzero (fun i' -> loop i (Some i') (h::acc) t) (I.insert s Neg i)
  and
    check_contradiction : I.t -> swff list -> swff list -> swff -> swff list -> I.t L.t = fun i acc t h ls ->
    (* if cleaned-up model has a contradiction then fail else search again *)
    let (i', ls') = cleanup i (acc@t) in
    begin
      match mrun (find_model i' (ls@ls')) with
      | None -> mzero
      | Some i2 -> loop i (Some i2) (h::acc) t
    end
  in
  loop i None [] ls;;

(* We have TODOs.
   1. Kripke model
   2. Optimization
   3. More comment
*)

(* let unit_propagation : formula list -> formula list = fun ls -> in *)
(* let rec clausep = function *)
(*   | Atom(s) -> true *)
(*   | And(a,b) -> (clausep a) && (clausep b) *)
(*   | _ -> false *)
(* in *)
(* let loop : formula -> formula list -> formula list = fun ls [] -> *)
(*   match ls with *)
(*   | [] -> *)
(*   | h :: t -> inner h t acc *)
(* and *)
(*   inner : formula -> formula list -> formula list = fun h t acc -> *)
(*   match h with *)

let not x = Not x;;
let (&) x y = And(x,y);;
let ( |. ) x y = Or(x,y);;
let (=>) x y = If(x,y);;
let ( <=> ) x y = (x => y) & (y => x);;
let prove f = maybe None (fun x -> Some (I.to_list x)) @@ mrun @@ find_model I.empty [(False(f))] ;;

let p1 = Atom "p1" ;;
let p2 = Atom "p2" ;;
let p3 = Atom "p3" ;;
let a = Atom "a" ;;
let b = Atom "b" ;;

prove (If(a, b)) ;;
prove (If(Or(a, b), Or(a, b))) ;;
(* let None = prove (If(And(a, b), And(a, b)));; *)
(* let None = prove (If(And(a, b), Or(a, b))) ;; *)
(* let Some x = prove (If(Or(a, b), And(a, b))) ;; *)
(* let Some x = prove (And(Or(a, Not(a)), (Not a)));; *)
(* let Some x = prove ((a |. not a) & not a);; *)
(* let Some x = prove (not ((a |. not a) & not a));; *)

(* SYJ201+1.001.p *)
prove
  ((
    ( ( p1 <=> p2)  => ( p1 & ( p2 & p3 ) ))
    &
    ( ( p2 <=> p3)  => ( p1 & ( p2 & p3 ) ))
    &
    ( ( p3 <=> p1)  => ( p1 & ( p2 & p3 ) ))
  )
    =>
    ( p1 & ( p2 & p3 ) )
  )
;;


prove
  (not ((
       ( ( p1 <=> p2)  => ( p1 &  p2 ) )
       &
       ( ( p2 <=> p1)  => ( p2 &  p1 ) )
     )
       =>
       ( p1 & p2 )
     ));;

prove (If(a, not (not a)));;
prove (If((not (not a), a)));;

(* for i = 1 to 20 do *)
(*   Printf.printf "let a%d = Atom \"a%d\" in\n" i i *)
(* done;; *)
(* let a1 = Atom "a1" in *)
(* let a2 = Atom "a2" in *)
(* let a3 = Atom "a3" in *)
(* let a4 = Atom "a4" in *)
(* let a5 = Atom "a5" in *)
(* let a6 = Atom "a6" in *)
(* let a7 = Atom "a7" in *)
(* let a8 = Atom "a8" in *)
(* let a9 = Atom "a9" in *)
(* let a10 = Atom "a10" in *)
(* let a11 = Atom "a11" in *)
(* let a12 = Atom "a12" in *)
(* let a13 = Atom "a13" in *)
(* let a14 = Atom "a14" in *)
(* let a15 = Atom "a15" in *)
(* let a16 = Atom "a16" in *)
(* let a17 = Atom "a17" in *)
(* let a18 = Atom "a18" in *)
(* let a19 = Atom "a19" in *)
(* let a20 = Atom "a20" in *)
(* prove *)
(*   ( *)
(*     ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( ( not(not (a1)) <=> a2)  <=> a3)  <=> a4)  <=> a5)  <=> a6)  <=> a7)  <=> a8)  <=> a9)  <=> a10)  <=> a11)  <=> a12)  <=> a13)  <=> a14)  <=> a15)  <=> a16)  <=> a17)  <=> a18)  <=> a19)  <=> a20)  <=> ( a20 <=> ( a19 <=> ( a18 <=> ( a17 <=> ( a16 <=> ( a15 <=> ( a14 <=> ( a13 <=> ( a12 <=> ( a11 <=> ( a10 <=> ( a9 <=> ( a8 <=> ( a7 <=> ( a6 <=> ( a5 <=> ( a4 <=> ( a3 <=> ( a2 <=> a1) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) *)
(*   );; *)


(* (\* Peirce's formula and variations *\) *)
(* let p = Atom "P";; *)
(* let q = Atom "Q";; *)
(* let p1 = If(If(If(p, q), p), p);; *)
(* (\* let pn = fun pn1 ->  *\) *)


(* let rec pn = function *)
(*   | 1 -> p1 *)
(*   | n -> let pn1 = pn (n - 1) in *)
(*     let nv = Atom(newvar()) in *)
(*     If(If(If(nv, pn1), nv), nv);; *)


(* for i = 1 to 4 do *)
(*   for j = 1 to 4 do *)
(*     Printf.printf "let o%d%d = Atom \"o%d%d\" in\n" i j i j *)
(*   done *)
(* done;; *)

(* (\* SYJ202+1.003 : ILTP v1.1.2 *\) *)
(* let syj202 = *)
(*   let o11 = Atom "o11" in *)
(*   let o12 = Atom "o12" in *)
(*   let o13 = Atom "o13" in *)
(*   let o14 = Atom "o14" in *)
(*   let o21 = Atom "o21" in *)
(*   let o22 = Atom "o22" in *)
(*   let o23 = Atom "o23" in *)
(*   let o24 = Atom "o24" in *)
(*   let o31 = Atom "o31" in *)
(*   let o32 = Atom "o32" in *)
(*   let o33 = Atom "o33" in *)
(*   let o34 = Atom "o34" in *)
(*   let o41 = Atom "o41" in *)
(*   let o42 = Atom "o42" in *)
(*   let o43 = Atom "o43" in *)
(*   let o44 = Atom "o44" in *)
(*   let ax1 = ( o11 |. ( o12 |. o13 ) ) in *)
(*   let ax2 = ( o21 |. ( o22 |. o23 ) ) in *)
(*   let ax3 = ( o31 |. ( o32 |. o33 ) ) in *)
(*   let ax4 = ( o41 |. ( o42 |. o43 ) ) in *)
(*   If(ax1 & ax2 & ax3 & ax4, *)
(*      ( ( o11 & o21 ) |. ( ( o11 & o31 ) |. ( ( o11 & o41 ) |. ( ( o21 & o31 ) |. ( ( o21 & o41 ) |. ( ( o31 & o41 ) |. ( ( o12 & o22 ) |. ( ( o12 & o32 ) |. ( ( o12 & o42 ) |. ( ( o22 & o32 ) |. ( ( o22 & o42 ) |. ( ( o32 & o42 ) |. ( ( o13 & o23 ) |. ( ( o13 & o33 ) |. ( ( o13 & o43 ) |. ( ( o23 & o33 ) |. ( ( o23 & o43 ) |. ( o33 & o43 ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) ) *)
(*     );; *)

(* prove syj202;; *)

(* (\* SYJ212+1.010 : ILTP v1.1.2 *\) *)
(* let syj212 = *)
(*   let a1 = Atom "a1" in *)
(*   let a2 = Atom "a2" in *)
(*   let a3 = Atom "a3" in *)
(*   let a4 = Atom "a4" in *)
(*   let a5 = Atom "a5" in *)
(*   let a6 = Atom "a6" in *)
(*   let a7 = Atom "a7" in *)
(*   let a8 = Atom "a8" in *)
(*   let a9 = Atom "a9" in *)
(*   let a10 = Atom "a10" in *)
(*   ( ( ( ( ( ( ( ( ( ( not(not(a1)) <=> a2)  <=> a3)  <=> a4)  <=> a5)  <=> a6)  <=> a7)  <=> a8)  <=> a9)  <=> a10)  <=> ( a10 <=> ( a9 <=> ( a8 <=> ( a7 <=> ( a6 <=> ( a5 <=> ( a4 <=> ( a3 <=> ( a2 <=> a1) ) ) ) ) ) ) ) ) );; *)

(* (\* SYJ208+1.002 : ILTP v1.1.2 *\) *)
(* let syj208 = *)
(*   let o11 = Atom "o11" in *)
(*   let o12 = Atom "o12" in *)
(*   let o13 = Atom "o13" in *)
(*   let o14 = Atom "o14" in *)
(*   let o21 = Atom "o21" in *)
(*   let o22 = Atom "o22" in *)
(*   let o23 = Atom "o23" in *)
(*   let o24 = Atom "o24" in *)
(*   let o31 = Atom "o31" in *)
(*   let o32 = Atom "o32" in *)
(*   let o33 = Atom "o33" in *)
(*   let o34 = Atom "o34" in *)
(*   let o41 = Atom "o41" in *)
(*   let o42 = Atom "o42" in *)
(*   let o43 = Atom "o43" in *)
(*   let o44 = Atom "o44" in *)
(*   let ax1 = ( o11 |. not(not(o12)) ) in *)
(*   let ax2 = ( o21 |. not(not(o22)) ) in *)
(*   let ax3 = ( o31 |. not(not(o32)) ) in *)
(*   If(ax1 & ax2 & ax3, ( ( o11 & o21 ) |. ( ( o11 & o31 ) |. ( ( o21 & o31 ) |. ( ( o12 & o22 ) |. ( ( o12 & o32 ) |. ( o22 & o32 ) ) ) ) ) ));; *)


(* (\* SYJ209+1.010 : ILTP v1.1.2 *\) *)
(* let syj209 = *)
(*   let a1 = Atom "a1" in *)
(*   let a2 = Atom "a2" in *)
(*   let a3 = Atom "a3" in *)
(*   let a4 = Atom "a4" in *)
(*   let a5 = Atom "a5" in *)
(*   let a6 = Atom "a6" in *)
(*   let a7 = Atom "a7" in *)
(*   let a8 = Atom "a8" in *)
(*   let a9 = Atom "a9" in *)
(*   let a10 = Atom "a10" in *)
(*   let f = Atom "f" in *)
(*   If(( ( ( a1 & ( a2 & ( a3 & ( a4 & ( a5 & ( a6 & ( a7 & ( a8 & ( a9 & a10 ) ) ) ) ) ) ) ) ) |. ( ( not(not(a1)) => f)  |. ( ( a2 => f)  |. ( ( a3 => f)  |. ( ( a4 => f)  |. ( ( a5 => f)  |. ( ( a6 => f)  |. ( ( a7 => f)  |. ( ( a8 => f)  |. ( ( a9 => f)  |. ( a10 => f)  ) ) ) ) ) ) ) ) ) ) => f), *)
(*      f);; *)

(* (\* SYJ209+1.005 : ILTP v1.1.2 *\) *)
(* let syj2091 = *)
(*   let a1 = Atom "a1" in *)
(*   let a2 = Atom "a2" in *)
(*   let a3 = Atom "a3" in *)
(*   let a4 = Atom "a4" in *)
(*   let a5 = Atom "a5" in *)
(*   let a6 = Atom "a6" in *)
(*   let a7 = Atom "a7" in *)
(*   let a8 = Atom "a8" in *)
(*   let a9 = Atom "a9" in *)
(*   let a10 = Atom "a10" in *)
(*   let f = Atom "f" in *)
(*   If(( ( ( a1 & ( a2 & ( a3 & ( a4 & a5 ) ) ) ) |. ( ( not(not(a1)) => f)  |. ( ( a2 => f)  |. ( ( a3 => f)  |. ( ( a4 => f)  |. ( a5 => f)  ) ) ) ) ) => f), *)
(*      f);; *)


(* let syj2092 = *)
(*   let a1 = Atom "a1" in *)
(*   let f = Atom "f" in *)
(*   If(  ( ( a1 |. ( not(not(a1)) => f)  ) => f), *)
(*        f);; *)
