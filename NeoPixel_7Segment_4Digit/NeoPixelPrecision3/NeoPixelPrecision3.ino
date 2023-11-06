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
}


//Test Loop
void loop() {
  updateSpeedDisplay(0.765);
  for(float i = 0.000;i<10;i+=0.001){
    updateSpeedDisplay(i);
    delay(10);
  }
}

/**
	 * setNum method, Sets provided digit on specified Display Segment:
	 * 
	 * @param startLED : Leading LED of Digit that needs to be changed.
   * Expected Input: 0, 8, 16 or 24. The start LEDs for the 4 digits to be displayed
   * @param num: Number to be changed to.
   * Expected Input: 0.000 to 9.999
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
   * @param interval: Float value of speed to be changed to
   * Expected Input: Float of precision 1 where 0<=speed<=9.9
	 */
void updateSpeedDisplay(float interval){
    //convert float to char to extract digits
    char intervalString[5];
    //Convert float to string to get values at ones and tenths place and decimal point
    dtostrf(interval, 3, 3, intervalString);
      //extract 1st digit from float string and cal setNum function
      setNum(0,intervalString[0]-'0');
      //skipping to index 2 due to decimal point location in expected input
      setNum(8,intervalString[2]-'0');
      setNum(15,intervalString[3]-'0');
      setNum(23,intervalString[4]-'0');
    pixels.setPixelColor(7,pixels.Color(0,255,0));
    pixels.show();
}
