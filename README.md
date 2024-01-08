<br />
<div align="center">
  <h3 align="center">LCD-data-getter software</h3>

  <p align="center">
    Simple software to comunicate with your software, request time, date and weather forecast.
    This repository only works with the LCD-data-getter, <a href="https://github.com/alessandro-ooo/LCD-data-getter">you can find it here.</a>
    <br />
    <br />
    <br />
  </p>
</div>

## About The Project

<a href="https://youtube.com/shorts/mDV9INZrdto?feature=share">View Demo</a>

There are a lot of modern digital clocks available on the internet or in physical store, even good-looking ones. Though I've decided to create this software to comunicate with my arduino board and learn-by-doing how everything works with embedd softwares.
This software is by no means complete AND/OR indicated for professional use, it has to be considered as amateur project, hobbist software.

## How does everything work?

Basically, when the board is connected through USB to the computer, it "awaits" for data. It means that the arduino board sends (through serial communication) "<weather>" string to the software, the software "reads" and gets the weather data through ```LAT``` and ```LOG``` of your location, which it would be hard coded in the software.
The weather forecast is gathered through an API call to <a href="https://openweathermap.org/">https://openweathermap.org/</a> every ten minutes using the <a href="https://curl.se/">CURL library</a>. Once the weather data is stored in Arduino, the board will keep communicating to the software "<time>" string every second and will receive time and date to display on the LCD. It'll be possible to display the weather pressing a button.

## Docs
# CPPCOMM
```cpp
void CPPCOMM(String message)
```
Sends ```message``` to the software.
example:
```cpp
void CPPCOMM(String "<weather>")
```

# LCDWrite
```cpp
void LCDWrite(String text, int line, bool clear = false)
```
Writes text on the LCD.
example:
```cpp
LCDWrite("Hello World", 0, false);
LCDWrite("I'm on the second row!", 1, false);
LCDWrite("Now wipe them all!", 0, true);
```

# refreshWeather
```cpp
bool refreshWeather()
```
Refresh weather data every ten minutes as indicated by <a href="https://openweathermap.org/">https://openweathermap.org/</a>

# retrieveData
```cpp
bool retrieveData()
```
Asks for time and date to the software and formats it to print two strings on the LCD.
