#include <SoftwareSerial.h>
#include <Stepper.h>

void stepping_motor_control();  //definition to controlling motor
 
#define DEBUG true
 
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                               // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                               // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  pinMode(13, 0);
  Serial.begin(9600);
  esp8266.begin(9600);         // your esp's baud rate might be different
  
 
  
  sendData("AT+RST\r\n",2000,DEBUG);              // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG);         // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG);            // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG);         // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG);   // turn on server on port 80
}

int state=1;
unsigned long start=1;
char input;
void loop()
{
  if(esp8266.available()) // check if the esp is sending a message 
  {
    /*
    while(esp8266.available())
    {
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
      Serial.write(c);
    } */
    
    if(esp8266.find("+IPD,"))
    {
     delay(1000);
 
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48

     String webpage;

     //---------------------------------------
     if(Serial.available()){
       input=Serial.read();
       if(input=='O'){
         Serial.println("Door is Opened");
         webpage="<h1>Door is Opened</h1>";
         state=0;
         start=millis();
         stepping_motor_control(1);
       }else if(input=='M'){
         Serial.println("Manager Opened Door");
         webpage="<h1>Manager Opened Door</h1>";
         state=0;
         start=millis();
         stepping_motor_control(1);
       }else if(input=='X'){
         Serial.println("Wrong number Detected 3 Times");
         webpage="<h1>Wrong number Detected 3 Times</h1>";
         start=millis();
       }
    }

    if(millis()-start>5000){
      webpage="<h1>Door Closed</h1>";
    }

    if(state==0){
      stepping_motor_control(2);
    }
    
    
     //---------------------------------------

     
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     
     
     /*
     webpage="<button>LED2</button>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     */
 
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
    }

    
  }
    
  delay(5000);
}
 
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}



void stepping_motor_control(int direct){
  int stepsPerRevolution=2048;                       // 2048:한바퀴(360도), 1024:반바퀴(180도), 512:1/4바퀴(90도)
  Stepper myStepper(stepsPerRevolution,11,9,10,8);  // 모터 드라이브에 연결된 핀 IN4, IN2, IN3, IN1
  myStepper.setSpeed(14);                            //스텝 모터 스피드 설정
  
  if(direct==1){
    myStepper.step(1024);             // 시계 반대 방향으로 한바퀴 회전
    delay(500);
  }else if(direct==2){
    myStepper.step(-1024);            // 시계 방향으로 한바퀴 회전
    delay(500);
  }else{
    Serial.println("?");
  }
}
