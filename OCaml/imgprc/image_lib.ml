let load_image fname =
  let ich = open_in_bin fname in
  let _ = input_line ich in
  let _ = input_line ich in
  let s = input_line ich in
  let _ = input_line ich in
  Scanf.sscanf s "%d %d" @@ fun width height -> 
    let image = Array.make (width * height * 3) 0 in
    for i = 0 to width * height * 3 - 1 do
      image.(i) <- int_of_char (input_char ich)
    done;
    close_in ich;
    (width, height, image)

let save_image fname (width, height, image) =
  let och = open_out_bin fname in
  output_string och "P6\n";
  output_string och "# CREATOR: Taka Image Lib (OCaml)\n";
  Printf.fprintf och "%d %d\n" width height;
  output_string och "255\n";
  for i = 0 to width * height * 3 - 1 do
    output_byte och image.(i)
  done

