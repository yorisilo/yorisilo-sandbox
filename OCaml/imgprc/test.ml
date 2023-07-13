(* input [| R; G; B; R; G; B ...|] *)
let copy (w:int) (h:int) inp out =
  for i = 0 to w*h*3 - 1 do
    out.(i) <- inp.(i)
  done

let ngps (w:int) (h:int) inp out =
  for i = 0 to w*h*3 - 1 do
    out.(i) <- 255 - inp.(i)
  done

let binari (w:int) (h:int) inp out =
  for i = 0 to w*h*3 - 1 do
    out.(i) <- if inp.(i) > (255/2) then 255 else 0
  done

let test func (img:string) (outname:string) =
  let (w,h,i) = (Image_lib.load_image img) in
  let o = Array.make (w*h*3) 0 in
  func w h i o;
  Image_lib.save_image outname (w,h,o)

(* let img = load_image "kam.ppm" |> test ngps img |> save_image "kam_ngps.ppm" *)
(* Array.make w*h*3 0 *)
