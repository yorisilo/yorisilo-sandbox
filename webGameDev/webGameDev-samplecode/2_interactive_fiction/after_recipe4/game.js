game.things = (function(){
  var items = {
    bat: {
      name: 'bat',
      effects: {
        'player_inventory': { message: "<p>バットを拾い上げました！</p>",
                            object: "addItem",
                            subject: "deleteItem"
        },
        'dino': { message: "<p>バットで恐竜をぶったたきました。</p><p>恐竜は怒っています！</p>",
                  subject: 'deleteItem'
        },
        'empty': {
              message: "<p>バットを置きました。</p>",
              object: "addItem",
              subject: "deleteItem"
        }
      }
    },
    dino: {
      name: 'dino',
      effects: {
        'player_inventory': { message: "<p>恐竜は動かせません...</p>" } 
      }
    }
  };
	
	// itemsオブジェクトのnameプロパティで指定されたオブジェクトを返す
	// これはbatかdino
  var get = function(name){
  	// console.log(name);
    return this.items[name];
  };
  // ドラッグしてきたオブジェクトとドロップ先のidを取る
  // たとえばバットをインベントリーにドラッグするときには<div class="inventory-box">とplayer_inventory、
  // バットを元に戻すときには<div class="inventory-box">とslide1が渡される
  var dropItemInto = function(itemNode, target){
  	// console.log(itemNode);
  	// console.log(target);
  	// ドラッグしてきた元のコンテナのid
    var sourceContext = itemNode.parentElement.parentElement.id;
    //console.log(sourceContext);
    // ドラッグ元とドラッグ先コンテナが同じでないなら
    if(sourceContext !== target){
    	// ドラッグしてきたオブジェクト内のid名（batかdino）を調べ
      var item = itemNode.firstChild.id;
      // console.log(item);
      // それに相当するitemsオブジェクト(items.batかitems.dino)を得る
      var itemObject = this.get(item);
      // console.log(itemObject);
      
      // ドロップ先がインベントリーの場合には
      if (target === 'player_inventory'){
      	// itemsオブジェクトから対応するオブジェクトを得る
      	// たとえばバットをインベントリーにドラッグすると、targetはplayer_inventoryなので、
      	// 変数effectsにはitems.bat.effects.player_inventoryを割り当てる
        var effects = itemObject.effects[target];
        
        // ドロップ先が恐竜のいるスライドの場合には
        // 変数effectsにはitems.bat.effects.dinoを割り当てる
      }else if(game.slide.getInventory(target)){
      	// console.log(target);
        var effects = itemObject.effects[game.slide.getInventory(target)];
        // console.log(effects);
       
      // ドラッグしたバットを元に戻した場合には
      }else{
      	// 変数effectsにはitems.bat.effects.emptyを割り当てる
        var effects = itemObject.effects['empty'];
        // console.log(effects);
      };

      var targetObject;
      // effects.objectはaddItem
      // console.log(effects.object);
      // console.log(!!effects.object);
      // !!はeffects.objectの値をtrueかfalseに変換する
      // ===は型まで厳密に同じであるかを調べる
      // effectsにobjectプロパティが存在する場合
      if (!!effects.object === true){
      	// ドロップ先がインベントリーなら	targetObjectにgame.playerInventoryの機能を設定
        if(target==="player_inventory"){
          targetObject = game.playerInventory;
         //console.log(targetObject);
        // そうでないなら、targetObjectにgame.slideの機能を設定
        }else{
          targetObject = game.slide;
        };
        // targetObjectの該当する関数にitemObjectを渡して呼び出す
        targetObject[effects.object](itemObject);
        //console.log(targetObject)
      };
      // effectsにsubjectプロパティが存在する場合("deleteItem")
      if (!!effects.subject === true){
      	// ドラッグ元コンテナがplayer_inventoryならsourceObjectにgame.playerInventoryの機能を設定
        if(sourceContext === "player_inventory"){
          var sourceObject = game.playerInventory;
          // console.log("player_inventory")
        // そうでないなら、sourceObjectにgame.slideの機能を設定
        }else{
          var sourceObject = game.slide;
          // console.log("player_inventory以外")
          // console.log(sourceObject)
        };
        // sourceObjectの該当する関数にitemObjectを渡して呼び出す
        sourceObject[effects.subject](itemObject);
        // console.log(effects.subject);
      };
      // effectsにmessageプロパティが存在する場合にはテキストを表示
      if (!!effects.message === true){
        game.slide.setText(effects.message);
      };
      // draw()を呼び出し、表示する画面を設定
      game.screen.draw();
    };
  };

  return{
    items: items,
    get: get,
    dropItemInto: dropItemInto
  }
})();

game.slide = (function(){
  var inventory = {
    slide1: 'bat',
    slide2: 'dino',
    slide3: null
  };
  // 現在のスライドに対応するinventoryオブジェクトのスライドを
  // 渡されたitemのname(batかdino)に設定する
  var addItem = function(item){
  // console.log("addItem");
  	//console.log(item)
  //	console.log(inventory);
    inventory[game.slide.currentSlide()] = item.name;
    //console.log(inventory);
  };
  // 現在のスライドに対応するinventoryオブジェクトのスライドをnullに設定する
  var deleteItem = function(item){
  	
  	// console.log(game.slide.currentSlide());
    inventory[game.slide.currentSlide()] = null;
   
   // console.log("deleteItem");
   // console.log(inventory);
  };
  // メッセージを表示するスライドのevent-textクラスを設定したノードを返す
  var findTextNode = function(slideId){
    return document.querySelector("#" + slideId + " .slide-text .event-text");
  };
  // slideIdはドロップ先コンテナのid
  var getInventory = function(slideId){
  	// console.log("getInventory");
  	// console.log(inventory);
  	//console.log(slideId);	// slide2
  	// console.log(inventory[slideId]);	// dino
  	// inventoryオブジェクトの対応するスライドidの値を返す
    return inventory[slideId];
  };
  
  var setText = function(message, slideId){
  	// slideIdが送られて来ない場合には、現在のスライドidに設定
    if (!!slideId === false){
      slideId = currentSlide();
    }
    // メッセージを設定するノードを調べ、そこにメッセージを割り当てて返す
    return findTextNode(slideId).innerHTML = message;
  };
  // 現在のスライドを返す（slide1,slide2）
  var currentSlide = function(){
  	//console.log(game.stepsTaken[game.stepsTaken.length - 1]);
    return game.stepsTaken[game.stepsTaken.length - 1];
  };
  // 現在のスライドidが送られてくる
  var draw = function(slideId){
  	// console.log("draw");
  	// この時点ですでにdeleteItemかaddItemが呼び出され、
  	// inventoryオブジェクトが変更されている
  	//console.log(slideId);
    if(!slideId === true){
      slideId = this.currentSlide();
      // console.log(slideId);
    };
    
    var item = inventory[slideId];
   // console.log(slideId);
   //console.log(item);	// nullかbatかdino
   // スライド下部にあるインベントリーボックス
    var inventoryBox = document.querySelector ('#'+slideId+' .inventory-box');
    // deleteItemが呼び出された場合
    if (item === null){
    	// console.log("null")
    	// インベントリーボックスを空にする
      inventoryBox.innerHTML = "";
      inventoryBox.classList.add("empty");
    }
    // addItemが呼び出された場合
    else{
    	// console.log("nullでない")
    	// インベントリーボックスに画像を設定し、emptyクラスを削除する
      inventoryBox.innerHTML = "<img src='"+item+".png' alt='"+item+"' class='item' id='"+item+"'>";
      inventoryBox.classList.remove("empty");
    }
  };

  return {
    addItem: addItem,
    deleteItem: deleteItem,
    setText: setText,
    getInventory: getInventory,
    draw: draw,
    currentSlide: currentSlide
  };
})();
game.playerInventory = (function(){
  var items = {
    bat: false
  };
  // インベントリーを空にする
  var clearInventory = function(){
    var playerInventoryBoxes = document.querySelectorAll('#player_inventory .inventory-box');
    [].forEach.call(playerInventoryBoxes, function(inventoryBox) {
      inventoryBox.classList.add("empty");
      inventoryBox.innerHTML = "";
      
    });
  };
  var addItem = function(item){
  	// console.log("addItem");
    if (this.items[item.name] === false){
    	// console.log(this.items);
      this.items[item.name] = true;
      // console.log(this.items);
      
    };
    return this.items;
  };
  var deleteItem = function(item){
  	// console.log("deleteItem");
  	// console.log(this.items);
    if (this.items[item.name] === true){
      this.items[item.name] = false;
    };
    // console.log(this.items);
    return this.items;
  };
  // インベントリーをいったん空にし、
  // 対象インベントリーからemptyクラスを削除して、innerHTMLに画像を設定
  var draw = function(){
  	// インベントリーを空にする
    clearInventory();
    var counter = 0;
    // インベントリーを全部取得
    var inventoryBoxes = document.querySelectorAll('#player_inventory .inventory-box');
    // itemsオブジェクト内のオブジェクトを繰り返し調べる
    for(var item in this.items){
      if(this.items[item] === true){
      	// console.log(items);
      	// console.log(items[item]);
      	// addItemによってbatがtrueになっている
      	// console.log(inventoryBoxes[counter]);
      	// 対象インベントリーのクラスからemptyを削除
        inventoryBoxes[counter].classList.remove("empty");
        // console.log(inventoryBoxes[counter]);
        // console.log(item);
        // 対象インベントリーにitem画像（バット）を設定
        inventoryBoxes[counter].innerHTML = "<img src='"+item+".png' alt='"+item+"' class='item' id='"+item+"'>";
      }
      counter = counter + 1;
      // console.log(counter);
    };
  };
  return {
    items: items,
    addItem: addItem,
    deleteItem: deleteItem,
    draw: draw
  };
})();

game.screen = (function(){
  var draw = function(){
    game.playerInventory.draw();
    game.slide.draw(game.slide.currentSlide());
  };
  return {
    draw: draw
  }
})();
