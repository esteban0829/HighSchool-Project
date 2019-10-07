#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  //lcd pin set
String arr="";                          //output array

void setup(){
  lcd.begin(16,2);                      //lcd format(width,length)
  Serial.begin(9600);                   //Serial port 9600(bit/s)
}

void loop(){
  
  if(Serial.available()){               //check if theres serial input
    arr = Serial.read();                //put serial input int to array
    if(arr=="0"){                       //if array is "0" change array to blank
      arr="";
    }
  }
  lcd.setCursor(0,0);                   //set lcd cursor to 0,0(x,y)
  lcd.print(arr);                       //print arr on lcd
  
}
