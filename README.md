# Smart Energy Monitoring System

An ESP32-based IoT project designed to monitor electrical energy consumption, enable remote appliance control, and support smarter energy management.

## 🏆 Hackathon Achievement

- **Event:** 30-Hour Hackathon
- **Achievement:** Second Prize
- **Prize Money:** ₹1,000

## 🎥 Project Demonstration

Watch the project demonstration on LinkedIn:

**[View Project Demo on LinkedIn](https://www.linkedin.com/posts/bomman_iot-smarthome-energymonitoring-ugcPost-7438919994337300480-W59v/?highlightedUpdateUrn=urn%3Ali%3Aactivity%3A7438920074901659648&highlightedUpdateType=SOCIAL_SHARE&origin=SOCIAL_SHARE&utm_source=social_share_send&utm_medium=android_app&rcm=ACoAAEi4jwgBphgBbfVAa4hYV59VTQ1KOZiFI7U&utm_campaign=copy_link)**

## 🚀 Features

- Real-time electrical parameter monitoring
- IoT-based monitoring through the Blynk dashboard
- Remote appliance control using a smartphone
- Gesture-based appliance control
- Vacation Mode for appliance management when occupants are away
- Theft detection functionality during Vacation Mode

*Note: Features should be verified against the actual prototype and implementation.*

## 🛠️ Hardware Components

- ESP32 development board
- ACS712 current sensor
- ZMPT101B voltage sensor
- Relay module
- Power supply and connecting wires
- Electrical load for testing

## 💻 Software and Technologies

- Embedded C/C++
- Arduino IDE
- ESP32
- Blynk IoT Platform
- Wi-Fi communication

## ⚙️ Working Principle

The ACS712 current sensor and ZMPT101B voltage sensor provide electrical measurements to the ESP32. The controller processes the sensor readings and communicates with the Blynk IoT platform over Wi-Fi.

Users can monitor the available measurements and control connected appliances remotely through the dashboard using a relay module.

## 🏗️ System Architecture

```text
ACS712 Current Sensor ──┐
                        ├──> ESP32
ZMPT101B Voltage Sensor ┘      │
                               │ Wi-Fi
                               ▼
                         Blynk Dashboard
                               │
                         Remote Control
                               │
                               ▼
                         Relay Module
                               │
                               ▼
                         Electrical Load
```

## 📂 Project Structure

```text
smart-energy-monitoring-system/
├── README.md
├── code/
│   └── smart_energy_monitor.ino
```

*Add the actual source code, circuit diagram, photographs, and report when available.*

## 🔮 Future Enhancements

- Energy consumption history and analytics
- Electricity bill estimation
- Energy-saving recommendations
- Improved dashboard visualization
- Enhanced appliance monitoring and automation

## ⚠️ Safety Notice

Mains electricity can cause fatal electric shock or fire. Use properly isolated, rated sensor modules and relay hardware, suitable protection, and an enclosed setup under qualified supervision. This educational prototype is not a certified energy meter.

## 📜 License

A license will be added when the intended terms for reuse and distribution are decided.

---

**Developed as an IoT-based energy monitoring and appliance management project.**
