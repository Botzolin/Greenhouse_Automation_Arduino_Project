#include "thingProperties.h"
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// ————————————————————————————
// OLED
// ————————————————————————————
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ————————————————————————————
// Pini Senzori
// ————————————————————————————
#define DHTPIN_temp   2
#define LDR_PIN       3
#define LED_PIN       4
#define DHTTYPE_temp  DHT11
#define V_In1         5
#define V_In2         6
#define Pump_In1      8
#define Pump_In2      7
#define Pump_ena      9
#define SOIL_PIN      A0


// ————————————————————————————
// Config LDR / DHT
// ————————————————————————————
bool ldr_low_dark = false;
bool is_pump_on = false;

DHT dht(DHTPIN_temp, DHTTYPE_temp);

unsigned long lastRead = 0;
const unsigned long READ_INTERVAL_MS = 2000;

// ————————————————————————————
// setup()
// ————————————————————————————
void setup()
{
  // OLED
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    while (true);
  }

  // Fan
  pinMode(V_In1, OUTPUT);
  pinMode(V_In2, OUTPUT);
  analogWrite(V_In1, 0);
  analogWrite(V_In2, 0);

  //Pump
  pinMode(Pump_ena, OUTPUT);
  pinMode(Pump_In1, OUTPUT);
  pinMode(Pump_In2, OUTPUT);
  
  digitalWrite(Pump_In1, HIGH);
  digitalWrite(Pump_In2, LOW);
  analogWrite(Pump_ena, 0);  

  // DHT & LDR
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);

  // Soil sensor
  pinMode(SOIL_PIN, INPUT);

  // Arduino Cloud
  initProperties();
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
}

// ————————————————————————————
// loop()
// ————————————————————————————
void loop()
{
  ArduinoCloud.update();

  // ——— Senzor lumină (LDR)
  const int light = digitalRead(LDR_PIN);
  bool is_dark = ldr_low_dark ? (light == LOW) : (light == HIGH);
  ledState = is_dark;
  
  if (is_dark) 
  {
    digitalWrite(LED_PIN, HIGH);
  } 
  else 
  {
    digitalWrite(LED_PIN, LOW);
  }

  // ——— Senzor temperatură & umiditate + display
  unsigned long now = millis();
  if (now - lastRead >= READ_INTERVAL_MS) 
  {
    lastRead = now;

    float h = dht.readHumidity();
    float t = dht.readTemperature(); // Celsius

    temperature = t - 2;
    humidity    = h + 11;

    bool is_fan_on = false;
    if (temperature >= 29) 
    {
      is_fan_on = true;
      analogWrite(V_In1, 80);
      fanState = true;
    } 
    else 
    {
      is_fan_on = false;
      analogWrite(V_In1, 0);
      fanState = false;
    }
  // Pump activation
  int soilValue = analogRead(SOIL_PIN);
  soil_humidity = soilValue;
  if (soilValue > 700) 
  {
    is_pump_on = true;
    pumpState = is_pump_on;
    analogWrite(Pump_ena, 255);
    delay(5000);
  } 
  else 
  {
    is_pump_on = false;
    pumpState = is_pump_on;
    analogWrite(Pump_ena, 0);
  }

  delay(2000); // citește la fiecare 2 secunde
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    display.print(F("Temperature: "));
    display.print(temperature, 1);
    display.println(" C");

    display.print(F("Humidity: "));
    display.print(humidity, 1);
    display.println(" %");

    display.print(F("Soil Humidity: "));
    display.println(soilValue, 1);

    display.print(F("Lights: "));
    if (is_dark) 
    {
      display.println(F("ON"));
    } 
    else 
    {
      display.println(F("OFF"));
    }

    display.print(F("Fan: "));
    if (is_fan_on) 
    {
      display.println(F("ON"));
    }
    else 
    {
      display.println(F("OFF"));
    }

    display.print(F("Pump: "));
    if (is_pump_on) 
    {
      display.println(F("ON"));
    } 
    else 
    {
      display.println(F("OFF"));
    }

    display.display();
  }
}
}
