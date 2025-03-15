
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2); // fformat elshasha  (Address,Width,Height )

#define echoPin 2 // ben3ml define lel pin D2 Arduino to Echo pin fel Sensor 
#define trigPin 3 // ben3ml define lel pin D3 Arduino to Trig pin fel Sensor

int duration; // ben3ml variable lel duration
              
int distance; // ben3ml variable lel distance
             

void setup()
{
    lcd.init(); // Initialize the lcd
    lcd.backlight(); // benftah elbacklight lel lcd

    pinMode(trigPin,OUTPUT); // benkhaly eltrigPin OUTPUT
            
    pinMode(echoPin, INPUT); // benkhaly elEchoPin INPUT
  
      // Initialize the serial communication
    Serial.begin(9600); 
  
    
    Serial.println("Distance measurement using Arduino Uno");  
                   

    delay(500);
}

void loop()
{
    digitalWrite(trigPin, LOW); // ben3ml eltrigPin low
    delayMicroseconds(2); // delay 2 microsecond
    digitalWrite(trigPin, HIGH); // ben3ml eltrigPin high
    delayMicroseconds(10); // delay 10 microsecond
    digitalWrite(trigPin, LOW); // ben3ml eltrigPin low
    duration = pulseIn(echoPin, HIGH); // ben3ml elduration = pulseIn(elEchoPin, HIGH)
    distance = duration * 0.0344 / 2; 
    Serial.print("Distance: "); 
    Serial.print(distance); 
    Serial.println(" cm");

    lcd.clear(); // clear the lcd
    lcd.setCursor(0, 0); // Set cursor for "Distance:" (0, 0)
        
    lcd.print("Distance:"); // print "Distance:" at (0, 0)
    lcd.setCursor(0,1); // Set cursor for output value  (0, 1)
                  
    lcd.print(distance); // print Output in cm at (0, 1)
    lcd.setCursor(4, 1); // move cursor to   (4, 1)
    lcd.print("cm"); // print "cm" at (4, 1)

    delay(100);
}
