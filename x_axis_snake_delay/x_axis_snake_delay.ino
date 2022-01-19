
#include <FastLED.h>
#define NUM_LEDS 48
#define DATA_PIN 5
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define BRIGHTNESS 15
#define VOLTS 5
#define MAX_AMPS 500//in mA
#define ROWS 4
#define COLUMNS 12

const unsigned long interval = 2000;//pauses 2000 ms between updates
unsigned long previous_time = 0;//pauses 200 ms between updates

byte food_x =0;
byte food_y =0;

byte snake_size =1;
byte head_x =0;
byte head_y =0;
bool eat = false;
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  delay(5000);  // give enough time to open the serial monitor after uploading
  Serial.println("Starting...");
  //////////////////////////////////////////
  food_x = random(0, 11);
  FastLED.addLeds<CHIPSET,DATA_PIN,COLOR_ORDER>(leds,NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS,MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();


}

void loop () {
  snake_size=1;
  head_x=0;//resets snake
  unsigned long cur_time = millis();//current running time
  for(int i=0;i<COLUMNS*ROWS-1;i++){//snake eats 12 times
    head_x = 0;//restarts at bottom again
    food_x = random(2, COLUMNS*ROWS-1);//rand number 
    eat=false;
    while(head_x!=COLUMNS*ROWS){
      Serial.println(food_x);
      Serial.println("loop?"); // prints time since program started
      if(eat == false){
        leds[food_x] = CRGB::Gold;//display food
      }
      display_snake(head_x,snake_size);
      FastLED.show();
     

      if(head_x==food_x){
        Serial.println("gobble"); // prints time since program started
        eat = true;
        snake_size+=1;
        leds[food_x] = CRGB::Red;//display food
        FastLED.show();

        for(int j=0;j<COLUMNS*ROWS;j++){
          leds[j].fadeToBlackBy(200);
        }

        FastLED.show();
        delay(400);
        
        
      
      }
      head_x+=1;//snake moves by 1

      FastLED.clear();
      delay(50);
    }
  }
  
}
void display_snake(byte head_x,byte snake_size){
  if(head_x<snake_size-1){
    Serial.println("went into if of display snake");
    for(int i=head_x;i>=0;i--){
        leds[i] = CRGB::Green;//displays snake
        leds[head_x]=CRGB::LimeGreen;
      }
  }
  else{
    for(int j=head_x;j>head_x-snake_size;j--){
      Serial.println("head is at ");
      Serial.println(head_x);
      Serial.println("went into else of display snake");
        leds[j] = CRGB::Green;//displays snake
        leds[head_x]=CRGB::LimeGreen;
      } 
  }
}
