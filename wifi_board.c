#include<SoftwareSerial.h>

SoftwareSerial mySerial(D4, D5); //시리얼 통신을 위한 객체선언

#include <ESP8266WiFi.h>

const char* ssid     = ""; // 사용 중 인 와이파이 이름
const char* password = ""; // 와이파이 패스워드
WiFiServer server(80);

int result = 0;

void setup() {
  Serial.begin(9600);     //시리얼 모니터
  mySerial.begin(9600);   //아두이노 시리얼
  delay(10);
  Serial.println();

  // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin("", "");   //와이파이 이름, 비밀번호
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.println(WiFi.localIP());
  
}

void loop() {
  
  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("Refresh: 1");       // 자동으로 웹페이지 새로고침 (1초 설정)
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html xmlns='http://www.w3.org/1999/xhtml'>");
  client.println("<head>\n<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />");
  //client.println("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");
  //client.println("<head>\n<meta charset='UTF-8'>");
  
  client.println("<title>B.W</title>"); // 웹 서버 페이지 제목 설정
  client.println("</head>\n<body>");
  client.println("<center>");                 // 웹 페이지 내용 중앙 정렬
  client.println("<H1>지하철 이용 현황</H1>"); // 페이지 내용 설정
  client.println("<br>");



 if(mySerial.available() > 0){
  result = mySerial.read();     //아두이노에서 전송받은 데이터 result그릇에 저장
 }

//웹 페이지 내용 작성
if (result<80)  client.print("<H3>1번 : 사용 불가</H3> ");  
else     client.print("<H2>1번 : 사용 가능</H2> ");
client.println("<br>");

if((result%10)<=3)  client.print("<H3>2번 : 사용 불가</H3> ");
else   client.print("<H2>2번 : 사용 가능</H2> "); 
client.println("<br>");

if(((result%10)==0)||((result%10)==1)||((result%10)==4)||((result%10)==5))  client.print("<H3>3번 : 사용 불가</H3> ");
else  client.print("<H2>3번 : 사용 가능</H2> ");
client.println("<br>");

if(result%2 == 0) client.print("<H3>4번 : 사용 불가</H3> "); 
else  client.println("<H2>4번 : 사용 가능</H2>");
client.println("<br>");

delay(1000);
 

  client.println("<br>");
  client.println("<br>");
 
  client.println("<H1> 김유진, 최이설 </H1>"); // 페이지 내용 설정
  client.println("<pre>");
  client.print("</body>\n</html>");
  Serial.println(result);
  
    }
