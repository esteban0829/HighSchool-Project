#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
//#include <Adafruit_TFTLCD.h>
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


void test();


void setup(void) {
    Serial.begin(9600);
    uint32_t when = millis();
    if (!Serial) delay(5000);           //리오나오드는 시간을 좀 준다.
    Serial.println("Serial took " + String((millis() - when)) + "ms to start");
    uint16_t ID = tft.readID(); //
    Serial.print("ID = 0x");
    Serial.println(ID, HEX);
    if (ID == 0xD3D3) ID = 0x9481; // write-only shield
//    ID = 0x9329;                             // force ID
    tft.begin(ID);
    tft.fillScreen(BLACK);
}

void loop(void) {
  test();
}


void test(){
  //width, height
  int w=tft.width();
  int h=tft.height();
  //------------------------------------
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  //------------------------------------
  tft.drawLine(0,10,240,10,RED);
  //------------------------------------
  tft.drawFastHLine(0,20, w, YELLOW);
  //------------------------------------
  tft.drawRect(0,20,20,30,GREEN);
  //------------------------------------
  tft.fillRect(10,30,20,40,RED);
  //------------------------------------
  tft.drawCircle(100,100,50,GREEN);
  //------------------------------------
  tft.fillCircle(50,50,25,YELLOW);
  //------------------------------------
  tft.drawTriangle(
    0,0, // peak
    0,50, // bottom left
    50,50, // bottom right
    BLUE);
  //------------------------------------
  tft.fillTriangle(
    5,5, // peak
    5,45, // bottom left
    45,45, // bottom right
    RED);
  //------------------------------------
  tft.drawRoundRect(100,100,150,150,10,RED);
  //------------------------------------
  tft.fillRoundRect(200,200,250,250,10,GREEN);
  //------------------------------------
  delay(5000);
}
