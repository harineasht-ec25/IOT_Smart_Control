🚀 ESP32 RelayVerse ⚡

Smart IoT Relay Automation using ESP32 • HiveMQ • MQTT • Web Dashboard

> 🌍 Control electrical devices from anywhere in the world using ESP32 and MQTT-powered cloud communication.




---

⚡ Overview

RelayVerse is a smart IoT-based relay automation system powered by ESP32 and HiveMQ MQTT cloud integration. The system enables real-time remote switching of multiple relays through a modern web dashboard accessible from any network globally.

Designed for:

🏠 Home Automation

🌾 Smart Agriculture

🏭 Industrial Automation

⚙ Remote Switching Systems

🌐 IoT Experiments & Learning



---

🔥 Features

✨ WiFi provisioning through captive portal
✨ Remote relay control from anywhere 🌍
✨ HiveMQ MQTT cloud communication ☁️
✨ Responsive web dashboard 💻
✨ Real-time relay toggle control ⚡
✨ Automatic WiFi reconnection 🔄
✨ Built-in WiFi status LED 💡
✨ 4-channel relay support
✨ Mobile-friendly control interface 📱


---

📡 System Workflow

ESP32 Hotspot
      ↓
WiFi Configuration Portal
      ↓
ESP32 Connects to Internet
      ↓
HiveMQ MQTT Broker
      ↓
Web Dashboard Sends Commands
      ↓
ESP32 Receives MQTT Messages
      ↓
Relay ON/OFF Control


---

🛠 Hardware Used

Component	Quantity

ESP32 Development Board	1
4-Channel Relay Module	1
Jumper Wires	As required
5V Power Supply	1



---

🔌 Relay Connections

Relay	ESP32 GPIO

Relay 1	GPIO 18
Relay 2	GPIO 19
Relay 3	GPIO 21
Relay 4	GPIO 22



---

☁️ MQTT Configuration

MQTT Broker

broker.hivemq.com

MQTT Topic

home/relay


---

⚡ Supported MQTT Commands

Command	Action

R1ON	Relay 1 ON
R1OFF	Relay 1 OFF
R2ON	Relay 2 ON
R2OFF	Relay 2 OFF
R3ON	Relay 3 ON
R3OFF	Relay 3 OFF
R4ON	Relay 4 ON
R4OFF	Relay 4 OFF



---

💻 Web Dashboard Features

✅ Single-button relay toggle control
✅ Dynamic ON/OFF state indication 🔴🟢
✅ MQTT-based real-time communication 📡
✅ Responsive design for mobile & desktop 📱💻


---

📚 Libraries Used

WiFi.h
WebServer.h
Preferences.h
DNSServer.h
PubSubClient.h


---

🚀 Getting Started

1️⃣ Upload ESP32 Firmware

Install ESP32 Board Package

Install PubSubClient library

Upload firmware using Arduino IDE



---

2️⃣ Configure WiFi

Connect to hotspot:

SSID : ESP32_Setup
PASSWORD : 12345678

Open:

http://192.168.4.1

Enter WiFi credentials.


---

3️⃣ Open Web Dashboard

Host the dashboard using:

GitHub Pages

Netlify

Vercel


Access from:

Mobile 📱

Laptop 💻

Any Network 🌍



---

📸 Project Preview

/images/dashboard.png
/images/esp32_setup.png
/images/relay_module.png


---

🔥 Future Upgrades

🚀 Firebase Integration
🚀 Real-time Feedback System
🚀 OTA Firmware Updates
🚀 Alexa / Google Assistant Support
🚀 Sensor Monitoring Dashboard
🚀 Mobile App Integration


---

👨‍💻 Developed By

Harineash ⚡


---

⭐ Support The Project

If you found this project useful:

⭐ Star the repository
🍴 Fork the project
🚀 Build your own IoT automation system
