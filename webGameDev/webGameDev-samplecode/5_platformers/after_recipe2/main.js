var jsApp = {
  onload: function() {
  	// console.log("jsAppのonload");
    if (!me.video.init('jsapp', 320, 240, true, 2.0)) {
      alert("html 5 キャンバスはこのブラウザではサポートされていません。");
      return;
    }
    me.loader.onload = this.loaded.bind(this);
    me.loader.preload(resources);
    me.state.change(me.state.LOADING);
  },
  loaded: function() {
  	// console.log("jsAppのloaded");
    me.state.set(me.state.PLAY, new PlayScreen());
    me.state.change(me.state.PLAY);
  }
};
window.onReady(function() {
	// console.log("windowのonReady");
  jsApp.onload();
});
