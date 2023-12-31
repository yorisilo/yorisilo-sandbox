// これを消去
// atom.input.bind(atom.key.LEFT_ARROW, 'left');
game = Object.create(Game.prototype);
// これを追加
game.keys = ['A', 'S', 'D', 'F'];
for (var i = 0; i < game.keys.length; i++){
  atom.input.bind(atom.key[game.keys[i]], game.keys[i]);
};
//

atom.currentMoleTime = 0;
atom.tillNewMole = 2;
game.update = function(dt) {
  atom.currentMoleTime = atom.currentMoleTime + dt;
  
  if (atom.currentMoleTime > atom.tillNewMole){
    game.activeMole = Math.floor(Math.random()*4);
    atom.currentMoleTime = 0;
    
    // console.log(game.activeMole);
    
    // これを追加
    if(game.bop.bopped === false){
      game.bop.total = game.bop.total-1;
    }
    else{
      game.bop.bopped = false;
    }
  };
  for (var i = 0; i < game.keys.length; i++){
    if (atom.input.pressed(game.keys[i])){
      game.bop.with_key(game.keys[i]);
    }
  };
  //
};

// これを追加
game.bop = {
  bopped: true,
  total:0,
  draw: function(){
    atom.context.fillStyle = '#000';
    atom.context.font = '130px monospace';
    atom.context.fillText('スコア: ' + this.total, 300, 200);
  },
  with_key: function(key){
  	// console.log(game.holes[game.activeMole]);
  	// 今アクティブなもぐらが-1でなく、かつ押されたキーがもぐらのラベルと一致するなら、
    if (!!(game.activeMole + 1) === true && key === game.holes[game.activeMole].label){
      this.total = this.total+1;
      game.activeMole = -1;
      this.bopped = true;
    }
    // お手付きした場合
    else{
    	console.log(game.activeMole);
      this.total = this.total-1;
    }
  }
}
//

game.draw = function() {
  this.drawBackground();
  
  for (var i = 0; i < game.holes.length; i++){
    if (i === game.activeMole){
      game.holes[i].active = true;
    }
    else{
      game.holes[i].active = false;
    };
    game.holes[i].draw();
  }
  // これを追加
  this.bop.draw();
};
game.makeHoles = function(labels, xOffset, yOffset){
  game.holes = [];
  for(var i = 0; i < labels.length; i++){
    var newHole = Object.create(game.hole);
    newHole.holeLocation = [xOffset + game.hole.spacing*i, yOffset];
    newHole.label = labels[i];
    game.holes.push(newHole);
  };
};

game.mole = {
  size: 40,
  color: '#557',
  noseSize: 8,
  noseColor: "#c55",
  eyeSize: 5,
  eyeOffset: 10, 
  eyeColor: "#000",
  draw: function(xPosition, yPosition){
    this.drawHead(xPosition, yPosition);
    this.drawEyes(xPosition, yPosition);
    this.drawNose(xPosition, yPosition);
    this.drawWhiskers(xPosition, yPosition);
  },
  drawHead: function(xPosition, yPosition){
    atom.context.beginPath(); 
    atom.context.fillStyle = this.color;
    atom.context.arc(xPosition, yPosition, this.size, 0, Math.PI*2); 
    atom.context.fill();
  },
  drawNose: function(xPosition, yPosition){
    atom.context.beginPath(); 
    atom.context.fillStyle = this.noseColor;
    atom.context.arc(xPosition, yPosition, this.noseSize, 0, Math.PI*2); 
    atom.context.fill();
  },
  drawEyes: function(xPosition, yPosition){
    atom.context.beginPath(); 
    atom.context.fillStyle = this.eyeColor;
    atom.context.arc(xPosition + this.eyeOffset, yPosition - this.eyeOffset, this.eyeSize, 0, Math.PI*2); 
    atom.context.fill();
    atom.context.beginPath(); 
    atom.context.fillStyle = this.eyeColor;
    atom.context.arc(xPosition - this.eyeOffset, yPosition - this.eyeOffset, this.eyeSize, 0, Math.PI*2); 
    atom.context.fill();
  },
  drawWhiskers: function(xPosition, yPosition){
    atom.context.beginPath(); 
    atom.context.moveTo(xPosition - 10, yPosition); 
    atom.context.lineTo(xPosition - 30, yPosition); 
    atom.context.moveTo(xPosition + 10, yPosition); 
    atom.context.lineTo(xPosition + 30, yPosition); 
    atom.context.moveTo(xPosition - 10, yPosition + 5); 
    atom.context.lineTo(xPosition - 30, yPosition + 10); 
    atom.context.moveTo(xPosition + 10, yPosition + 5); 
    atom.context.lineTo(xPosition + 30, yPosition + 10); 
    atom.context.stroke();
  }
}
game.hole = {
  size: 40,
  spacing: 280,
  color: '#311',
  labelOffset: 140,
  labelColor: '#000',
  labelFont: "130px monospace",
  moleOffset: 20,
  draw: function(){
    this.drawHole();
    this.drawLabel();
    if (this.active === true){
      this.drawMole(this.holeLocation[0], this.holeLocation[1] - this.moleOffset);
    };
  },
  drawHole: function(){
    atom.context.fillStyle = this.color;
    atom.context.beginPath(); 
    atom.context.arc(this.holeLocation[0], this.holeLocation[1], this.size, 0, Math.PI*2, false); 
    atom.context.fill();
  },
  drawLabel: function(){
    atom.context.fillStyle = this.labelColor;
    atom.context.font = this.labelFont;
    atom.context.fillText(this.label, this.holeLocation[0] - this.size, this.holeLocation[1] + this.labelOffset);
  },
  drawMole: function(xPosition, yPosition){
    game.mole.draw(xPosition, yPosition);
  }
};
game.drawBackground = function(){
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
// これを変更
//game.makeHoles(['A', 'S', 'D', 'F'], 145, atom.height/2 + 85);
game.makeHoles(game.keys, 145, atom.height/2 + 85);
game.run();