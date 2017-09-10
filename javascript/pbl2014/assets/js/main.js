var cards = [],
    CARD_NUM = 4,//initial
    currentNum, // 0 or 1 or ...
    openedCard, // 0..7 .
    correctNum = 0, //正解だった回数.
    enableFlip = true, //めくっている最中かどうか.
    score = 0,
    timerID;

// function runTimer() {
//   document.getElementById('score').innerHTML = score--;
//   timerID = window.setTimeout(function() {runTimer();}, 10);
// }

//http://ideone.com/zLQSY6

function level(n) {
  if(n == 3) {
    CARD_NUM = 25;
    score = 5000
  } else if(n == 2) {
    CARD_NUM = 16;
    score = 5000
  } else {
    CARD_NUM = 4;
    score = 1000
  }
  initcards();
  timer();
}

function timer() {
  document.getElementById('score').innerHTML = score--;
  timerID = window.setTimeout(function() {timer();}, 10);
  if(score < 0) {
    window.clearTimeout(timerID);
    alert("Game over...");
    window.location.reload();
    jumpPage("badend.html");
  }
}


function flip(card) {
  if(!enableFlip) { //めくっている最中はflipは効かない
    return;
  }
  //var card = document.getElementById('card_'+ n);
  if(card.value != '?') { //めくるカードが?以外の時はflipは効かない
    return;
  }
  card.value = card.dataset.num;
  if(typeof currentNum === 'undefined') {
    // 1枚目
    openedCard = card;
    currentNum = card.dataset.num;
  } else {
    //2枚目
    //判定
    judge(card);
    currentNum = undefined;
  }
}

function judge(card) {
  if(currentNum == card.dataset.num) {
    //正解
    correctNum++;
    if(correctNum == CARD_NUM / 2) {
      window.clearTimeout(timerID);
      alert("your score is ..." + document.getElementById('score').innerHTML);
      window.location.reload();
      jumpPage("goodend.html");
    }
  } else {
    //不正解
    enableFlip = false;
    window.setTimeout(function() {
      enableFlip = true;
      //document.getElementById('card_' + openedCard).value = '?';
      //document.getElementById('card_' + n).value = '?';
      openedCard.value = '?';
      card.value = '?'
      enableFlip = true;
    }, 3000);
  }
}

function jumpPage(url) {
  location.href = url;
}

function opencards() {
  for(var i = 0; i < CARD_NUM; i++) {
    //var card = document.getElementById('card_'+ i);
    card = cards[i];
    card.value = card.dataset.num;
  }
}

function hidecards() {
  for(var i = 0; i < CARD_NUM; i++) {
    //var card = document.getElementById('card_'+ i);
    card = cards[i];
    card.value = '?';
  }
}

function grancecards() {
  correctNum = 0;
  opencards();
  window.setTimeout("hidecards()",500);
}

function initcards() { // カードの組を設定する
  var num,
      cardIndex,
      i,
      stage = document.getElementById('stage');

  for (i = 0; i < CARD_NUM; i++) {
    num = Math.floor(i / 2); // 00 11 22 33 44 55 みたいになる
    do {
      cardIndex = Math.floor(Math.random() * CARD_NUM); // 0からCARDS_NUMまでの値をランダムに割り振るお決まりのやつ
      //console.log(cardIndex);
    } while (typeof cards[cardIndex] !== 'undefined'); // cards[hoge]に値が入っていれば，回す
    cards[cardIndex] = createCard(num);
  }

  for (i = 0; i < CARD_NUM; i++) {
    console.log(i,cards[i].dataset.num);
    stage.appendChild(cards[i]);
    if (i % Math.sqrt(CARD_NUM) == (Math.sqrt(CARD_NUM)) - 1) {
      stage.appendChild(document.createElement('br'));
    }
  }
}


function createCard(num) {
  var card = document.createElement('input');
  card.type = 'button';
  card.value = '?';
  card.dataset.num = num;
  card.onclick = function () {
    flip(this);
  };
  return card;
}
