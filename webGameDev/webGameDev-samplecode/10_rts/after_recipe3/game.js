window.onload = function() {
  Crafty.init();
  Crafty.viewport.scale(3.5);
  var iso = Crafty.isometric.size(16);
  var mapWidth = 20;
  var mapHeight = 40;
  Crafty.sprite(16, "sprites.png", {
    grass: [0,0,1,1],
    selected_grass: [1,0,1,1],
    blue_box: [2,0,1,1],
    blue_one: [3,0,1,1],
    blue_two: [4,0,1,1],
    blue_three: [5,0,1,1],
    blue_bomb: [6,0,1,1],
    blue_flag: [7,0,1,1],
    red_box: [8,0,1,1],
    red_one: [9,0,1,1],
    red_two: [10,0,1,1],
    red_three: [11,0,1,1],
    red_bomb: [12,0,1,1],
    red_flag: [13,0,1,1],
    selected_box: [14,0,1,1]
  });
  var setMap = function(){
    for(var x = 0; x < mapWidth; x++) {
      for(var y = 0; y < mapHeight; y++) {
        var bias = ((y % 2) ? 1 : 0);
        var z = x+y + bias;
        console.log("x : " + x);
        console.log("y : " + y);
        console.log("bias : " + bias);
        console.log("z : " + z);
        var tile = Crafty.e("2D, DOM, grass, Mouse")
          .attr('z',z)
          .areaMap([7,0],[8,0],[15,5],[15,6],[8,9],[7,9],[0,6],[0,5])
          .bind("MouseOver", function() {
            this.addComponent("selected_grass");
            this.removeComponent("grass");
          }).bind("MouseOut", function() {
            this.addComponent("grass");
            this.removeComponent("selected_grass");
          });
        iso.place(x,y,0, tile);
      }
    }
  };
  setMap();
  var socket = io.connect('http://localhost:1234');
  socket.on('started', function(data){
    console.log(data);
  });
};
