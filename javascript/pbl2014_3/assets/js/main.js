var tiemrID,
    time = 0,
    click = 0,
    click_num = 0;

function timer () {
  document.getElementById('time').innerHTML = time--;
  timerID = window.setTimeout(function() {timer();}, 10);
  if(time < 0) {
    window.clearTimeout(timerID);
    alert("Game over...");
    window.location.reload();
    jumpPage("badend.html");
  }
}

function level(n) {
  if(n == 1) {
    time=1000;
    click_num = 20;
  } else if(n == 2) {
    time=1000;
    click_num = 200;
  } else {
    time=1000;
    click_num = 300;
  }
  timer();
}

function clicker () {
  document.getElementById( "click" ).innerHTML = click_num--;
  if(click_num == 0) {
    alert("congratulations!!!");
    window.location.reload();
    jumpPage("goodend.html");
  }
}

function reload () {
  window.location.reload();
}
