// document.getElementById('choice').textContent = new Date();
// console.log(document.getElementById('choice').textContent);

// var todo = ['hoge', 'fuga', 'bar', 'bazz'];

// todo.push('unko');

// for(var i = 0, max = todo.length; i < max; i++) {
//   var li = document.createElement('li'); // タグの生成
//   li.textContent = todo[i];
//   document.getElementById('list').appendChild(li);
// }

// var book = {title: 'unko', price: '100000000'};

// for(var p in book){
//   console.log(p + '=' + book[p]);
// } // オブジェクトはプロパティの順序に無頓着にできてるので，forin 文でプロパティを読み取ろうとすると，場合によっては登録した順番通りにならないことがある．


// <input type="text" name="my_name"> たろう --> サーバーへは my_name="たろう" のような形で送信される．
// document.getElementById('form').onsubmit = function() {
//   var search = document.getElementById('form').word.value;
//   document.getElementById('output').textContent = '「' + search + '」の検索中．．．';
//   return false; // <form> は 送信ボタンがクリックされたら，入力されたデータをaction属性のURLへ送信する．URL の後ろに ?word=*** とあるが，これが送信しようとしたデータ．フォームの基本動作送信ボタンがクリックされたら，入力されたデータをaction属性のURLへ送信する．をキャンセルするために return false とする．
//   // HTMLタグの中には，<form>，<a> など，基本動作があらかじめ定義されているものがあるが，イベントを使って処理を行う場合，こうした基本動作はキャンセルすることがよくある．イベントで実行される関数に return false; が出てきたら，ああ，HTMLの基本動作をキャンセルしてるんだなと思おう．
// };

(function () {
  var now = new Date();
  var year = now.getFullYear();
  var month = now.getMonth();
  var date = now.getDate();
  var hour = now.getHours();
  var min = now.getMinutes();
  var sec = now.getSeconds();

  var output = year + '/' + (month + 1) + '/' + date + ' ' + hour + ':' + min + ':' + sec;

  document.getElementById('time').textContent = output;
}());

// jQuery(function() {
//   $(window).scroll(function () {
//     //var $target_pos = $('#target').offset().top;
//     var $target_pos = $('#target').get(0).offsetTop;
//   });
// });


// function Dog() {
//   Dog.prototype.bark = function(){
//     console.log('わんわん');
//   };
// }

// var dog = new Dog();
// dog.bark();
