const int motorDirectionPin = 2; // Pin connected to the direction control of the motor driver
const int motorSpeedPin = 3;     // Pin connected to the speed control of the motor driver
const int sensorPin = 5;         // Pin connected to the IR sensor output
unsigned long previousMillis = 0;
unsigned long interval = 1050; // Time in milliseconds for expected interval
bool holeDetected = false;
// Variables to store the time of the last and current signal detections
unsigned long lastSignalTime = 0;
unsigned long currentSignalTime = 0;

// Variable to store the time difference
unsigned long timeDifference = 0;
int currentMotorSpeed = 128;

int adjustMotorSpeed(unsigned long timeTaken){
    signed long deviation = timeTaken - 1000;
    signed long adjustment = deviation * 0.15;
    currentMotorSpeed += adjustment;
    if (currentMotorSpeed < 10){
      currentMotorSpeed = 10;
    }
    else if (currentMotorSpeed > 255){
      currentMotorSpeed = 255;
    }
    analogWrite(motorSpeedPin, currentMotorSpeed);
}

void setup()
{
  pinMode(motorSpeedPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  Serial.begin(9600);
  analogWrite(motorSpeedPin, currentMotorSpeed); // Setting the default speed to 128 for now for testing purposes
}

void loop()
{
  int sensorValue = digitalRead(sensorPin);
  unsigned long currentMillis = millis();

  //  analogWrite(motorSpeedPin, 255); //Setting the default speed

  if (sensorValue == HIGH && lastSignalTime == 0)
  {
    // Record the time of the first signal detection
    lastSignalTime = millis();
  }
  else if (sensorValue == LOW && lastSignalTime != 0)
  {
    // Record the time of the second signal detection
    currentSignalTime = millis();

    // Calculate the time difference between consecutive signals
    timeDifference = currentSignalTime - lastSignalTime;
    adjustMotorSpeed(timeDifference);

    // Print the time difference to the Serial Monitor
    Serial.print("Time Difference: ");
    Serial.println(timeDifference);    

    // Reset the last signal time for the next measurement
    lastSignalTime = 0;
  }
}
