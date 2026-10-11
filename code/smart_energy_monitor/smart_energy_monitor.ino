/*
  Smart Energy Monitoring System — reconstructed starter firmware
  Board: ESP32
  Sensors: ACS712 current sensor + ZMPT101B voltage sensor
  Dashboard: Blynk IoT
  Relay: one-channel relay module

  IMPORTANT:
  - This is a reconstructed starter, NOT the original hackathon source code.
  - Calibrate the sensor factors against suitable reference instruments.
  - This prototype is not a certified electricity meter.
  - Mains voltage is lethal. Use only properly isolated, enclosed, rated modules
    and qualified supervision. Never connect mains directly to ESP32 pins.
*/

#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Energy Monitoring"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <math.h>

// Replace these before compiling. Keep real credentials out of public GitHub.
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// ESP32 ADC1 pins are used to avoid ADC2/Wi-Fi conflicts.
constexpr int PIN_CURRENT = 34; // ADC1 input-only
constexpr int PIN_VOLTAGE = 35; // ADC1 input-only
constexpr int PIN_RELAY   = 26; // digital output

// Set to true for many active-LOW relay boards; verify your module.
constexpr bool RELAY_ACTIVE_LOW = true;

// Calibration settings — these MUST be calibrated for your exact hardware.
// ACS712 sensitivities at its sensor output (typical nominal values):
// 5A module: 0.185 V/A; 20A: 0.100 V/A; 30A: 0.066 V/A.
// If using a different module, set the matching value.
constexpr float ACS712_SENSITIVITY_V_PER_A = 0.100f; // ASSUMES ACS712-20A

// ADC conversion approximation. Calibrate against the actual board if needed.
constexpr float ADC_VOLTS_PER_COUNT = 3.3f / 4095.0f;

// Set this after measuring the ZMPT101B output with a safe, isolated setup.
// It means: actual mains Vrms / measured sensor-output Vrms.
// 1.0 is only a placeholder and will NOT usually give correct mains voltage.
constexpr float VOLTAGE_CALIBRATION_FACTOR = 1.0f; // PLACEHOLDER — calibrate

constexpr int SAMPLE_COUNT = 1200;
constexpr uint32_t REPORT_INTERVAL_MS = 1000;

BlynkTimer timer;
bool relayOn = false;
float voltageRms = 0.0f;
float currentRms = 0.0f;
float apparentPowerVA = 0.0f;
float energyWh = 0.0f;
uint32_t lastEnergyUpdateMs = 0;

void applyRelay(bool on) {
  relayOn = on;
  const int activeLevel = RELAY_ACTIVE_LOW ? LOW : HIGH;
  const int inactiveLevel = RELAY_ACTIVE_LOW ? HIGH : LOW;
  digitalWrite(PIN_RELAY, on ? activeLevel : inactiveLevel);
  Blynk.virtualWrite(V4, on ? 1 : 0);
}

BLYNK_WRITE(V4) {
  // Blynk switch widget: Datastream V4, integer 0/1.
  applyRelay(param.asInt() == 1);
}

void measureSensors() {
  // Collect samples and calculate each channel's AC RMS around its own mean.
  // Sequential sampling is approximate; this does not calculate true real power
  // or power factor. Use an appropriate meter for safety-critical measurements.
  double sumV = 0.0, sumV2 = 0.0;
  double sumI = 0.0, sumI2 = 0.0;

  for (int n = 0; n < SAMPLE_COUNT; n++) {
    const float vCount = (float)analogRead(PIN_VOLTAGE);
    const float iCount = (float)analogRead(PIN_CURRENT);
    sumV += vCount;
    sumV2 += (double)vCount * vCount;
    sumI += iCount;
    sumI2 += (double)iCount * iCount;
    delayMicroseconds(250);
  }

  const double meanV = sumV / SAMPLE_COUNT;
  const double meanI = sumI / SAMPLE_COUNT;
  const double varianceV = fmax(0.0, (sumV2 / SAMPLE_COUNT) - meanV * meanV);
  const double varianceI = fmax(0.0, (sumI2 / SAMPLE_COUNT) - meanI * meanI);

  const float sensorVrms = sqrt(varianceV) * ADC_VOLTS_PER_COUNT;
  const float sensorIrms = sqrt(varianceI) * ADC_VOLTS_PER_COUNT;

  voltageRms = sensorVrms * VOLTAGE_CALIBRATION_FACTOR;
  currentRms = sensorIrms / ACS712_SENSITIVITY_V_PER_A;

  // Apparent power only. Real power needs synchronized v(t)*i(t) sampling
  // and suitable calibration; this estimate assumes no power-factor correction.
  apparentPowerVA = voltageRms * currentRms;

  const uint32_t now = millis();
  if (lastEnergyUpdateMs != 0) {
    const float elapsedHours = (now - lastEnergyUpdateMs) / 3600000.0f;
    // VA-hours estimate, not certified active energy in Wh.
    energyWh += apparentPowerVA * elapsedHours;
  }
  lastEnergyUpdateMs = now;

  if (Blynk.connected()) {
    Blynk.virtualWrite(V0, voltageRms);
    Blynk.virtualWrite(V1, currentRms);
    Blynk.virtualWrite(V2, apparentPowerVA);
    Blynk.virtualWrite(V3, energyWh);
  }

  Serial.printf("Vrms=%.2f V | Irms=%.3f A | Apparent power=%.2f VA | Estimated energy=%.4f VAh | Relay=%s\n",
                voltageRms, currentRms, apparentPowerVA, energyWh, relayOn ? "ON" : "OFF");
}

void setup() {
  Serial.begin(115200);

  pinMode(PIN_RELAY, OUTPUT);
  // Set relay OFF immediately at boot.
  digitalWrite(PIN_RELAY, RELAY_ACTIVE_LOW ? HIGH : LOW);

  analogReadResolution(12);
  analogSetPinAttenuation(PIN_CURRENT, ADC_11db);
  analogSetPinAttenuation(PIN_VOLTAGE, ADC_11db);

  WiFi.mode(WIFI_STA);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  lastEnergyUpdateMs = millis();
  timer.setInterval(REPORT_INTERVAL_MS, measureSensors);
}

void loop() {
  Blynk.run();
  timer.run();
}
