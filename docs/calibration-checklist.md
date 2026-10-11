# Calibration Checklist

1. Confirm the exact ACS712 module variant from its label/datasheet.
2. Use a safe, isolated test setup and qualified supervision for any mains-side equipment.
3. Confirm the sensor analog output remains inside the ESP32 ADC's allowed voltage range.
4. Compare the ZMPT101B-derived voltage reading with a suitable true-RMS meter and adjust `VOLTAGE_CALIBRATION_FACTOR`.
5. Compare ACS712 current readings with an appropriate reference and confirm `ACS712_SENSITIVITY_V_PER_A`.
6. Confirm relay polarity with the load disconnected before testing.
7. Record reference readings, measured readings, calibration factors, and test conditions.
8. Do not use this prototype for billing, protection, or safety-critical decisions.
