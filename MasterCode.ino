#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    64
#define BRIGHTNESS  32
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define SOUND_PIN   A0
#define FSR_PIN     A1
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

int sensorValue = 0;
int abs_value = 0;
int baselineVal;
int fsrReading; // the analog reading from the FSR resistor divider
bool turnedOn = true;
bool talkingMode = false;  //By default, talking mode is false
bool talkingModeFlag = false;
int circleCountdown = 0;

void setup() {
  // put your setup code here, to run once:
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  Serial.begin(9600);
  pinMode(SOUND_PIN,INPUT);
  pinMode(FSR_PIN, INPUT);
  int p = analogRead(SOUND_PIN);
  for(int i=0; i < 7; i++) {
    baselineVal = baselineVal + analogRead(SOUND_PIN);
  }
  
  baselineVal = baselineVal / 7;
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void loop() {
  // put your main code here, to run repeatedly:
  fsrReading = analogRead(FSR_PIN);
  //////////////////////////////////////////////////////
  //////////FSR AND MICROPHONE PORTION OF CODE//////////
  //////////////////////////////////////////////////////
  //If the LED mask is turned on
  if(turnedOn){
    //turn it off if FSR is pressed
    if(fsrReading > 400) {
      turnedOn = false;
      turnAllOff();
      delay(200);
    }
    //or turn on talking mode if microphone is used
    else{
      sensorValue = analogRead(SOUND_PIN);
      abs_value = abs(sensorValue - baselineVal);
      Serial.println(abs_value);
      delay(10);
      if(abs_value > 5) { /* 2 if 3.3, 5 if 5V*/
        turnOnCircle();
        talkingMode = true;
        talkingModeFlag = true;
      }
      else{
        turnOnLine();
      }
    }
  }
  //If the FSR is pressed when the mask is off, turn on the line
  else{
    if(fsrReading > 400) {
      turnedOn = true;
      turnOnLine();
      delay(200);
    }
  }

  /////////////////////////////////////////////////////////
  //////////TALKING MODE HANDLING PORTION OF CODE//////////
  /////////////////////////////////////////////////////////
 //If talking mode is enabled, keep circle displayed for 200ms
 if(talkingMode){
    //if talking mode just started, start countdown timer
    if(talkingModeFlag){
        circleCountdown = 200;
        talkingModeFlag = false;
    }
    //if countdown is finished, turn on line, turn off talking mode
    if(circleCountdown == 0 && turnedOn){
        turnOnLine();
        talkingMode = false;
    }
    //decrement circleCountdown by 1 every ms
    else{
        circleCountdown--;
        delay(1);
    }
 }
}



  ///////////////////////////////////////////////////////////
  //////////FUNCTIONS NEIL WROTE TO CLEAN UP THINGS//////////
  ///////////////////////////////////////////////////////////
void turnOnCircle()
{
        leds[2] = CRGB::White; FastLED.show(); 
        leds[3] = CRGB::White; FastLED.show();
        leds[4] = CRGB::White; FastLED.show(); 
        leds[5] = CRGB::White; FastLED.show(); 
        leds[9] = CRGB::White; FastLED.show(); 
        leds[14] = CRGB::White; FastLED.show(); 
        leds[16] = CRGB::White; FastLED.show(); 
        leds[23] = CRGB::White; FastLED.show(); 
        leds[24] = CRGB::White; FastLED.show(); 
        leds[31] = CRGB::White; FastLED.show(); 
        leds[32] = CRGB::White; FastLED.show(); 
        leds[39] = CRGB::White; FastLED.show(); 
        leds[40] = CRGB::White; FastLED.show(); 
        leds[47] = CRGB::White; FastLED.show(); 
        leds[49] = CRGB::White; FastLED.show(); 
        leds[54] = CRGB::White; FastLED.show(); 
        leds[58] = CRGB::White; FastLED.show(); 
        leds[59] = CRGB::White; FastLED.show(); 
        leds[60] = CRGB::White; FastLED.show(); 
        leds[61] = CRGB::White; FastLED.show();

        leds[11] = CRGB::Black; FastLED.show();
        leds[12] = CRGB::Black; FastLED.show(); 
        leds[19] = CRGB::Black; FastLED.show();
        leds[20] = CRGB::Black; FastLED.show(); 
        leds[27] = CRGB::Black; FastLED.show();
        leds[28] = CRGB::Black; FastLED.show(); 
        leds[35] = CRGB::Black; FastLED.show();
        leds[36] = CRGB::Black; FastLED.show(); 
        leds[43] = CRGB::Black; FastLED.show();
        leds[44] = CRGB::Black; FastLED.show(); 
        leds[51] = CRGB::Black; FastLED.show();
        leds[52] = CRGB::Black; FastLED.show(); 
}

void turnOnLine()
{
        //Display Line
        leds[3] = CRGB::White; FastLED.show();
        leds[4] = CRGB::White; FastLED.show(); 
        leds[11] = CRGB::White; FastLED.show();
        leds[12] = CRGB::White; FastLED.show(); 
        leds[19] = CRGB::White; FastLED.show();
        leds[20] = CRGB::White; FastLED.show(); 
        leds[27] = CRGB::White; FastLED.show();
        leds[28] = CRGB::White; FastLED.show(); 
        leds[35] = CRGB::White; FastLED.show();
        leds[36] = CRGB::White; FastLED.show(); 
        leds[43] = CRGB::White; FastLED.show();
        leds[44] = CRGB::White; FastLED.show(); 
        leds[51] = CRGB::White; FastLED.show();
        leds[52] = CRGB::White; FastLED.show(); 
        leds[59] = CRGB::White; FastLED.show();
        leds[60] = CRGB::White; FastLED.show();
        //Erase Circle
        leds[2] = CRGB::Black; FastLED.show(); 
        leds[5] = CRGB::Black; FastLED.show(); 
        leds[9] = CRGB::Black; FastLED.show(); 
        leds[14] = CRGB::Black; FastLED.show(); 
        leds[16] = CRGB::Black; FastLED.show(); 
        leds[23] = CRGB::Black; FastLED.show(); 
        leds[24] = CRGB::Black; FastLED.show(); 
        leds[31] = CRGB::Black; FastLED.show(); 
        leds[32] = CRGB::Black; FastLED.show(); 
        leds[39] = CRGB::Black; FastLED.show(); 
        leds[40] = CRGB::Black; FastLED.show(); 
        leds[47] = CRGB::Black; FastLED.show(); 
        leds[49] = CRGB::Black; FastLED.show(); 
        leds[54] = CRGB::Black; FastLED.show(); 
        leds[58] = CRGB::Black; FastLED.show(); 
        leds[61] = CRGB::Black; FastLED.show(); 
}

void turnAllOff()
{
      leds[2] = CRGB::Black; FastLED.show(); 
      leds[5] = CRGB::Black; FastLED.show(); 
      leds[9] = CRGB::Black; FastLED.show(); 
      leds[14] = CRGB::Black; FastLED.show(); 
      leds[16] = CRGB::Black; FastLED.show(); 
      leds[23] = CRGB::Black; FastLED.show(); 
      leds[24] = CRGB::Black; FastLED.show(); 
      leds[31] = CRGB::Black; FastLED.show(); 
      leds[32] = CRGB::Black; FastLED.show(); 
      leds[39] = CRGB::Black; FastLED.show(); 
      leds[40] = CRGB::Black; FastLED.show(); 
      leds[47] = CRGB::Black; FastLED.show(); 
      leds[49] = CRGB::Black; FastLED.show(); 
      leds[54] = CRGB::Black; FastLED.show(); 
      leds[58] = CRGB::Black; FastLED.show(); 
      leds[61] = CRGB::Black; FastLED.show(); 

      leds[3] = CRGB::Black; FastLED.show();
      leds[4] = CRGB::Black; FastLED.show();
      leds[11] = CRGB::Black; FastLED.show();
      leds[12] = CRGB::Black; FastLED.show(); 
      leds[19] = CRGB::Black; FastLED.show();
      leds[20] = CRGB::Black; FastLED.show(); 
      leds[27] = CRGB::Black; FastLED.show();
      leds[28] = CRGB::Black; FastLED.show(); 
      leds[35] = CRGB::Black; FastLED.show();
      leds[36] = CRGB::Black; FastLED.show(); 
      leds[43] = CRGB::Black; FastLED.show();
      leds[44] = CRGB::Black; FastLED.show(); 
      leds[51] = CRGB::Black; FastLED.show();
      leds[52] = CRGB::Black; FastLED.show(); 
      leds[59] = CRGB::Black; FastLED.show();
      leds[60] = CRGB::Black; FastLED.show();  
}
