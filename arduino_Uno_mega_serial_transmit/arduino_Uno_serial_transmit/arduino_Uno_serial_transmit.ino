void blinkLed();

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

char input;
void loop(){
  if(Serial.available()){
    blinkLed();
    input=Serial.read();
    if(input=='O'){
      Serial.println("Door is Opened");
    }else if(input=='M'){
      Serial.println("Manager Opened Door");
    }else if(input=='X'){
      Serial.println("Wrong number Detected 3 Times");
    }
  }
}

void blinkLed(){
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(500);
}
