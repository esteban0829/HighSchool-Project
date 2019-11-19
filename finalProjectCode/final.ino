#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>

// 16진수로 표현되는 색깔을 실제 색깔이름에 대입
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//누르는 압력 제한
#define MINPRESSURE 200
#define MAXPRESSURE 1000

//좌표값 관련 변수 지정
const int XP=6,XM=A2,YP=A1,YM=7; //ID=0x9341
const int TS_LEFT=907,TS_RT=136,TS_TOP=942,TS_BOT=139;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

void testText();
void numberDisplayt(int *arr);
void resDisplay(int *arr);
int numberDetection();

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

    //숫자 표시
    int arr[12]={1,2,3,4,5,6,7,8,9,'*',0,'<'};
    numberDisplay(arr);
}


void loop(void) {
    
    int res[4]={' ',' ',' ',' '};    //입력된 숫자가 들어갈 배열

    tp = ts.getPoint();   //tp.z 는 ADC 값

    int buttonState=0, lastButtonState=0;
    unsigned long pressTime=0, lastPressTime=0;

    int i=0;
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
      
        buttonState=1;     //현재 버튼 상대
        lastButtonState=0; //과거 버튼 상태
        
        if(buttonState==1 && lastButtonState==0) lastPressTime=millis();   //버튼 처음 눌렸을 때 시간

        //버튼 처음 눌렸을 때의 시간과 그후 시간의 차이가 50ms가 넘어갈때 코드 실행
        if(millis()-lastPressTime>50){
          res[i]=numberDetection();   i=(i%4)+1;            
        }
        
        
    }else{
      lastButtonState=1; //과거 버튼 상태
      buttonState=0;     //현재 버튼 상태
    }

    resDisplay(res);
}



int numberDetection(){
  
  uint16_t xpos, ypos;  //화면 x,y 좌표
  tp = ts.getPoint();   //tp.x, tp.y 는 ADC 값
  pinMode(XM, OUTPUT);  //핀 공유할 수도 있으니까 핀 모드 바꿔주기
  pinMode(YP, OUTPUT);

  xpos = map(tp.x, TS_RT, TS_LEFT, 0, tft.width());    // xpos, ypos 좌표값 받기
  ypos = map(tp.y, TS_BOT, TS_TOP, 0, tft.height());   

  return 1;
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
  tft.drawFastHLine(0, 64-1, w, RED);
  tft.drawFastHLine(0, 128-1, w, RED);
  tft.drawFastHLine(0, 192-1, w, RED);
  tft.drawFastHLine(0, 254-1, w, RED);
  tft.drawFastVLine(80, 64-1, h-64-1, BLUE);
  tft.drawFastVLine(160, 64-1, h-64-1, BLUE);

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
}


void resDisplay(int *arr){
  int h = tft.height();              // h : 320
  int w = tft.width();               // w : 240

  //1 X 4 격자판 표시하는 코드 
  tft.drawFastVLine(0, 64, w, RED);
  tft.drawFastVLine(60, 0, h-(320-64), GREEN);
  tft.drawFastVLine(60, 0, h-(320-64), GREEN);

  //입력받은 숫자 표시하는 코드
  int idx=0;
  tft.setTextColor(WHITE);
  tft.setTextSize(7);
  for(int j=0;j<240;j+=60){
    tft.setCursor(j,0);
    if(arr[idx]>9) tft.fillRect(60*idx,0,60*(idx+1)); 
    else tft.print(arr[idx]);
    idx++;
  }
}
