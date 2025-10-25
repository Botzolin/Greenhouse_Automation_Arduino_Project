# 🌱 Arduino Smart Irrigation System

This project is an **automatic plant watering system** built with an **Arduino UNO R4 WIFI**.  
It monitors **soil moisture**, **temperature**, **humidity**, and **light intensity**, and controls a **water pump** and **fan** automatically.  
An **OLED display** shows real-time sensor readings.

---

## 🧩 Components Used

- Arduino UNO R4 WIFI  
- DHT11 temperature & humidity sensor  
- Soil moisture sensor (analog module)  
- LDR (light sensor module)  
- OLED 0.96" I2C display (SSD1306)  
- Water pump + motor driver (L298N or L9110)  
- Small DC fan (optional)
- 220 Ohm Resistor
- Jumper wires & 5V power supply  

---

## ⚙️ Features

- Reads **soil humidity** and activates the **pump** when the soil is dry  
- Displays **temperature, air humidity, light, and soil moisture** on OLED  
- Turns on a **fan** automatically if the temperature exceeds a set threshold  
- Works with **Arduino Cloud IoT** for remote monitoring (optional)

---

## 🔌 Circuit Connections

**Soil Humidity Sensor (modul cu 4 pini: VCC, GND, A0, D0)**
- VCC → 5V
- GND → GND
- A0 → A0
- D0 → not connected

**DHT11 Sensor (Temperature and Humidity)**
- VCC → 5V
- GND → GND
- DATA → D2

**LDR Sensor Module**
- VCC → 5V
- GND → GND
- OUT → D3

**LED**
- VCC → 5V
- GND → GND (use a 220 Ohm resistor in series)

**Fan Module (5V)**
- INA → D5 (PWM)
- INB → D6 (PWM)
- VCC → 5V
- GND → GND

**Water Pump (usingH-Bridge L298N driver)**
- IN1 → D8
- IN2 → D7
- ENA → D9
- VCC → 5V
- GND → GND
- Motor Bridge → Pump 6V/GND (needs additional power supply)

**Display OLED I2C (SSD1306)**
- VCC → 5V
- GND → GND
- SDA → SDA (on arduino)
- SCL → SCL (on arduino)
