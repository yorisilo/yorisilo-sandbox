var PlayScreen = me.ScreenObject.extend({
  onResetEvent: function() {
  	// console.log("PlayScreenのonResetEvent");
    me.levelDirector.loadLevel("level1");
  }
});
