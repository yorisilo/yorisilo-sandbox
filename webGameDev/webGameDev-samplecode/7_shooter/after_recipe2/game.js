var PLAYGROUND_WIDTH = 700;
var PLAYGROUND_HEIGHT = 250;
var REFRESH_RATE = 15;
var farParallaxSpeed = 1; 
var closeParallaxSpeed = 3;

var enemyHeight = 30;
var enemyWidth = 60;
var enemySpawnRate = 1000;

function Enemy(node, value){
  this.value = value;
  this.speed = 5;
  this.node = node;
  this.update = function(){
    this.node.x(-this.speed, true);
  };
};


var background1 = new $.gQ.Animation({imageURL: "background1.png"});
var background2 = new $.gQ.Animation({imageURL: "background2.png"}); 
var background3 = new $.gQ.Animation({imageURL: "background3.png"});
var background4 = new $.gQ.Animation({imageURL: "background4.png"});

$("#playground").playground({height: PLAYGROUND_HEIGHT, width: PLAYGROUND_WIDTH, keyTracker: true});

$.playground().addGroup("background", {width: PLAYGROUND_WIDTH, height: PLAYGROUND_HEIGHT})
.addSprite("background1", {animation: background1, width: PLAYGROUND_WIDTH, height: PLAYGROUND_HEIGHT})
.addSprite("background2", {animation: background2, width: PLAYGROUND_WIDTH, height: PLAYGROUND_HEIGHT, posx: PLAYGROUND_WIDTH})
.addSprite("background3", {animation: background3, width: PLAYGROUND_WIDTH, height: PLAYGROUND_HEIGHT})
.addSprite("background4", {animation: background4, width: PLAYGROUND_WIDTH, height: PLAYGROUND_HEIGHT, posx: PLAYGROUND_WIDTH})
.end()
.addGroup("enemies", {width: PLAYGROUND_WIDTH, height: PLAYGROUND_HEIGHT})

$.playground().registerCallback(function(){
  $("#background1").x(($("#background1").x() - farParallaxSpeed - PLAYGROUND_WIDTH) % (-2 * PLAYGROUND_WIDTH) + PLAYGROUND_WIDTH);
  $("#background2").x(($("#background2").x() - farParallaxSpeed - PLAYGROUND_WIDTH) % (-2 * PLAYGROUND_WIDTH) + PLAYGROUND_WIDTH);
  $("#background3").x(($("#background3").x() - closeParallaxSpeed - PLAYGROUND_WIDTH) % (-2 * PLAYGROUND_WIDTH) + PLAYGROUND_WIDTH);
  $("#background4").x(($("#background4").x() - closeParallaxSpeed - PLAYGROUND_WIDTH) % (-2 * PLAYGROUND_WIDTH) + PLAYGROUND_WIDTH);
  $(".enemy").each(function(){
    this.enemy.update();
    if(($(this).x()+ enemyWidth) < 0){
      $(this).remove();
    } 
  });
}, REFRESH_RATE);
$.playground().registerCallback(function(){
  var enemyValue = Math.ceil(Math.random()*21) - 11;
  var name = "enemy_"+(new Date).getTime();
  $("#enemies").addSprite(name, {animation: '', posx: PLAYGROUND_WIDTH, 
  	posy:	Math.random()*PLAYGROUND_HEIGHT*0.9,width: enemyWidth, height: enemyHeight});
  var enemyElement = $("#"+name);
  enemyElement.addClass("enemy");
  enemyElement[0].enemy = new Enemy(enemyElement, enemyValue);
  enemyElement.text(enemyValue);
  
  // console.log(enemyValue + " :" + enemyElement.y());
  // console.log(enemyElement[0]);
}, enemySpawnRate); 

$.playground().startGame();
