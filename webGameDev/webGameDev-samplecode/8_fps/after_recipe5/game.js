var Game = function(){
  var raycaster = {
    init: function(){
      var numberOfRays = 300;
      var angleBetweenRays = .2 * Math.PI /180;
      this.castRays = function() {
        for (var i=0;i<numberOfRays;i++) {
          var rayNumber = -numberOfRays/2 + i;
          var rayAngle = angleBetweenRays * rayNumber + player.angle;
          // this.castRay(rayAngle);
          // castRayに送る引数にiを追加
          this.castRay(rayAngle, i);
        }
      }
      // this.castRay = function(rayAngle){
      // castRayのパラメータにiを追加
      this.castRay = function(rayAngle, i){
        var twoPi = Math.PI * 2; 
        rayAngle %= twoPi;
        if (rayAngle < 0) rayAngle += twoPi;
        var right = (rayAngle > twoPi * 0.75 || rayAngle < twoPi * 0.25);
        var up = rayAngle > Math.PI;
        var slope = Math.tan(rayAngle);
        var distance = 0;
        var xHit = 0;
        var yHit = 0;
        var wallX;  
        var wallY;
        var dX = right ? 1 : -1; 
        var dY = dX * slope;  
        var x = right ? Math.ceil(player.x) : Math.floor(player.x);
        var y = player.y + (x - player.x) * slope; 
        while (x >= 0 && x < minimap.cellsAcross && y >= 0 && y < minimap.cellsDown) {
          wallX = Math.floor(x + (right ? 0 : -1));
          wallY = Math.floor(y);
          if (map[wallY][wallX] > -1) {
            var distanceX = x - player.x;
            var distanceY = y - player.y;
            distance = Math.sqrt(distanceX*distanceX + distanceY*distanceY);  
            xHit = x;  
            yHit = y;
            break;
          }
          x += dX; 
          y += dY;
        }
        slope = 1/slope;
        dY = up ? -1 : 1;
        dX = dY * slope;
        y = up ? Math.floor(player.y) : Math.ceil(player.y);
        x = player.x + (y - player.y) * slope;
        while (x >= 0 && x < minimap.cellsAcross && y >= 0 && y < minimap.cellsDown) {
          wallY = Math.floor(y + (up ? -1 : 0));
          wallX = Math.floor(x);
          if (map[wallY][wallX] > -1) {
            var distanceX = x - player.x;
            var distanceY = y - player.y;
            var blockDistance = Math.sqrt(distanceX*distanceX + distanceY*distanceY);
            if (!distance || blockDistance < distance) {
              distance = blockDistance;
              xHit = x;
              yHit = y;
            }
            break;
          }
          x += dX;
          y += dY;
        }
        // this.draw(xHit, yHit);
        // drawの引数にdistance, i, rayAngleを追加
        this.draw(xHit, yHit, distance, i, rayAngle);
      };
      // this.draw = function(rayX, rayY){
      // drawのパラメータにdistance, i, rayAngleを追加
      this.draw = function(rayX, rayY, distance, i, rayAngle){ 
        minimap.context.beginPath();
        minimap.context.moveTo(minimap.cellWidth*player.x, minimap.cellHeight*player.y);
        minimap.context.lineTo(rayX * minimap.cellWidth, rayY * minimap.cellHeight);
        minimap.context.closePath();
        minimap.context.stroke();
        // 以下を追加
        var adjustedDistance = Math.cos(rayAngle - player.angle) * distance;
        var wallHalfHeight = canvas.height / adjustedDistance / 2;
        var wallTop = Math.max(0, canvas.halfHeight - wallHalfHeight);
        var wallBottom = Math.min(canvas.height, canvas.halfHeight + wallHalfHeight);
        canvas.drawSliver(i, wallTop, wallBottom, "#000");
        // ここまで
        
      }
    }
  }
  var player = {
    init: function(){
      this.x = 10;
      this.y = 6;
      this.direction = 0;
      this.angle = 0;
      this.speed = 0;
      this.movementSpeed = 0.1;
      this.turnSpeed = 4 * Math.PI / 180; 
      this.move = function(){
        var moveStep = this.speed * this.movementSpeed;
        this.angle += this.direction * this.turnSpeed;
        var newX = this.x + Math.cos(this.angle) * moveStep;
        var newY = this.y + Math.sin(this.angle) * moveStep;
        if (!containsBlock(newX, newY)){
          this.x = newX;
          this.y = newY;
        };
      };
      this.draw = function(){
        var playerXOnMinimap = this.x * minimap.cellWidth;
        var playerYOnMinimap = this.y * minimap.cellHeight;
        minimap.context.fillStyle = "#000000";
        minimap.context.beginPath();
        minimap.context.arc(minimap.cellWidth*this.x, minimap.cellHeight*this.y, minimap.cellWidth/2, 0, 2*Math.PI, true); 
        minimap.context.fill();
        var projectedX = this.x + Math.cos(this.angle);
        var projectedY = this.y + Math.sin(this.angle);
        minimap.context.fillRect(minimap.cellWidth*projectedX - minimap.cellWidth/4, minimap.cellHeight*projectedY - minimap.cellHeight/4, minimap.cellWidth/2, minimap.cellHeight/2);
      };
    }
  }
  function containsBlock(x,y) {
    return (map[Math.floor(y)][Math.floor(x)] !== -1); 
  };
  var map = [ [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1], 
      [1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1], 
      [1,-1,-1,-1,-1,-1,-1,0,-1,2,3,1,-1,-1,-1,1], 
      [1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1], 
      [1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1], 
      [1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1], 
      [1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1], 
      [1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1], 
      [1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,-1,-1,-1,1], 
      [1,-1,-1,1,-1,-1,-1,-1,-1,3,-1,-1,-1,-1,-1,1], 
      [1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1], 
      [1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1], 
      [1,-1,-1,-1,-1,-1,1,-1,-1,2,-1,-1,-1,-1,-1,1], 
      [1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1], 
      [1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1], 
      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]]; 
  var canvas = {
    init: function(){
      this.element = document.getElementById('canvas');
      this.context = this.element.getContext("2d");
      this.width = this.element.width;
      this.height = this.element.height;
      this.halfHeight = this.height/2;
      this.ground = '#DFD3C3'; 
      this.sky = '#418DFB'; 
      this.blank = function(){
        this.context.clearRect(0, 0, this.width, this.height);
        this.context.fillStyle = this.sky;
        this.context.fillRect(0, 0, this.width, this.halfHeight);
        this.context.fillStyle = this.ground;
        this.context.fillRect(0, this.halfHeight, this.width, this.height);
      }
      this.drawSliver = function(sliver, wallTop, wallBottom, color){
        this.context.beginPath();
        this.context.strokeStyle = color;
        this.context.moveTo(sliver + .5, wallTop);
        this.context.lineTo(sliver + .5, wallBottom);
        //this.context.moveTo(sliver, wallTop);
        //this.context.lineTo(sliver, wallBottom);
        this.context.closePath();
        this.context.stroke();
      }
    }
  };
  
  var minimap = {
    init: function(){
      this.element = document.getElementById('minimap');
      this.context = this.element.getContext("2d");
      this.element.width = 300;
      this.element.height = 300;
      this.width = this.element.width;
      this.height = this.element.height;
      this.cellsAcross = map[0].length;
      this.cellsDown = map.length;
      this.cellWidth = this.width/this.cellsAcross;
      this.cellHeight = this.height/this.cellsDown;
      this.colors = ["#ffff00", "#ff00ff", "#00ffff", "#0000ff"];
      this.draw = function(){
        for(var y = 0; y < this.cellsDown; y++){
          for(var x = 0; x < this.cellsAcross; x++){
            var cell = map[y][x];
            if (cell===-1){
              this.context.fillStyle = "#ffffff"
            }else{
              this.context.fillStyle = this.colors[map[y][x]];
            };
            this.context.fillRect(this.cellWidth*x, this.cellHeight*y, this.cellWidth, this.cellHeight);
          };
        };
      };
    }
  };
  
  this.draw = function(){
    minimap.draw();
    player.draw(); 
    canvas.blank();
    raycaster.castRays();
  };
  this.setup = function() {
    minimap.init();
    player.init();
    raycaster.init(); 
    canvas.init();
  };
  this.update = function(){
    if(jaws.pressed("left")) { player.direction = -1 };
    if(jaws.pressed("right")) { player.direction = 1 };
    if(jaws.pressed("up")) { player.speed = 1 };
    if(jaws.pressed("down")) { player.speed = -1 }; 

    if(jaws.on_keyup(["left", "right"], function(){
       player.direction = 0;
    })); 
    if(jaws.on_keyup(["up", "down"], function(){
       player.speed = 0;
    })); 
    player.move();
  };
}
