#include <Arduino.h>

void setup(){
  //シリアル通信開始
  Serial.begin(9600);
}

void loop(){
  //３つの値をアナログ入力で読み込む
  int x=analogRead(0);
  int y=analogRead(1);
  int z=analogRead(2);

  //Xの値を出力（十進数）
  Serial.print(x,DEC);
  //値と値の間に区切りを入れる
  Serial.print(",");
  //Yの値を出力
  Serial.print(y,DEC);
  //値と値の間に区切りを入れる
  Serial.print(",");
  //Zの値を出力し改行する
  Serial.println(z,DEC);
  delay(100);
}
