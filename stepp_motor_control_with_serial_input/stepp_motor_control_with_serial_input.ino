/*
  28BYJ-48 stepper motor and ULN2003 Arduino
  28BJ-48 스테퍼 모터를 ULN2003모듈을 이용하여 조종하는 프로그램이다.
*/

#include <Stepper.h>

void stepping_motor_control();

void setup(){
  Serial.begin(9600);
  int stepsPerRevolution=2048;                      // 2048:한바퀴(360도), 1024:반바퀴(180도), 512:1/4바퀴(90도)
  Stepper myStepper(stepsPerRevolution,11,9,10,8);  // 모터 드라이브에 연결된 핀 IN4, IN2, IN3, IN1
}

 

void loop(){ 
   if (Serial.available()){
     int direct = Serial.parseInt();
     stepping_motor_control(direct);
   } 
}

 

void stepping_motor_control(int direct){
      myStepper.setSpeed(14);                           //스텝 모터 스피드 설정
      
      if(direct==1){
        myStepper.step(2048);             // 시계 반대 방향으로 한바퀴 회전
        delay(500);
      }else if(direct==2){
        myStepper.step(-2048);            // 시계 방향으로 한바퀴 회전
        delay(500);
      }else{
        Serial.println("?");
      }
}
