#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 10
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {

  lcd.begin(16, 2);

  dht.begin();

  if (!bmp.begin()) {
	lcd.print("GREŠKA BMP180");
	while (1) {}
  }

  lcd.setCursor(0, 0);
  lcd.print("Vrijeme i");
  lcd.setCursor(0, 1);
  lcd.print("Relej Grijalice");
  delay(5000);
  lcd.clear();
}


void loop() 
{

  int vlaga=dht.readHumidity();
  int relej=8;
  int relejStanje = LOW;

  pinMode(relej, OUTPUT);

  //digitalWrite(relej, HIGH);

  int temp=bmp.readTemperature();

  if(temp<=19)
  {
    relejStanje = HIGH;
    digitalWrite(relej, HIGH);
  }

  else if(temp>=24)
  {
    relejStanje = LOW;
    digitalWrite(relej, LOW);
  }

  lcd.setCursor(0, 0);
  lcd.print("Unutra ");
	lcd.print(bmp.readTemperature());
  lcd.print(" C");
    lcd.setCursor(0, 1);

  if (relejStanje==HIGH)
  {
  lcd.print("Grijanje ON");
  }

  else if (relejStanje==LOW)
  {
    lcd.print("Grijanje OFF");
  }


  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Vani ");
  lcd.print(dht.readTemperature());
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Vlaga ");
  lcd.print(vlaga);
  lcd.print("%");

  delay(5000);
  lcd.clear();

}
