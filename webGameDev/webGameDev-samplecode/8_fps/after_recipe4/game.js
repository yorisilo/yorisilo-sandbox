var Game = function(){
  var raycaster = {
    init: function(){
      var numberOfRays = 300;
      var angleBetweenRays = .2 * Math.PI /180;
      this.castRays = function() {
        for (var i=0;i<numberOfRays;i++) {
          var rayNumber = -numberOfRays/2 + i;
          var rayAngle = angleBetweenRays * rayNumber + player.angle;
          this.castRay(rayAngle);
        }
      }
      // 照射角度の情報からレイを描画する
      this.castRay = function(rayAngle){
        var twoPi = Math.PI * 2; 
        rayAngle %= twoPi;
        if (rayAngle < 0) rayAngle += twoPi;
        // 照射するレイは右方向なのかどうか
        var right = (rayAngle > twoPi * 0.75 || rayAngle < twoPi * 0.25);
        // 照射するレイは上方向なのかどうか
        var up = rayAngle > Math.PI;
        // レイが斜辺に当たる三角形の高さ
        var slope = Math.tan(rayAngle);
        // ブロックまでの距離
        var distance = 0;
        // レイとブロックがぶつかる位置
        var xHit = 0;
        var yHit = 0;
        // レイとブロックがぶつかった位置のマップ座標
        var wallX;  
        var wallY;
        
        // 水平方向のヒットチェック
        
        // 次に伸ばすレイのx軸上の変化量
        // 右方向のレイならdXは1、そうでないならdXは-1
        var dX = right ? 1 : -1; 
        // 次に伸ばすレイのy軸上の変化量
        // dXを単位として、slope倍してdYを決める
        var dY = dX * slope;
        // レイが照射時に進む、マップ上のセルの位置
        var x = right ? Math.ceil(player.x) : Math.floor(player.x);
        var y = player.y + (x - player.x) * slope; 
        
        // レイとブロック、マップの端との水平方向のヒットを調べる
        while (x >= 0 && x < minimap.cellsAcross && y >= 0 && y < minimap.cellsDown) {
        	// 対象セルの特定
          wallX = Math.floor(x + (right ? 0 : -1));
          wallY = Math.floor(y);
          // セルにブロックがあるならヒット
          if (map[wallY][wallX] > -1) {
          	// プレイヤーからの距離を計算する
            var distanceX = x - player.x;
            var distanceY = y - player.y;
            // ２点間の距離を計算
            distance = Math.sqrt(distanceX*distanceX + distanceY*distanceY);
            // レイとブロックがぶつかった位置を特定
            xHit = x;  
            yHit = y;
            break;
          }
          // ヒットがない場合には、レイを伸ばしてさらに調べる
          x += dX; 
          y += dY;
        }
        
        // 垂直方向のヒットチェック
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
        this.draw(xHit, yHit); 
      };
      this.draw = function(rayX, rayY){
        minimap.context.beginPath();
        minimap.context.moveTo(minimap.cellWidth*player.x, minimap.cellHeight*player.y);
        minimap.context.lineTo(rayX * minimap.cellWidth, rayY * minimap.cellHeight);
        minimap.context.closePath();
        minimap.context.stroke();
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
    raycaster.castRays();
  };
  this.setup = function() {
    minimap.init();
    player.init();
    raycaster.init(); 
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
