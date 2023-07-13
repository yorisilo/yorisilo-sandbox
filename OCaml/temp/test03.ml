(* データ定義 *)
type gakusei_t = {
         namae : string;
         tensuu : int;
         seiseki : string;
  }

(* 学生データの例 *)
let g1 = {namae="asai"; tensuu=70; seiseki="B"}
let g2 = {namae="junpei"; tensuu=90; seiseki="A"}
let g3 = {namae="yomo"; tensuu=60; seiseki="C"}

(* 目的：学生の成績データを受け取ったら，成績通知文を返す *)
(* tsuuchi：gakusei_t -> string *)
let tsuuchi gakusei = match gakusei with
  | {namae=n; tensuu=t; seiseki=s} -> "1"

(* テスト *)
let test1 = (tsuuchi g1 = "asai は B")
let test2 = (tsuuchi g2 = "junpei は A")
let test3 = (tsuuchi g3 = "yomo は C")
