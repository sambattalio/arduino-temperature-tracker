#include <LiquidCrystal.h>

// Global variables
const int temperaturePin = A5; // TMP36 pin
const int userTempPin = A0; // Potentiometer pin
const int redLEDpin = 9;
const int blueLEDpin = 10;
const int buttonPin = 2;
volatile bool isCelsius = false;

LiquidCrystal lcd(11,12,4,5,6,7);

void setup() 
{ 
  // Set pins to right mode
  pinMode(buttonPin, INPUT);
  pinMode(redLEDpin, OUTPUT);
  pinMode(blueLEDpin, OUTPUT);

  // attach interrupt to the 0 port
  attachInterrupt(0, unitChange, RISING);

  // init lcd
  lcd.begin(16,2);
}

void loop() 
{
  int tempReading; // Analog reading of temperature sensor
  int userTempReading; // Analog reading of potentiometer
  float tempVoltage; // Voltage from temperature sensor
  float readTemp; // Temperature Reading from Sensor (defaulted at Celsius)
  float setTemp; // Temperature set from Potentiometer (10-26.666 C)(50-80 F) 
  String tempOutput; // Temperature Output for LCD
  String setOutput; // Set Temp output for LCD

  // User's Set "room temperature" from pot
  userTempReading = analogRead(userTempPin);
  // Map to range of 10 - 26.6666 C
  setTemp = 1.0 * userTempReading / 1023 * 50 / 3 + 10;
  setTemp = oneDecimalPlace(setTemp);
  
  // Acutal reading to voltage from TMP36
  tempReading = analogRead(temperaturePin);
  // Map analog to voltage
  tempVoltage = 1.0 * tempReading / 1023 * 5;
  
  // Convert voltage to temperature
  readTemp = (tempVoltage - 0.5) * 100;

  // Find Celsius difference of two values
  float diff = readTemp - setTemp;
  // Map value to PWM where difference of (0-10) -> (0-255) PWM
  int led_pwm = diff / 10.0 * 255; 
  // Make sure pwm is within 0-255 magnitude
  led_pwm = min(max(led_pwm,-255),255);
  
  if (diff > 0.5) // if diff of temp and set temp is positive 
  {
    // Red = PWM / Blue = OFF
    analogWrite(redLEDpin,led_pwm);
    analogWrite(blueLEDpin,LOW); 
  } 
  else if(diff < -.5) // if diff of temp and set temp is neg
  {
    // Flip PWM value to make positive again
    led_pwm = -1.0 * led_pwm; 
    // Red = OFF / Blue = PWM
    analogWrite(redLEDpin,LOW);
    analogWrite(blueLEDpin,led_pwm);
  } 
  else // diff isn't bigger than threshold
  {
      // both off
      analogWrite(redLEDpin, LOW);
      analogWrite(blueLEDpin,LOW);
  }
  

  // Convert to farenheit or keep Celsius
  if (isCelsius)
  { 
      // Make output strings
      tempOutput = String(readTemp) + " C";
      setOutput = String(setTemp) + " C";
  }
  else
  { 
    readTemp = toFarenheit(readTemp); 
    setTemp = toFarenheit(setTemp);
    setTemp = oneDecimalPlace(setTemp);
    // Make output strings
    tempOutput = String(readTemp) + " F";
    setOutput = String(setTemp) + " F";
  }


  // Print output to LCD
  lcd.clear();
  lcd.print("Temp:" + tempOutput);
  lcd.setCursor(0,1);
  lcd.print("Set Temp:" + setOutput);
  // Delay for 1 second
  delay(1000);
}

void unitChange()
{
  // flip boolean value
  isCelsius = !isCelsius;
}

float oneDecimalPlace(float input)
{
  // Return float value rounded to one decimal place
  return round(input * 10.0) / 10.0; 
}

float toFarenheit(float celsius)
{
  // Convert using equation C * 9/5 + 32
  return (celsius * 9.0 / 5.0) + 32;
}


