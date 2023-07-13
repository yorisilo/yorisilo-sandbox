(* タブロー法による証明 *)
open Term
open Format

let wff_to_init wff w =
  match wff with
  | _ as wff -> Node(TabFrm(PrvblWff(w,false,wff),false),Empty,Empty)

(* (\* wffを引数に取り，証明図を返す *\) *)
(* let prove wff = *)
(*   begin *)
(*     match wff with *)
(*     |  -> *)
(*   end *)

(* 展開規則
 * ||- /\ prvAnd
 * \||- /\ notprvAnd
 * ||- \/ prvOr
 * \||- \/ notprvOr
 * ||- -> prvImp
 * \||- -> notprvImp
 * ||- not prvNot
 * \||- not notprvNot
 * ||-  prv
 *)


(* let rec insert_direct x = function *)
(*   | Node(y,[]) -> Node(y,[x]) *)
(*   | Node(y,[h]) -> Node (y,[insert_direct h]) *)

(* let rec insertright x = function *)
(*   | Empty -> Node(x,Empty,Empty) *)
(*   | Node(y,left,right) -> Node (y,left,(insertright x right)) *)

(* * ||- /\ prvAnd *)
let rec prv_and w p q tree =
  match tree with
  | Empty -> Empty
  | Node(e,Empty,Empty) -> Node(e,Node(TabFrm(PrvblWff(w,true,p),false),Node(TabFrm(PrvblWff(w,true,p),false),Empty,Empty),Empty),Empty)
  | Node(TabFrm(PrvblWff(w,true,WffAnd(p1,q1)),bool),t1,t2) -> Node(TabFrm(PrvblWff(w,false,WffAnd(p1,q1)),true), prv_and w p1 q1 t1, prv_and w p1 q1 t2)
  | _ -> failwith "this is not expression ||- /\\ prvAnd"


(* \||- /\ notprvAnd *)
let rec notprv_and w p q tree =
  match tree with
  | Empty -> Empty
  | Node(e,Empty,Empty) -> Node(e,Node(TabFrm(PrvblWff(w,false,p),true),Empty,Empty),Node(TabFrm(PrvblWff(w,false,q),true),Empty,Empty))
  | Node(TabFrm(PrvblWff(w,false,WffAnd(p1,q1)),bool),t1,t2) -> Node(TabFrm(PrvblWff(w,false,WffAnd(p1,q1)),true), notprv_and w p1 q1 t1, notprv_and w p1 q1 t2)
  | _ -> failwith "this is not expression \\||- /\\ notprvAnd"

(* ||- \/ prvOr *)
let rec prv_or w p q tree =
  match tree with
  | Empty -> Empty
  | Node(e,Empty,Empty) -> Node(e,Node(TabFrm(PrvblWff(w,true,p),false),Empty,Empty),Node(TabFrm(PrvblWff(w,true,q),false),Empty,Empty))
  | Node(TabFrm(PrvblWff(w,true,WffOr(p1,q1)),bool),t1,t2) -> Node(TabFrm(PrvblWff(w,true,WffOr(p1,q1)),true), notprv_and w p1 q1 t1, notprv_and w p1 q1 t2)
  | _ -> failwith "this is not expression ||- \\/ prvOr"

let apply_rule tree =
  match tree with
  | Empty -> Empty
  | Node(TabFrm(PrvblWff(w,false,WffAnd(p,q)),bool),t1,t2) as node -> notprv_and w p q node
  | _ -> failwith "this is not WffAnd"


let rec find_not_apply_rule_tabform tree =
  match tree with
  | Empty -> Empty
  | Node(TabFrm(p,false),_,_) as node -> apply_rule node
  | Node(TabFrm(p,true),t1,t2) -> Node(TabFrm(p,true),find_not_apply_rule_tabform t1, find_not_apply_rule_tabform t2)
  | _ -> failwith "this is not hoge"

let proof tree =
  find_not_apply_rule_tabform tree

(* tree構造をもらってその枝リストのリストを返す *)
let rec branch_list tree =
  match tree with
  | Empty -> []
  (* | Node(TabFrm(p,_),Empty,Empty) -> [p] *)
  (* | Node(TabFrm(p,_),Node(TabFrm(q,_),Empty,Empty),Empty) -> [p;q] *)
  (* | Node(TabFrm(p,_),Node(TabFrm(q,_),Empty,Empty),Node(TabFrm(r,_),Empty,Empty)) -> [[p;q];[p;r]] *)
  | Node(TabFrm(p,_),t1,t2) -> if t2 = Empty then p::branch_list t1
                               else p::branch_list t1 @ p::branch_list t2
  | Node(_,_,_) -> []

let rec contradiction branch =
  match branch with
  | PrvblWff(w,true,WffAtom(p)) :: ps -> if List.exists (fun x -> x = PrvblWff(w,false,(WffAtom p))) branch then true else contradiction ps
  | PrvblWff(w,false,WffAtom(p)) :: ps -> if List.exists (fun x -> x = PrvblWff(w,true,(WffAtom p))) branch then true else contradiction ps
  | _::ps -> contradiction ps
  | [] -> false


(* bfs *)
let search e tree =
  let q = Queue.create () in
  Queue.add tree q;
  let rec loop () =
    try match Queue.pop q with
        | Empty -> loop ()
        | Node (e_, l, r) ->
           if e_ = e then true
           else
             begin
               Queue.add l q;
               Queue.add r q;
               loop ()
             end
    with
    | Queue.Empty -> false in
  loop ()

let all_true tree =
  let q = Queue.create () in
  Queue.add tree q;
  let rec loop () =
    try match Queue.pop q with
        | Empty -> loop ()
        | Node (TabFrm(_,bool), l, r) ->
           if bool = false then true
           else
             begin
               Queue.add l q;
               Queue.add r q;
               loop ()
             end
        | Node(_,l,r) ->
           begin
             Queue.add l q;
             Queue.add r q;
             loop ()
           end
    with
    | Queue.Empty -> false in
  loop ()



let rec find_false tree =
  if not (all_true tree) then
    begin
      let rec find_not_apply_rule_tabform tree =
        let q = Queue.create () in
        Queue.add tree q;
        let rec loop () =
          try match Queue.pop q with
              | Empty -> loop ()
              | Node (e_, l, r) ->
                 if e_ = e then Some e_
                 else
                   begin
                     Queue.add l q;
                     Queue.add r q;
                     loop ()
                   end
          with
          | Queue.Empty -> None in
        loop ()

             match tree with
             | Empty ->
             | Node(TabFrm(p,false),_,_) as node -> apply_rule node
             | Node(TabFrm(p,true),t1,t2) -> Node(TabFrm(p,true),find_false t1, find_false t2)
    end
  else
    tree


let search tree =
  let q = Queue.create () in
  Queue.add tree q;
  let rec loop () =
    try match Queue.pop q with
        | Node(e_,Empty,Empty) ->
        | Node (_, l, r) ->
           begin
             Queue.add l q;
             Queue.add r q;
             loop ()
           end
    with
    | Queue.Empty -> None in
  loop ()


let find_not_apply_rule_tabform tree =
  let q = Queue.create () in
  Queue.add tree q;
  let rec loop () =
    match Queue.pop q with
    | Empty -> loop ()
    | Node(TabFrm(pwff,bool),t1,t2) as n ->
       if bool = false then apply_rule n (* 部分木を返す *)

let find_not_apply_rule_tabform tree =
  let q = Queue.create () in
  Queue.add tree q;
  let rec loop () =
    match Queue.pop q with
    | Empty -> loop ()
    | Node(TabFrm(pwff,bool),t1,t2) as n ->
       if bool = false then apply_rule n (* 部分木を返す *)



(* bfs *)
let search e tree =
  let q = Queue.create () in
  Queue.add tree q;
  let rec loop () =
    try match Queue.pop q with
        | Empty -> loop ()
        | Node (e_, l, r) ->
           if e_ = e then Some e_
           else
             begin
               Queue.add l q;
               Queue.add r q;
               loop ()
             end
    with
    | Queue.Empty -> None in
  loop ()

(* treeの一番後ろに一本道のtab_treeを加える *)
(* let rec direct prvblwffs branch_tree = *)
(*   match prvblwffs with *)
(*   | t::ts -> (insertleft t branch_tree) *)

(* (\* treeの後ろに分岐したtab_tabtreeを加える *\) *)
(* let rec branch prvblwffs branch_tree = *)
(*   match prvblwffs with *)
(*   |  -> *)

(* let prvAnd prv_wff tree = *)
(*   match prv_wff with *)
(*   | TabFrm(PrvblWff(w,true,WffAnd(p,q)),false) -> insertleft (TabFrm(PrvblWff(w,true,q),false)) (insertleft (TabFrm(PrvblWff(w,true,p),false)) tree) *)
(*   | _ -> failwith "this is not expression ||- /\\ prvAnd" *)

(* let notprvAnd prv_wff tree = *)
(*   match prv_wff with *)
(*   | TabFrm(PrvblWff(w,false,WffAnd(p,q)),false) -> insertleft (TabFrm(PrvblWff(w,false,q),false)) (insertright (TabFrm(PrvblWff(w,false,p),false)) tree) *)
(*   | _ -> failwith "this is not expression \\||- /\\ notprvAnd" *)

(* let prvOr prv_wff tree = *)
(*   match prv_wff with *)
(*   | TabFrm(PrvblWff(w,true,WffOr(p,q)),false) -> insertleft (TabFrm(PrvblWff(w,false,p),false)) (insertright (TabFrm(PrvblWff(w,false,q),false)) tree) *)
(*   | _ -> failwith "this is not expression ||- \\/ prvOr" *)

(* let notprvOr prv_wff tree = *)
(*   match prv_wff with *)
(*   | TabFrm(PrvblWff(w,false,WffOr(p,q)),false) -> insertleft (TabFrm(PrvblWff(w,false,q),false)) (insertleft (TabFrm(PrvblWff(w,false,p),false)) tree) *)
(*   | _ -> failwith "this is not expression \\||- \\/ notprvOr" *)

(* let prvArrow prv_wff tree = *)
(*   match prv_wff with *)
(*   | TabFrm(PrvblWff(w,true,WffArrow(p,q)),false) -> *)
(*      let w' = w + 1 in *)
(*      let branch = insertright (TabFrm(PrvblWff(w,false,q),false)) (insertleft (TabFrm(PrvblWff(w,false,p),false)) Empty) in *)
(*      (insertleft (TabAcs(AcsWld(w,w'))) tree) *)
(*   | _ -> failwith "this is not expression ||- -> prvArrow" *)



(* let ref w = 0 in *)
(*     let notprvAnd h = match h with *)
(*       | TabFrm(PrvblWff(world w)) -> Node() *)


let decide prvblwff tree =
  search prvblwff tree

(* ランダムな形のタブロー図をつくる *)
(* let random_make_tree = *)


(* 論理式を受け取ってタブロー図を返す関数 w:world *)
let proof h w =
  let st = wff_to_init h w in
  st
