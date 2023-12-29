#include <Arduino.h>
#include <LiquidCrystal.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

const int firstBtnPin = 13;
const int secondBtnPin = 10;
const int thirdBtnPin = 9;

void setup() {
    Serial.begin(9600); 
    lcd.begin(16, 2);
    lcd.print("time");


}

void loop() {
    if(digitalRead(secondBtnPin) == HIGH) {
        lcd.clear();
    }

    if (Serial.available() > 0) {
        lcd.clear();
        String timestampString = Serial.readStringUntil('\n');
        const int splitter = timestampString.indexOf(' ');
        
        const String date = timestampString.substring(0, splitter);
        lcd.setCursor(0, 0);
        lcd.print(date);

        const String time = timestampString.substring(splitter+3);
        lcd.setCursor(0, 1);
        lcd.print(time);
    }

    delay(1000);
}
