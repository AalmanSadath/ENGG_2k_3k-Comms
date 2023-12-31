const int motorDirectionPin = 8; // Pin connected to the direction control of the motor driver
const int motorSpeedPin = 5;     // Pin connected to the speed control of the motor driver
const int sensorPin = 6;         // Pin connected to the IR sensor output
unsigned long previousMillis = 0;
unsigned long interval = 1050; // Time in milliseconds for expected interval
bool holeDetected = false;
bool onWall = false;
// Variables to store the time of the last and current signal detections
unsigned long lastSignalTime = 0;
unsigned long currentSignalTime = 0;

// Variable to store the time difference
unsigned long timeDifference = 0;
int currentMotorSpeed = 125;
const int defaultSpeed = 125;

int adjustMotorSpeed(unsigned long timeTaken){
    signed long deviation = timeTaken - 1000;
    signed long adjustment = deviation * 0.15;
    currentMotorSpeed += adjustment;
    if (currentMotorSpeed < 100){
      currentMotorSpeed = 100;
    }
    else if (currentMotorSpeed > 255){
      currentMotorSpeed = 255;
    }
    analogWrite(motorSpeedPin, currentMotorSpeed);

}

void setup()
{
  pinMode(motorSpeedPin, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  Serial.begin(9600);
  analogWrite(motorSpeedPin, currentMotorSpeed);
  analogWrite(3, 90); // Setting the default speed to 128 for now for testing purposes
}

void loop()
{
  //pulse the motor speed to reduce momentum at stop
  delay(20);
  analogWrite(motorSpeedPin, 0);
  delay(20);
  analogWrite(motorSpeedPin, defaultSpeed);

  int sensorValue = digitalRead(sensorPin);
  unsigned long currentMillis = millis();

  //  analogWrite(motorSpeedPin, 255); //Setting the default speed

  if (sensorValue == HIGH && lastSignalTime == 0)
  {
    // Record the time of the first signal detection
    lastSignalTime = millis();
  }
  else if(sensorValue == LOW && lastSignalTime != 0 && !onWall){
    onWall=true;
  }
  else if(lastSignalTime !=0 && (millis()-lastSignalTime)>1000 && digitalRead(sensorPin)==LOW){
      analogWrite(motorSpeedPin,170);
      while(digitalRead(sensorPin)==LOW){}
    }
  else if (sensorValue == HIGH && lastSignalTime != 0 && onWall)
  {
    // Record the time of the second signal detection
    currentSignalTime = millis();

    // Calculate the time difference between consecutive signals
    timeDifference = currentSignalTime - lastSignalTime;
    analogWrite(motorSpeedPin, 0);
    if(timeDifference<1000){
      delay(1000-timeDifference);
    }
    analogWrite(motorSpeedPin,defaultSpeed);
    //adjustMotorSpeed(timeDifference);
    // analogWrite(motorSpeedPin, currentMotorSpeed);

    // Print the time difference to the Serial Monitor
    Serial.print("Time Difference: ");
    Serial.println(timeDifference);
    Serial.print("Current motor speed: ");
    Serial.println(currentMotorSpeed);




    // Reset the last signal time for the next measurement
    onWall=false;
    lastSignalTime = 0;
  }
}