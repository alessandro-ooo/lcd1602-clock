#include <Arduino.h>
#include <LiquidCrystal.h>
#include <ezButton.h>
#include <stdio.h>
#include <string.h>
#include <arduino-timer.h>

#define FIRST_BUTTON 13

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   
ezButton button(FIRST_BUTTON);  

bool Arduino_isGettingData;
auto timer = timer_create_default();
auto weatherUpdater = timer_create_default();

String currentWeather;

void CPPCOMM(String message) {
    char *to_send = &message[0];
    Serial.write(to_send);
}

void LCDWrite(String text, int line, bool clear = false) {
    if(clear == true) {
        lcd.clear();
    }

    lcd.setCursor(0, line);
    lcd.print(text);
}

bool refreshWeater(void *) {
    currentWeather = true;
    return true;
}

bool retrieveData(void *) {
    CPPCOMM("<time>");

    if (Serial.available() > 0) {
        lcd.clear();
        String timestampString = Serial.readStringUntil('\n');
        const int splitter = timestampString.indexOf(' ');
            
        String date = timestampString.substring(0, splitter);
        LCDWrite(date, 0);

        String time = timestampString.substring(splitter+1);
        LCDWrite(time, 1);
    }

    return true;
}

void setup() {
    Arduino_isGettingData = true;

    button.setDebounceTime(1);

    Serial.begin(9600); 
    lcd.begin(16, 2);
    lcd.print("waiting for data...");
    timer.every(1000, retrieveData);
    weatherUpdater.every(600000, refreshWeater);
}

void loop() {
    button.loop();

    if(Arduino_isGettingData == true) {
        CPPCOMM("<weather>");
        delay(5000);

        if(Serial.available()) {
            currentWeather = Serial.readString();
            Arduino_isGettingData = false;
        }
    }

    if(Arduino_isGettingData == false) {
        timer.tick();
        weatherUpdater.tick();
    }

    if(button.isPressed()) {
        Serial.end();
        LCDWrite(currentWeather, 0, true);
        delay(5000);
        Serial.begin(9600); 
    }
}
