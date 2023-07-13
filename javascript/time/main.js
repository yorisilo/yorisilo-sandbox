function clock() {
  var now = new Date();
  var date = now.getDate();
  var day = now.getDay();
  var hour = now.getHours();
  var min = now.getMinutes();
  var sec = now.getSeconds();

  var DEADLINE = 10;

  document.getElementById('clock1').style.color = 'white';

  if (hour >= 18 && min >= 30) {
    document.getElementById('clock1').style.color = '#ffaeb9';
  }
  if (hour >= 19 && min >= 0) {
    document.getElementById('clock1').style.color = '#ff6eb4';
  }

  if (hour < 10) {
    hour = "0" + hour;
  }
  if (min < 10) {
    min = "0" + min;
  }
  if (sec < 10) {
    sec = "0" + sec;
  }

  //console.log(hour);
  var clock1 = hour + ":" + min + ":" + sec;

  document.getElementById('clock1').innerHTML = clock1.toLocaleString();

  //window.setTimeout("clock()", 1000);
  // window.setTimeout(function() {
  //   clock();
  // }, 1000);

  var tid = window.setTimeout(clock, 1000);

  // if( hour > DEADLINE) {
  //   window.clearTimeout(tid);
  // }
}

/*
  色を変更（一定時間かけてだんだん色が変わる）
*/
function fade(elem, from, to) {
  // 変更前の元の色と変更後の情報
  var fromColor = new Color(from);
  var destColor = new Color(to);

  // fromの色をまずセットする
  elem.style.backgroundColor = from;

  // 経過時間に応じたrgb値を計算するeasing関数
  function easing(time, from, distance, duration) {
    return (time / duration) * distance + from;
  }

  //
  var begin = new Date() - 0;
  var distance_r = destColor.getRed() - fromColor.getRed();
  var distance_g = destColor.getGreen() - fromColor.getGreen();
  var distance_b = destColor.getBlue() - fromColor.getBlue();
  var duration = 30;    // 色がだんだん変化するのにかける時間

  // じょじょに色が変わる
  var id = window.setInterval(function() {
    var time = new Date() - begin;
    var r = easing(time, fromColor.getRed(), distance_r, duration);
    var g = easing(time, fromColor.getGreen(), distance_g, duration);
    var b = easing(time, fromColor.getBlue(), distance_b, duration);

    if (time > duration) {
      window.clearInterval(id);
      r = fromColor.getRed() + distance_r;
      g = fromColor.getGreen() + distance_g;
      b = fromColor.getBlue() + distance_b;
    }

    elem.style.backgroundColor = Color.toHex(r, g, b);
  }, 50);
}

/*
  色を扱うクラス
*/
function Color(colorString) {
  this._red = parseInt(colorString.substr(1, 2), 16);
  this._green = parseInt(colorString.substr(3, 2), 16);
  this._blue = parseInt(colorString.substr(5, 2), 16);
};
Color.toHex = function (r, g, b) {
  r = Math.floor(r);
  g = Math.floor(g);
  b = Math.floor(b);
  return '#' + ( r < 16 ? "0" : "") + r.toString(16) +
    ( g < 16 ? "0" : "") + g.toString(16) +
    ( b < 16 ? "0" : "") + b.toString(16);
};
Color.prototype = {
  toString: function() {
    return Color.toHex(this._red, this._green, this._blue);
  },
  getRed: function() {
    return this._red;
  },
  getGreen: function() {
    return this._green;
  },
  getBlue: function() {
    return this._blue;
  }
};

window.onload = clock;
// window.onload = fade(document.getElementById('clock'), 'white', 'yellow');
