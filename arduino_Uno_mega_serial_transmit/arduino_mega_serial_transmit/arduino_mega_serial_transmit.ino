void blinkLed();

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(13,OUTPUT);
}

int input;
void loop() {
  if(Serial1.available()){
    input=Serial1.read();
    Serial.println(input);
    if(input==1){
      blinkLed();
    }
  }
}

void blinkLed(){
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(500);
}
