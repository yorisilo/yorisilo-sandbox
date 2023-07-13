
module Stack = struct
  exception Empty

  type 'a stack =
    | SNil
    | SCell of 'a * 'a stack

  let create = SNil

  let push st x = SCell (x, st)

  let top = function
    | SNil -> raise Empty
    | SCell (x, _) -> x

  let pop = function
    | SNil -> raise Empty
    | SCell (_, st) -> st

  let is_empty st = st = SNil
end
