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

void testText();
void numberDisplayt(int *arr);

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
    tft.fillScreen(BLACK);      //화면을 검은색으로 초기화 해준다.
    testText();

    //------------------------------------   숫자 표시
    int arr[12]={1,2,3,4,5,6,7,8,9,'*',0,'<'};
    numberDisplay(arr);
}

void loop(void) {
    
}



void testText() {
  
    tft.fillScreen(BLACK);      //화면을 검은색으로 초기화 해준다.
    
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

    delay(500);                //디스플레이 표시 5초후 화면을 검은색을 만든다.
    tft.fillScreen(BLACK);     
}



void numberDisplay(int *arr) {
  int h = tft.height();              // h : 320
  int w=tft.width();                 // w : 240

  //3 X 4 격자판 표시하는 코드 
  tft.drawFastHLine(0, 64, w, RED);
  tft.drawFastHLine(0, 128, w, RED);
  tft.drawFastHLine(0, 192, w, RED);
  tft.drawFastHLine(0, 254, w, RED);
  tft.drawFastVLine(80, 64, h-64, BLUE);
  tft.drawFastVLine(160, 64, h-64, BLUE);

  //입력받은 숫자 표시하는 코드
  int idx=0;
  tft.setTextColor(WHITE);
  tft.setTextSize(7);
  for(int i=64;i<320;i+=64){
    for(int j=0;j<240;j+=80){
      tft.setCursor(j+23,i+10);
      if(arr[idx]>9) tft.print((char)arr[idx]);  
      else tft.print(arr[idx]);
      idx++;
    }
  }
  
  delay(10);
}
