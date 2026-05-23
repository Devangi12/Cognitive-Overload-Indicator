# Hardware Specification Sheet

## Microcontroller

| Parameter     | Value                          |
|---------------|--------------------------------|
| Module        | ESP32 (e.g. ESP32-WROOM-32)    |
| CPU           | Dual-core Xtensa LX6, 240 MHz  |
| RAM           | 520 KB SRAM                    |
| Flash         | 4 MB                           |
| Wireless      | Wi-Fi 802.11 b/g/n, BLE 4.2    |
| ADC           | 12-bit, multiple channels      |
| Operating V   | 3.3V logic                     |

---

## Sensors

### 1. GSR / EDA Sensor (Grove GSR or equivalent)
| Parameter       | Value              |
|-----------------|--------------------|
| Output          | Analog voltage     |
| Sampling Rate   | 4 Hz               |
| ESP32 Pin       | GPIO34 (ADC1_CH6)  |
| Supply Voltage  | 3.3V / 5V          |
| Notes           | Measures skin conductance via two finger/wrist electrodes |

---

### 2. PPG Sensor — MAX30102
| Parameter       | Value              |
|-----------------|--------------------|
| Interface       | I2C                |
| I2C Address     | 0x57               |
| Sampling Rate   | 64 Hz              |
| ESP32 SDA Pin   | GPIO21             |
| ESP32 SCL Pin   | GPIO22             |
| Supply Voltage  | 1.8V / 3.3V        |
| Notes           | Red + IR LEDs for SpO2 and HR; HRV derived from IBI |

---

### 3. Skin Temperature — MLX90614
| Parameter       | Value              |
|-----------------|--------------------|
| Interface       | I2C                |
| I2C Address     | 0x5A (default)     |
| Sampling Rate   | 4 Hz               |
| ESP32 SDA Pin   | GPIO21 (shared)    |
| ESP32 SCL Pin   | GPIO22 (shared)    |
| Supply Voltage  | 3.3V / 5V          |
| Accuracy        | ±0.5°C             |
| Notes           | Non-contact IR; measures peripheral skin temp |

---

### 4. IMU — MPU6050
| Parameter       | Value              |
|-----------------|--------------------|
| Interface       | I2C                |
| I2C Address     | 0x68 (AD0 low)     |
| Sampling Rate   | 32 Hz              |
| ESP32 SDA Pin   | GPIO21 (shared)    |
| ESP32 SCL Pin   | GPIO22 (shared)    |
| Supply Voltage  | 3.3V               |
| Notes           | 3-axis accel + gyro; used for fidgeting/motion detection |

---

## Pin Mapping Summary

| ESP32 Pin | Connected To         | Type    |
|-----------|----------------------|---------|
| GPIO21    | SDA (all I2C)        | I2C     |
| GPIO22    | SCL (all I2C)        | I2C     |
| GPIO34    | GSR Sensor (analog)  | ADC in  |
| GPIO25    | LED output           | Digital |
| GPIO26    | Vibration motor      | Digital |
| 3V3       | Sensor power rail    | Power   |
| GND       | Common ground        | Power   |

---

## Feedback Actuators

| Actuator        | Interface | ESP32 Pin | Notes                        |
|-----------------|-----------|-----------|------------------------------|
| RGB LED         | Digital   | GPIO25    | Common cathode; use PWM      |
| Vibration Motor | Digital   | GPIO26    | Use MOSFET driver (e.g. 2N7000) |

---

## Power

- Primary: LiPo 3.7V 500mAh (rechargeable)
- Regulator: AMS1117-3.3 for 3.3V rail
- Charging: TP4056 module (USB-C preferred)
- Estimated runtime: ~6–8 hours continuous sensing
