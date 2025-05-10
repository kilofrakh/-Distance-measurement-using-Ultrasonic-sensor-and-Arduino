#include <LiquidCrystal_I2C.h>

#define trigPin
#define echoPin 

LiquidCrystal_I2C
    lcd(0x20, 16, 2);



int dist; // Variable to store distance calculated usingint duration
int dur;
void setup()
{
  	lcd.init(); // Initialize the lcd
	lcd.backlight(); // Turn on the Backlight
    pinMode(trigPin,
            OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

    // Serial Communication is starting with 9600 of
    // baudrate speed
    Serial.begin(9600);

    // The text to be printed in serial monitor
    Serial.println(
        "Distance measurement using Arduino Uno.");
    delay(500);
}

void loop()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // wait for 2 ms to avoid
                          // collision in serial monitor

    digitalWrite(
        trigPin,
        HIGH); // turn on the Trigger to generate pulse
    delayMicroseconds(
        10); // keep the trigger "ON" for 10 ms to generate
             // pulse for 10 ms.

    digitalWrite(trigPin,
                 LOW); // Turn off the pulse trigger to stop
                       // pulse generation

    // If pulse reached the receiver echoPin
    // become high Then pulseIn() returns the
    // time taken by the pulse to reach the
    // receiver

    dur = pulseIn(echoPin, HIGH);
    dist
        = dur * 0.0344 / 2; // Expression to calculate
                                 // distance using time

    Serial.print("Distance: ");
    Serial.print(
        dist); // Print the output in serial monitor
    Serial.println(" cm");
    delay(100);
  
  
  lcd.clear(); // Clear the display buffer
    lcd.setCursor(0, 0); // Set cursor for "Distance:" (Column, Row)
        
    lcd.print("Distance:"); // print "Distance:" at (0, 0)
    lcd.setCursor(0,1); // Set cursor for output value  (0, 1)
                  
    lcd.print(dist); // print Output in cm at (0, 1)
    lcd.setCursor(4, 1); // move cursor to   (4, 1)
    lcd.print("cm"); // print "cm" at (4, 1)

    delay(100);
}
