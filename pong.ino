
#include "FastLED.h"
#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    246
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120


const byte interruptPin = 3;
const byte interruptPin2 = 2;
volatile byte alpha = LOW;
volatile byte beta = LOW;
volatile byte aturn = HIGH;
volatile byte jack = HIGH;
volatile byte jill = HIGH;
volatile byte loserA = LOW;
volatile byte loserB = LOW;

void setup() {


  pinMode(interruptPin, INPUT);
  pinMode(interruptPin2, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), smashA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), smashB, CHANGE);
  Serial.begin(9600);
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);
  

}
void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void loop() {
   
  
  if (loserB == HIGH){
    loseB();
  }
  if (loserA == HIGH){
    loseA();
  }
  
  Serial.println("neutral.");
  if (aturn == HIGH){  
  sendA();
  }
  if (aturn == LOW){
  sendB();
  }





}
 
   
	


  
  



#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void sendA(){
  static uint8_t hue = 0;
  Serial.print("sendA");
	// First slide the led in one direction
    if (jack == HIGH){
      
      for(int i = 0; i < NUM_LEDS; i++) {
		
        // Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		//if (i >= NUM_LEDS-10){
                //  loserB = HIGH;
                //}
                jack = LOW;
                jill = HIGH;
                fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
  
      }
      
}
}
void sendB(){
  static uint8_t hue = 0;
  Serial.print("sendB");
if (jill == HIGH){
  
	// Now go in the other direction.  
	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
                fadeall();
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		
                jill = LOW;
                jack = HIGH;
                fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
}
}}

void smashA() {
  alpha = !alpha;
  Serial.println("player1!");
  aturn = LOW;
}
void smashB() {
  beta = !beta;
  Serial.println("player2!");
  aturn = HIGH;
}

void loseA(){
    leds[6] = CRGB::Green;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[6] = CRGB::Black;
  FastLED.show();
  delay(100);
}
void loseB(){
    leds[90] = CRGB::Green;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[90] = CRGB::Black;
  FastLED.show();
  delay(100);
}
