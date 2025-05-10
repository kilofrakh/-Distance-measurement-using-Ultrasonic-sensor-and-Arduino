#include <LiquidCrystal_I2C.h>
#include <RemoteXY.h>
#include <SoftwareSerial.h>
#include <SD.h>

// RemoteXY connection settings
#define REMOTEXY_MODE__SOFTSERIAL // benestakhdem software serial lel Bluetooth
#define REMOTEXY_SERIAL_RX 10 // el pin da beyconnect ma3 TX fel HC-05
#define REMOTEXY_SERIAL_TX 11 // el pin da beyconnect ma3 RX fel HC-05
#define REMOTEXY_SERIAL_SPEED 9600 // ben7aded el speed b 9600

// RemoteXY interface configuration
#pragma pack(push, 1) // ben3ml align lel data fel memory lel RemoteXY
uint8_t RemoteXY_CONF[] = {
  255,1,0,0,0,35,0,8,13,1,
  1,0,5,10,70,20,2,26,31,68,
  105,115,116,97,110,99,101,0
};
struct {
  char distance_txt[30]; // variable da bey7ot eldistance text lel RemoteXY
} RemoteXY;
#pragma pack(pop)

// ben3ml LCD object ma3 address 0x27, 16 columns, w 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ben3ml define lel pins lel ultrasonic sensor
#define echoPin 2 // el pin da beyestanna el echo signal
#define trigPin 3 // el pin da beyeb3at el trigger signal
#define chipSelect 4 // el pin da beyconnect lel SD card module

int duration; // variable da bey7ot el time lel echo
int distance; // variable da bey7ot eldistance elly et7seb
file dataFile; // variable da bey7ot el file lel SD card

void setup() {
    lcd.init(); // ben3ml initialize lel lcd
    lcd.backlight(); // benftah elbacklight lel lcd

    pinMode(trigPin, OUTPUT); // benkhaly eltrigPin OUTPUT
    pinMode(echoPin, INPUT); // benkhaly elEchoPin INPUT

    Serial.begin(9600); // benftah el serial communication
    Serial.println("Distance measurement using Arduino Uno"); // benprint message fel serial monitor
    
    if (!SD.begin(chipSelect)) { // bencheck 3la el SD card
        Serial.println("Card failed, or not present"); // benprint message fel serial monitor
        return; // ben3ml return
    }






    Serial.println("Card initialized."); // benprint message fel serial monitor

    dataFile = SD.open("datalog.txt", FILE_WRITE); // benftah el file lel writing
    if (dataFile) { // bencheck 3la el file
        dataFile.println("Distance Data"); // benprint message fel file
        
    } else {
        Serial.println("Error opening datalog.txt"); // benprint message fel serial monitor
    }


    RemoteXY_Init(); // ben3ml initialize lel RemoteXY

    delay(500); // benestanna 500ms
}

void loop() {
    RemoteXY_Handler(); // benhandle el RemoteXY communication

    digitalWrite(trigPin, LOW); // ben3ml eltrigPin low
    delayMicroseconds(2); // benestanna 2 microsecond
    digitalWrite(trigPin, HIGH); // ben3ml eltrigPin high
    delayMicroseconds(10); // benestanna 10 microsecond
    digitalWrite(trigPin, LOW); // ben3ml eltrigPin low

    duration = pulseIn(echoPin, HIGH); // ben2ees elduration bel pulseIn
    distance = duration * 0.0344 / 2; // ben7seb eldistance

    Serial.print("Distance: "); // benprint "Distance:" fel serial monitor
    Serial.print(distance); // benprint eldistance fel serial monitor
    Serial.println(" cm"); // benprint "cm" fel serial monitor

    lcd.clear(); // benms7 el lcd
    lcd.setCursor(0, 0); // ben7ot el cursor fe (0, 0)
    lcd.print("Distance:"); // benprint "Distance:" fel lcd
    lcd.setCursor(0, 1); // ben7ot el cursor fe (0, 1)
    lcd.print(distance); // benprint eldistance fel lcd
    lcd.setCursor(4, 1); // ben7ot el cursor fe (4, 1)
    lcd.print("cm"); // benprint "cm" fel lcd

    String distStr = String(distance) + " cm"; // ben7awel eldistance le string
    distStr.toCharArray(RemoteXY.distance_txt, 30); // ben7ot el string fel RemoteXY text field




    if (dataFile) {
        dataFile.print("Distance: ");
        dataFile.print(distance);
        dataFile.println(" cm");
        dataFile.flush();  // Ensure data is written to SD card
      }


    else {
        Serial.println("Error writing to datalog.txt"); // benprint message fel serial monitor
    }

    delay(500); // benestanna 500ms
    
}
