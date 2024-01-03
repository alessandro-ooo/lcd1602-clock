#include <Arduino.h>
#include <LiquidCrystal.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

const int firstBtnPin = 13;
const int secondBtnPin = 10;
const int thirdBtnPin = 9;

void printMessage(String message) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Buon anno!");
    delay(5000);
}

void retrieveData() {
    if (Serial.available() > 0) {
        lcd.clear();
        String timestampString = Serial.readStringUntil('\n');
        const int splitter = timestampString.indexOf(' ');
        
        String date = timestampString.substring(0, splitter);
        lcd.setCursor(0, 0);
        lcd.print(date);

        String time = timestampString.substring(splitter+1);
        lcd.setCursor(0, 1);
        lcd.print(time);
    }
}

void setup() {
    Serial.begin(9600); 
    lcd.begin(16, 2);
    lcd.print("time");
}

void loop() {
    if(digitalRead(firstBtnPin) == HIGH) {
        Serial.end();
        printMessage("Buon anno");
        Serial.begin(9600); 
    }

    retrieveData();
}
