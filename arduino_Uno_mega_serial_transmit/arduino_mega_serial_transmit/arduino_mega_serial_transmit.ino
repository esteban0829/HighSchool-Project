void blinkLed();

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(13,OUTPUT);
}

char input;
void loop(){
  if(Serial.available()){
    blinkLed();
    input=Serial.read();
    if(input=='O'){
      Serial.write('O');
      Serial1.write('O');
    }else if(input=='M'){
      Serial.write('M');
      Serial1.write('M');
    }else if(input=='X'){
      Serial.write('X');
      Serial1.write('X');
    }
  }
}


void blinkLed(){
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(500);
}
