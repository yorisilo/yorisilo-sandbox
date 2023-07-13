open Term

(*
 * general rules:
 * Antecedent:
 *   list of pair (Term,Number).
 *   Number is counted using ``anum''.
 * Succedent:
 *   pair of Term.
 *   1. sucR is usual succedent.
 *   2. sucL is special succedent for ->->L rules.
 * Atomic Proposition:
 *   fresh atomic proposition comes from ``pnum''.
 *)

let do_debug_sequent = true

let debug_sequent name ant1 ant2 sucL sucR =
  if do_debug_sequent then begin
    Format.eprintf "%s: " name;
    List.iter (fun (x,_) -> Format.eprintf "%a, "
      (print_wffi empty_env 0) x) (List.rev ant2);
    Format.eprintf ";; ";
    List.iter (fun (x,_) -> Format.eprintf "%a, "
      (print_wffi empty_env 0) x) ant1;
    begin match sucL with
    | None ->
        Format.eprintf "|- %a@."
          (print_wffi empty_env 0) sucR
    | Some sucLS ->
        Format.eprintf " [%a -> %a], |- %a@."
          (print_wffi empty_env 0) sucR
          (print_wffi empty_env 0) sucLS
          (print_wffi empty_env 0) sucR
    end
  end else ()

(* solve1: only use reversible rules *)

(*
 * solves [ant |- (sucR -> sucL) -> sucR ]
 * handles:
 * 1. |- (A -> B)
 * 2. |- (A /\ B)
 * 3. |- True
 *)
(* solve1_internal_s 0 pnum [] None p *)
let rec solve1_internal_s anum pnum ant sucL sucR =
  debug_sequent "1S" ant [] sucL sucR;
  begin match sucR with
  | WffiArrow (t1,t2) ->
      solve1_internal_s (anum+1) pnum ((t1,anum)::ant) sucL t2
  | WffiAnd (t1,t2) ->
      solve1_internal_s anum pnum ant sucL t1 &&
      solve1_internal_s anum pnum ant sucL t2
  | WffiTop -> true
  | _ -> solve1_internal_a1 anum pnum ant [] sucL sucR
  end

(*
 * solves [ant2 @ ant1 |- (sucR -> sucL) -> sucR ]
 * handles:
 *  1. (A <-> B) |-
 *  2. (A /\ B) |-
 *  3. (A \/ B) |-
 *  4. True |-
 *  5. False |-
 *  6. p |- p
 *  7. (True -> A) |-
 *  8. (False -> A) |-
 *  9. (A /\ B -> C) |-
 * 10. ((A <-> B) -> C) |-
 * 11. (A \/ B -> C) |-
 * note: only solve1_internal_{s,a1,a2} can call it.
 * note: ``ant2'' must not have propositions which can be handled in
 *   solve1_internal_a1.
 *)
and solve1_internal_a1 anum pnum ant1 ant2 sucL sucR =
  debug_sequent "1A1" ant1 ant2 sucL sucR;
  begin match ant1 with
  | [] -> solve1_internal_a2 anum pnum ant2 [] sucL sucR
  | (WffiAnd (t1,t2),ti) :: ant1t ->
      solve1_internal_a1 (anum+2) pnum
        ((t1,anum)::(t2,anum+1)::ant1t) ant2 sucL sucR
  | (WffiOr (t1,t2),ti) :: ant1t ->
      solve1_internal_a1 (anum+1) pnum
        ((t1,anum)::ant1t) ant2 sucL sucR &&
      solve1_internal_a1 (anum+1) pnum
        ((t2,anum+1)::ant1t) ant2 sucL sucR
  | (WffiTop,ti) :: ant1t ->
      solve1_internal_a1 anum pnum ant1t ant2 sucL sucR
  | (WffiBot,ti) :: ant1t -> true
  | (WffiAtom p,ti) :: ant1t when sucR = WffiAtom p -> true
  | (WffiArrow (WffiTop,t3),ti) :: ant1t ->
      solve1_internal_a1 (anum+1) pnum
        ((t3,anum)::ant1t) ant2 sucL sucR
  | (WffiArrow (WffiBot,t3),ti) :: ant1t ->
      solve1_internal_a1 anum pnum ant1t ant2 sucL sucR
  | (WffiArrow (WffiAnd (t1,t2),t3),ti) :: ant1t ->
      solve1_internal_a1 (anum+1) pnum
        ((WffiArrow (t1,WffiArrow (t2,t3)),anum)::ant1t) ant2 sucL sucR
  (* | (WffiArrow (WffiEquiv (t1,t2),t3),ti) :: ant1t -> *)
  (*     solve1_internal_a1 (anum+1) pnum *)
  (*       ((WffiArrow (WffiArrow (t1,t2),WffiArrow (WffiArrow (t2,t1),t3)),anum)::ant1t) *)
  (*       ant2 sucL sucR *)
  | (WffiArrow (WffiOr (t1,t2),t3),ti) :: ant1t ->
      let p = WffiAtom pnum in
      solve1_internal_a1 (anum+3) (pnum+1) (
          (WffiArrow (t1,p),anum)::
          (WffiArrow (t2,p),anum+1)::
          (WffiArrow (p,t3),anum+2)::ant1t)
        ant2 sucL sucR
  | ant1h :: ant1t ->
      solve1_internal_a1 anum pnum ant1t (ant1h::ant2) sucL sucR
  end

(*
 * solves [ant2 @ ant1 |- (sucR -> sucL) -> sucR ]
 * handles:
 * 1. (p -> C) |- [ only handles when p is in (ant2 @ ant1). ]
 * note: only solve1_internal_{a1,a2} can call it.
 * note: ``ant2'' must not have propositions which can be handled in
 *   solve1_internal_a1 and solve1_internal_a2.
 *)
and solve1_internal_a2 anum pnum ant1 ant2 sucL sucR =
  debug_sequent "1A2" ant1 ant2 sucL sucR;
  begin match ant1 with
  | [] -> solve2_internal_s anum pnum ant2 sucL sucR
  | (WffiArrow (WffiAtom p,t3),ti) :: ant1t
      when List.exists (fun (x,_) -> x = WffiAtom p) ant1 ||
           List.exists (fun (x,_) -> x = WffiAtom p) ant2 ->
      solve1_internal_a1 (anum+1) pnum [(t3,anum)] (ant2@ant1t) sucL sucR
  | ant1h :: ant1t ->
      solve1_internal_a2 anum pnum ant1t (ant1h::ant2) sucL sucR
  end

(*
 * solves [ant |- (sucR -> sucL) -> sucR ]
 * handles:
 * 1. |- (A \/ B)
 *)
and solve2_internal_s anum pnum ant sucL sucR =
  debug_sequent "2S" ant [] sucL sucR;
  begin match sucR with
  | WffiOr (t1,t2) ->
      begin match sucL with
      | None ->
          solve1_internal_s anum pnum ant sucL t1 ||
          solve1_internal_s anum pnum ant sucL t2
      | Some sucLS ->
          let p = WffiAtom pnum in
          let sp = Some p in
          solve1_internal_s (anum+2) (pnum+1)
            ((WffiArrow (t2,p),anum)::(WffiArrow (p,sucLS),anum+1)::ant) sp t1 ||
          solve1_internal_s (anum+2) (pnum+1)
            ((WffiArrow (t1,p),anum)::(WffiArrow (p,sucLS),anum+1)::ant) sp t2
      end
  | _ -> false
  end || solve2_internal_a anum pnum ant [] sucL sucR

(*
 * solves [ant2 @ ant1 |- (sucR -> sucL) -> sucR ]
 * handles:
 * 1. ((A -> B) -> C) |-
 * note: ``ant2'' must not have propositions which can be handled in
 *   solve2_internal_a.
 *)
and solve2_internal_a anum pnum ant1 ant2 sucL sucR =
  debug_sequent "2A" ant1 ant2 sucL sucR;
  begin match ant1 with
  | [] -> false
  | ant1h :: ant1t -> begin match ant1h with
      | WffiArrow (WffiArrow (t1,t2),t3),ti ->
          begin match sucL with
          | None ->
              solve1_internal_s (anum+1) pnum
                ((t1,anum)::ant1t@ant2) (Some t3) t2
          | Some sucLS ->
              solve1_internal_s (anum+2) pnum
                ((WffiArrow (sucR,sucLS),anum)::(t1,anum+1)::ant1t@ant2)
                (Some t3) t2
          end &&
          solve1_internal_s (anum+1) pnum
            ((t3,anum)::ant1t@ant2) sucL sucR
      | _ -> false
      end ||
      solve2_internal_a anum pnum ant1t (ant1h::ant2) sucL sucR
  end

let solve pnum p =
  solve1_internal_s 0 pnum [] None p
