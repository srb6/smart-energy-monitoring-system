# Smart Energy Monitoring System

**Reconstructed documentation and starter firmware** for an ESP32-based IoT energy-monitoring and appliance-control project.

## Achievement
- **Reported award:** Second Prize
- **Reported prize money:** ₹1,000
- **Event:** 30-hour ECE Association hackathon

These achievement details were supplied by the project owner. Add event proof or photos if available.

## What is confirmed vs. what is still assumed

### Confirmed from the owner's recollection
- ESP32 controller
- ACS712 current sensor
- ZMPT101B voltage sensor
- Blynk dashboard
- Relay module
- Project concept included energy monitoring and remote appliance control

### Reconstructed / requires verification
- GPIO assignments in the sample firmware
- ACS712 module rating (sample assumes 20 A, 100 mV/A)
- Voltage calibration factor
- Relay active-LOW behavior
- Exact Blynk datastream configuration
- Gesture control, Vacation Mode, and theft detection implementation
- Accuracy of energy measurements

The original source files were unavailable when this repository was prepared. The firmware is a starting point, not a recovered copy of the original implementation.

## Hardware list
- ESP32 development board
- ACS712 current sensor module (confirm 5 A / 20 A / 30 A variant)
- ZMPT101B voltage sensor module
- Relay module compatible with the chosen ESP32 logic interface
- Appropriate isolated, rated power supply and protected enclosure
- Test load and suitable reference instruments for calibration

## Software
- Arduino IDE
- ESP32 board support package
- Blynk IoT library
- `BlynkSimpleEsp32` library

## Starter wiring (GPIO choices are assumptions)
| Module signal | ESP32 pin | Notes |
|---|---:|---|
| ACS712 analog output | GPIO34 | ADC1 input-only; ensure output stays within ESP32's allowed input range |
| ZMPT101B analog output | GPIO35 | ADC1 input-only; ensure output stays within ESP32's allowed input range |
| Relay input | GPIO26 | Confirm relay logic and driver compatibility |
| Sensor grounds | ESP32 GND | Only for low-voltage isolated sensor outputs; follow module documentation |

**Do not connect mains wiring to the ESP32.** The ZMPT101B board may involve hazardous mains-side terminals. Use appropriate isolation, enclosures, fusing, clearances, and qualified supervision.

## Blynk datastreams used by the sample
Create these Virtual Pin datastreams in the Blynk template:
- **V0**: voltage (Double)
- **V1**: current (Double)
- **V2**: apparent power (Double, VA)
- **V3**: estimated accumulated apparent energy (Double, VAh)
- **V4**: relay control (Integer 0/1, switch widget)

The code sends apparent power and a VAh estimate. It does **not** calculate certified real power or billing-grade kWh. True active power requires properly synchronized voltage/current sampling, calibration, and power-factor measurement.

## Setup
1. Install Arduino IDE and ESP32 board support.
2. Install the Blynk library.
3. Open `code/smart_energy_monitor.ino`.
4. Replace Blynk and Wi-Fi placeholders locally. Do not publish credentials.
5. Confirm your exact sensor module variants, relay polarity, and wiring before powering the system.
6. Calibrate the voltage factor and current sensitivity against appropriate reference instruments using a safe test setup.
7. Open Serial Monitor at 115200 baud.
8. Configure Blynk Virtual Pin datastreams V0–V4 and matching widgets.
9. Test only under qualified supervision and with a properly isolated, protected setup.

## Calibration checklist
- [ ] Confirm the ACS712 variant and sensitivity from its datasheet/module label.
- [ ] Confirm the ZMPT101B output range never exceeds the ESP32 ADC input range.
- [ ] Calibrate voltage against a suitable true-RMS meter.
- [ ] Calibrate current against a suitable current reference at a known safe load.
- [ ] Confirm relay ON/OFF polarity with the load disconnected first.
- [ ] Validate readings over multiple loads; do not use this as a certified meter.

## Repository structure
```text
smart-energy-monitoring-system/
├── README.md
├── .gitignore
├── code/
│   ├── smart_energy_monitor.ino
│   └── secrets.example.h
├── circuit/
├── images/
└── docs/
```

## Safety
Mains electricity can cause fatal electric shock or fire. Never connect mains directly to ESP32 pins or a solderless breadboard. Do not handle exposed mains terminals while powered. Use correctly rated isolated modules, enclosure, fuse/protection, and qualified supervision. This prototype is educational and is not a certified energy meter or safety device.

## License
No license selected. Choose one only after deciding how others may reuse the work.
