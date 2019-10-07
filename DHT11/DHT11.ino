#include "DHT.h"

DHT dht(8,DHT11);

void setup(){
  Serial.begin(9600);
}

void loop(){
  
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  
  Serial.print("Humi : ");Serial.print(h);Serial.println(" %");
  Serial.print("Temp : ");Serial.print(t);Serial.println(" c");

}
