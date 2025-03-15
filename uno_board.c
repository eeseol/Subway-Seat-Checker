#include<SoftwareSerial.h>

SoftwareSerial mySerial(3,4); //시리얼 통신을 위한 객체선언

int L_sensor_0 = A0;
int W_sensor_1 = A1;
int L_sensor_2 = A2;
int L_sensor_3 = A3;

int value_0, value_1, value_2, value_3;
int mid, result;

void setup() {
Serial.begin(9600);     //시리얼 모니터
mySerial.begin(9600);   //와이파이 보드 시리얼

}

void loop() {
  
value_0=analogRead(L_sensor_0);  //센서값들을 각각의 value 그릇에 저장
value_1=analogRead(W_sensor_1);
value_2=analogRead(L_sensor_2);
value_3=analogRead(L_sensor_3);

if(value_0 >= 300) mid = 2000;             //첫번째 자리에 사람이 없을 때
else mid = 1000;                          //첫번째 자리에 사람이 있을 때

if(value_1 <= 50) mid = mid + 200;       //두번째 자리에 사람이 없을 때
else mid = mid + 100;                     //두번째 자리에 사람이 있을 때

if(value_2 >= 100) mid = mid + 20;         //세번째 자리에 사람이 없을 때
else mid = mid + 10;                      //세번째 자리에 사람이 있을 때

if(value_3 >= 400) mid = mid + 2;          //네번째 자리에 사람이 없을 때
else mid = mid + 1;                       //네번째 자리에 사람이 있을 때

switch(mid){
  case 1111: result = 70; break;    //F   XXXX  
  case 1112: result = 71; break;    //G   XXXO
  case 1121: result = 72; break;    //H   XXOX
  case 1122: result = 73; break;    //I   XXOO
  case 1211: result = 74; break;    //J   XOXX
  case 1212: result = 75; break;    //K   XOXO
  case 1221: result = 76; break;    //L   XOOX
  case 1222: result = 77; break;    //M   XOOO
  case 2111: result = 80; break;    //P   OXXX
  case 2112: result = 81; break;    //Q   OXXO
  case 2121: result = 82; break;    //R   OXOX
  case 2122: result = 83; break;    //S   OXOO 
  case 2211: result = 84; break;    //T   OOXX
  case 2212: result = 85; break;    //U   OOXO
  case 2221: result = 86; break;    //V   OOOX
  case 2222: result = 87; break;    //W   OOOO
  default: result = 63;             //?   ERRO 값 출력
}

//시리얼 모니터 내용을 블루투스 측에 write
mySerial.write((char)result);
Serial.println((char)result);
delay(1000);

result = result - result;         //result 값 초기화
}
