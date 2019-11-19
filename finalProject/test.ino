#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

// 16진수로 표현되는 색깔을 실제 색깔이름에 대입
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

unsigned long testText();
unsigned long test();
void dummy();

void setup(void) {
    Serial.begin(9600);
    uint32_t when = millis();
    //    while (!Serial) ;   //hangs a Leonardo until you connect a Serial
    if (!Serial) delay(5000);           //allow some time for Leonardo
    Serial.println("Serial took " + String((millis() - when)) + "ms to start");
    //    tft.reset();                 //hardware reset
    uint16_t ID = tft.readID(); //
    Serial.print("ID = 0x");
    Serial.println(ID, HEX);
    if (ID == 0xD3D3) ID = 0x9481; // write-only shield
//    ID = 0x9329;                             // force ID
    tft.begin(ID);
}

void loop(void) {
    test();
}



unsigned long testText() {
    unsigned long start;        //프로그램 시작 시간을 넣을 start변수를 설정한다.
    tft.fillScreen(BLACK);      //화면을 검은색으로 초기화 해준다.
    start = micros();           //현재 프로그램 시간을 start변수에 넣는다.
    
    tft.setCursor(0, 4);        //커서 위치를 x,y로 해준다.
    
    tft.setTextColor(BLUE);     //화면에 "HighTech School"출력
    tft.setTextSize(5);
    tft.println("HighTech");
    tft.println("School");
    tft.println();
    
    tft.setTextColor(GREEN);    //화면에 "Team 2  Project"출력
    tft.setTextSize(4);
    tft.println("TEAM 2"); 
    tft.setTextSize(5);
    tft.println("Project");
    tft.println();
    
    tft.setTextColor(MAGENTA);  //화면에 "Smart DoorLock" 출력
    tft.println("Smart\nDoorLock");
    
    return micros() - start;    //이 함수가 실행하는데 걸린시간을 반환한다.
}



unsigned long test() {
    unsigned long start;        //프로그램 시작 시간을 넣을 start변수를 설정한다.
    tft.fillScreen(BLACK);      //화면을 검은색으로 초기화 해준다.
    start = micros();           //현재 프로그램 시간을 start변수에 넣는다.

    int x=5, y=5, w = tft.width(), h = tft.height();       //w=240    h=320

    /*
    Serial.print("w : ");
    Serial.print(w);
    Serial.print("\th : ");
    Serial.println(h);
    */
    
    tft.setRotation(0);
    tft.fillScreen(BLUE);
    delay(100);
    testText();
    //tft.drawLine(0, 0, 1, 1,RED);
    delay(500);
    tft.fillScreen(BLACK);
    tft.drawFastHLine(0, 80, 240, RED);
    tft.drawFastHLine(0, 160, 240, RED);
    tft.drawFastHLine(0, 240, 240, RED);
    tft.drawFastVLine(80, 0, h, BLUE);
    tft.drawFastVLine(160, 0, h, BLUE);
    delay(500);
    tft.fillScreen(BLACK);
    tft.drawRect(0,0,50,50,GREEN);
    tft.fillCircle(220,300,10,RED);
    tft.drawTriangle(
            100 , 160 , // peak
            50  , 260 , // bottom left
            150 , 260 , // bottom right
            BLUE);
    tft.fillRoundRect(50,50,100,100,5,GREEN);
    delay(500);
    
    return micros() - start;    //이 함수가 실행하는데 걸린시간을 반환한다.
}



void dummy(){
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
