#include <Adafruit_NeoPixel.h>

#define PIN 2	 // input pin Neopixel is attached to

#define NUMPIXELS      30 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1000; // timing delay in milliseconds
//Nested array of boolean values corresponding to LEDs based on design specifications of 7 Segment Display. Numbers in Array correspond to array position. 
int ledStates[10][7]={{1,1,1,1,0,1,1},{0,0,0,1,0,1,0},{1,0,1,1,1,0,1},{0,0,1,1,1,1,1},{0,1,0,1,1,1,0},{0,1,1,0,1,1,1},{1,1,1,0,1,1,1},{0,0,1,1,0,1,0},{1,1,1,1,1,1,1},{0,1,1,1,1,1,1}};

void setup() {
  // Initialize the NeoPixel library.
  pixels.begin();
  //updateSpeedDisplay(2,8.8);
}


//Test Loop
void loop() {
  //testing all digits displaying on LED Strip
  //for (int i=0; i < 10; i++) {
  //  //Call SetNum function with numbers from 0 to 9
  updateSpeedDisplay(0.573);
  //  pixels.setPixelColor(7,pixels.Color(0,255,0));
  //  pixels.setPixelColor(22,pixels.Color(0,255,0));
//
  //  // This sends the updated pixel color to the hardware.
   // pixels.show();
//
  //  // Delay for a period of time (in milliseconds).
  //  delay(delayval); 
 // }
 delay(1000);
 pixels.show();
}

/**
	 * setNum method, Sets provided digit on specified Display Segment:
	 * 
	 * @param startLED : Leading LED of Digit that needs to be changed.
   * Expected Input: 0, 8, 16 or 24. The start LEDs for the 4 digits to be displayed
   * @param num: Number to be changed to.
   * Expected Input: 0 to 9
	 */
void setNum(int startLED, int num){

    for(int i=0; i<=6; i++){
      if(ledStates[num][i]){
        pixels.setPixelColor(startLED+i,pixels.Color(0,0,255));
      }
      else{
        pixels.setPixelColor(startLED+i,pixels.Color(0,0,0));
      }
    }
}

/**
	 * updateSpeed method, Set Provided Float to Digits on LED Display
	 * 
	 * @param wheelNum : Wheel Number whose corresponding speed needs to be changed on LED display
   * Expected Input: 1 or 2
   * @param speed: Float value of speed to be changed to
   * Expected Input: Float of precision 1 where 0<=speed<=9.9
	 */
void updateSpeedDisplay(float speed){
    //convert float to char to extract digits
    char speedString[5];
    //Convert float to string to get values at ones and tenths place and decimal point
    dtostrf(speed, 3, 3, speedString);
      //extract 1st digit from float string and cal setNum function
      setNum(0,speedString[0]-'0');
      //skipping to index 2 due to decimal point location in expected input
      setNum(8,speedString[2]-'0');
      setNum(15,speedString[3]-'0');
      setNum(23,speedString[4]-'0');
    pixels.setPixelColor(7,pixels.Color(0,255,0));
    pixels.show();
}
