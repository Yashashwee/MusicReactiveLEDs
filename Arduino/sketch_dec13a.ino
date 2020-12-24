#include<FastLED.h>
#include<math.h>
#define LED_PIN 7
#define NUM_LEDS 60
#define INPUT_SIZE 30
CRGB leds[NUM_LEDS];

String inBuffer;
byte incoming;
int brit=100;
//char input[INPUT_SIZE +1];
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  for(int i=0; i<NUM_LEDS; i++)  //Turn off all the LEDs.
  {
  leds[i] = CRGB::Black;
  }
  FastLED.show();
}
//void ledChange(int arr) {
//  int x;
//  int y;
//  int r;
//  int lookUp[11][3] = {
//    {0,0,0},
//    { 63, 81, 54},
//    {33, 11, 77},
//    {91, 78, 13},
//    {90, 15, 75},
//    {17, 119,  34},
//    {171,  76,  76},
//    {105, 168, 105},
//    {115, 207, 115},
//    { 50, 200,  50},
//    {243, 162, 216}
//    
//  };
//  for (int i = 0; i < 30; i++) {
//    
// 
//    r = arr / pow(10, i);
// 
//    r = r % 10;
//    
//    Serial.print(r);
//    //x = arr[i];
//    //y = arr[NUM_LEDS-i-1];
//    
//    leds[i] = CRGB ( lookUp[x][0], lookUp[x][1], lookUp[x][2]);
//    leds[NUM_LEDS - i - 1] = CRGB(lookUp[y][0], lookUp[y][1], lookUp[y][2]);
//    
//    delay(40);
//  }
//  FastLED.show();
//  
//}
void loop() {      
  if (Serial.available()){
  incoming = Serial.read();
  if (incoming =='p'){
    handleCommand();
    inBuffer="";
    
  }else {
    inBuffer+= (char)incoming;
  }


  }
}

void handleCommand(){
  int n,val=0;
  String bufLeft = inBuffer;
  n=bufLeft.substring(0,bufLeft.indexOf(' ')).toInt();
  for(int i= 0;i<n;i++)
  {
//    n=bufLeft.substring(0,bufLeft.indexOf(' ')).toInt();
//    bufLeft = bufLeft.substring(bufLeft.indexOf(' ') + 1);
//    val=map(n,0,10,0,255);
    leds[i] = CHSV (val,200,100);
    leds[NUM_LEDS - i - 1] = CHSV(val,200,200);
    val+=20;  
    //delay(10);
    
  }
  brit+=10;
  if(brit>200)
    brit=100;
  for(int i=val+1; i<=NUM_LEDS; i++)
  {
  leds[i].nscale8(10);
  leds[NUM_LEDS - i - 1].nscale8(10);
  }
  FastLED.show();
}

//9 8 7 1 8 7 5 4 9 4 1 7 4 6 3 6 1 6 2 2 8 1 5 1 2 1 3 7 5 1 p
