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

## See Connections.txt for more info
