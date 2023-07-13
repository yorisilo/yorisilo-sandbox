// $.gQ.Animationで、background1.pngを使ってgameQueryの”アニメーション”を作成
var background1 = new $.gQ.Animation({imageURL: "background1.png"});

console.log($());

// 設定版playgroundで、ゲームの表示に使用する<div>要素を#playgroundにする
$("#playground").playground({height: 250, width: 700, keyTracker: true});
// backgroundという名前のレイヤー（透明なスプライト）を作成し、そこにbackground1という名前のスプライトを追加する。
// 追加するbackground1スプライトのanimation属性には、1行めで作成したbackground1アニメーションを指定する。
$.playground().addGroup("background", {width: 700, height: 250}).
	addSprite("background1", {animation: background1, width: 700, height: 250});

// 15ミリ秒おきに呼び出される関数（今の場合は無名関数）を登録する。
$.playground().registerCallback(function(){
	// ダイナミックに作成したスプライトbackground1のx位置を変更する
  $("#background1").x(($("#background1").x() - 1 - 250) % (-2 * 250) + 250);
}, 15);
// リソースをプリロードしてゲームを準備し、メインループを開始する
$.playground().startGame();