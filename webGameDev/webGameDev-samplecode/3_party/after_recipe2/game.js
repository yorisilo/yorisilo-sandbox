atom.input.bind(atom.key.LEFT_ARROW, 'left');
game = Object.create(Game.prototype);
game.update = function(dt) {
  if (atom.input.pressed('left')) {
    return console.log("プレイヤーは左への移動を開始");
  } else if (atom.input.down('left')) {
    return console.log("プレイヤーはまだ左へ移動中");
  }
};
// drawメソッドを全部書き換える
game.draw = function() {
  atom.context.beginPath();
  atom.context.fillStyle = '#34e';
  atom.context.fillRect(0, 0, atom.width, atom.height/2);
  atom.context.fillStyle = '#ee3';
  atom.context.arc(140, atom.height/2 -30, 90, Math.PI*2, 0); 
  atom.context.fill();
  atom.context.fillStyle = '#2e2';
  atom.context.fillRect(0, atom.height/2, atom.width, atom.height/2);
};
window.onblur = function() {
  return game.stop();
};
window.onfocus = function() {
  return game.run();
};
game.run();


//console.log(Game.prototype);
//console.log(Game.prototype.__proto__);
//console.log(Game.prototype.hasOwnProperty());