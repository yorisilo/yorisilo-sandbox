open Printf

let rate = 114.32;;

let usd_to_jpy usd =
  let jpy_base = floor (usd *. rate +. 0.5) in
  int_of_float jpy_base
;;

let jpy_to_usd jpy =
  floor (float_of_int jpy *. 10. /. rate) /. 10.
;;
