#include <FastLED.h>
#include <AudioAnalyzer.h>
#include <math.h>

Analyzer Audio = Analyzer(4,5,4);//Strobe pin ->4  RST pin ->5 Analog Pin ->5
//Analyzer Audio = Analyzer();//Strobe->4 RST->5 Analog->0

#define led_pin 11
#define led_count 88  //44 is the middle led


int FreqVal[7]; //hold the current frequency
int FreqVal2[7];

unsigned currenttime;
unsigned preavioustime = 0;


CRGB leds [led_count];

void setup(){
  Serial.begin (38400);
  Audio.Init ();
  FastLED.addLeds<WS2812B, led_pin, GRB>(leds, led_count);
  FastLED.setBrightness (50);

}

void hertz_6250(float FreqValue) {
  //Serial.println (FreqValue);
  float FreqValHolder;
  FreqValHolder = FreqValue;

  if (FreqValHolder < - 0.00) {
    for (int i = 24; i <= 64;  i++) {
        leds[i].setRGB (174,4,104);
    }
  }
    FastLED.show();
  fadeToBlackBy(leds, led_count, 100);
}

void hertz_160 (float FreqValue) {
  //Serial.println (FreqValue);
  float FreqValHolder;
  FreqValHolder = FreqValue;
  currenttime = millis();

  if (FreqValHolder < -0.00) {
    for (int i = led_count; i >= led_count - 8; i--) {
      leds[i].setRGB (0,205,100);
        //FastLED.show();
    }
  }
  FastLED.show();
  fadeToBlackBy(leds, led_count, 10);
}

void hertz_160_2 (float FreqValue) {
  //Serial.println (FreqValue);
  FastLED.setBrightness (100);
  float FreqValHolder;
  FreqValHolder = FreqValue;
  currenttime = millis();

  if (FreqValHolder < -0.00) {
    for (int i = 0; i <= 8; i++) {
      leds[i].setRGB (255,103,0);
        //FastLED.show();
    }
  }
  FastLED.show();
  fadeToBlackBy(leds, led_count, 10);
}


void FreqReading(int Delay) {
  Audio.ReadFreq(FreqVal);  //Return 7 values of 7 bands pass filiter
                          //Frequency (Hz): 63    160   400   1K    2.5K    6.25K   16K
                        //FreqVal[]:      0       1     2    3      4       5      6

  for (int i= 0; i < 7; i++) {
          FreqVal2[i] = (max((FreqVal[i] - 100), 0));
          /*Serial.print(sin(FreqVal2[i] * (PI / 180)));
    if(i < 6)
      Serial.print(",");
      else  Serial.println();*/
  }
  hertz_160 (sin(FreqVal2[1] * (PI / 180)));
  hertz_160_2 (sin(FreqVal2[1] * (PI / 180)));
  hertz_6250 (sin(FreqVal2[5] * (PI / 180)));
}

void loop() {
  FreqReading (20);
}