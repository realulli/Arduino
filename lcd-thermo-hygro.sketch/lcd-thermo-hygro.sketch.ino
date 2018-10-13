/*
  
Digital Air quality

This sketch is based on the examples from the libraries:

* LiquidCrystal

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
//#include <SimpleDHT.h>
#include <DHT.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTPIN 6     // what digital pin we're connected to

DHT dht(DHTPIN, DHTTYPE);

byte tOld=0;
byte humOld=0;
char dataPool[10][16] = {
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  ""
};


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Temp.   Humid.");
  Serial.begin(115200);
}

void updateDisplay(int sLine) {
  char* one={dataPool[sLine]};
  char* two={dataPool[sLine+1]};
  lcd.setCursor(0,0);
  lcd.print(one);
  lcd.setCursor(0,1);
  lcd.print(two);
}

void loop() {
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  Serial.println("=================================");
  Serial.println("Sample DHT11...");

  int err = SimpleDHTErrSuccess;
  if ((err = dht.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");

/*  
  dht.read(pinDHT11, &temperature, &humidity, NULL);
  if ((tOld != temperature) || (humOld != humidity)) {
    updateDisplay("Temp(C) : "+(int)temperature,"Humidity: "+(int)humidity);
    tOld=temperature;
    humOld=humidity;
    return;
  }
  */
  delay(10000);
}
