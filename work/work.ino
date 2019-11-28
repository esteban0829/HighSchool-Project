#include <Stepper.h>

//핀 변수 설정
//---------------------------------
int rainDropPin = A0;                                // 빗방울센서 핀을 A0으로 설정
int tmpSensorPin = A1;                               // 온도 센서  핀을 A1으로 설정
Stepper myStepper(2048,11,9,10,8);    // 모터 드라이브에 연결된 핀 IN4, IN2, IN3, IN1
//---------------------------------


//---------------------------------
//빗물감지함수
//빗물이 감지되면 1 안되면 0을 반환함
int rainState(int pin);

//온도감지센서
//설정값 이상의 온도를 감지하면 1 안하면 0을 반환함
float tmpState(int pin,int limit);

//스테핑 모터 함수
//바퀴수를 입력하면 회전함
//예 : steppMotorControl(2) -> 오른쪽 2바퀴
//예 : steppMotorControl(-3) -> 왼쪽 3바퀴
void steppMotorControl(int turn);
//---------------------------------


void setup(){
  pinMode(rainDropPin,INPUT);
  pinMode(tmpSensorPin,INPUT);
  Serial.begin(9600);
}

//코드설명
//비나 온도가 설정온도보다 올라가면 오른쪽으로 설정된바퀴가 돈다.
//비가 그치거나 온도가 설정온도보다 내려가면 설정된바퀴가 내려간다.
//------------------------------------------------
unsigned int start;
int state=0;
int lastState=0;
void loop(){
  
  if(rainState(rainDropPin)||tmpState(tmpSensorPin,30)) state=1;
  else state=0;


  if(lastState==0 && state==1) steppMotorControl(1);
  if(lastState==1 && state==0) steppMotorControl(-1);

  lastState=state;
  delay(10);
}


//사용자 함수
//---------------------------------------------------------------------------------------------------
//빗물감지함수
//빗물이 감지되면 1 안되면 0을 반환함
int rainState(int pin){
  Serial.print("rain : ");
  Serial.print(analogRead(pin));
  if(analogRead(pin)<500) return 1;
  else return 0;
}

//온도감지센서
//설정값 이상의 온도를 감지하면 1 안하면 0을 반환함
float tmpState(int pin,int limit){
  int sensor=analogRead(tmpSensorPin);
  float temp = ((sensor*5000.0/1024.0)-500)/10.0;     // 온도센서의 값을 전압으로 변환뒤 Celsius로 변환
  Serial.print("\ttmpe : ");
  Serial.println(temp);
  if(temp>limit) return 1;
  else return 0;
}

//스테핑 모터 함수
//바퀴수를 입력하면 회전함
//예 : steppMotorControl(2) -> 오른쪽 2바퀴
//예 : steppMotorControl(-3) -> 왼쪽 3바퀴
void steppMotorControl(int turn){
      myStepper.setSpeed(14);
      myStepper.step(2048*turn);
}
