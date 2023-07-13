open Parser
open Lexer
open Term
open Format


let () =
  let lexbuf = Lexing.from_channel stdin in
  begin try
    let tn = Parser.main Lexer.token lexbuf in
    (* eprintf "Term is %a@." (pp_print_pnterm 5) tn; *)
    let (t,env,num) = convert_name tn in
    (* eprintf "Term is %a@." (pp_print_pterm env 5) t; *)
    let t = swffif t in
    let time = Sys.time () in
    ignore (Tb_proof.solve num t);
    print_float (Sys.time () -. time);
    print_newline ()
    with
      | Parsing.Parse_error ->
         eprintf "Parse Error@."
  end
