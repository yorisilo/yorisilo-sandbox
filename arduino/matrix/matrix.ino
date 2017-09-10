void setup()
{
  //16本のピン(2~17)を出力に設定
  for(int i=2;i<=17;i++){
    pinMode(i,OUTPUT);
  }
}

void loop()
{
  //行（横）の繰り返し処理
  for(int i=2;i<=9;i++){     //行（2~9番ピン）
    digitalWrite(i,LOW);    //HIGHで点灯

    //列（縦）の繰り返し処理
    for(int j=10;j<=17;j++){ //列（10~17番ピン）
      digitalWrite(j,HIGH);   //LOWで点灯
      delay(100);            //点灯時間
      digitalWrite(j,LOW);  //列をオフにする
    }

    digitalWrite(i,HIGH);     //行をオフにする
  }
}