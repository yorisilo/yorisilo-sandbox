let rec fib n =
  match n with
  | 1 | 2 -> 1, 1
  | _ ->
      let f_1, f_2 = fib (n-1) in
      f_1 + f_2, f_1

let fib n = fst (fib n)
