# 🧠 Cognitive Overload Wristband

A non-invasive wearable wristband that detects cognitive overload in real time using multimodal physiological sensing, centered on an ESP32 microcontroller.

---

## 📌 Project Overview

This project fuses signals from four physiological sensors to compute a **Cognitive Load Index (CLI)** — a real-time score that classifies the wearer's mental state into four levels:

| Level | State       | Feedback                  |
|-------|-------------|---------------------------|
| 0     | Calm        | Green LED                 |
| 1     | Elevated    | Yellow LED                |
| 2     | High Load   | Orange LED + soft vibration |
| 3     | Overload    | Red LED + strong vibration |

---

## 🔧 Hardware Stack

| Component        | Sensor / Module     | Purpose                        |
|------------------|---------------------|--------------------------------|
| Microcontroller  | ESP32               | Processing & wireless          |
| EDA/GSR          | Grove GSR Sensor    | Electrodermal activity         |
| PPG              | MAX30102            | Heart rate variability (HRV)   |
| Skin Temperature | MLX90614            | Peripheral skin temperature    |
| IMU              | MPU6050             | Motion / fidgeting detection   |

---

## 🧮 Algorithm Pipeline

```
Startup (2–3 min baseline calibration)
        ↓
Raw sensor readings (at respective sampling rates)
        ↓
Z-score normalization (against personal baseline)
        ↓
Weighted CLI fusion
        ↓
State classification (0–3)
        ↓
LED + vibration feedback
```

### Sensor Weights (from literature)

| Sensor           | Weight    |
|------------------|-----------|
| GSR / EDA        | 35–40%    |
| HRV (PPG-derived)| 30–35%    |
| Skin Temperature | 15–20%    |
| Accelerometer    | 10–15%    |

### Sampling Rates (Nature 2024 dataset)

| Sensor           | Rate   |
|------------------|--------|
| EDA              | 4 Hz   |
| Skin Temperature | 4 Hz   |
| PPG              | 64 Hz  |
| Accelerometer    | 32 Hz  |

---

## 📁 Repository Structure

```
cognitive-overload-wristband/
├── README.md
├── .gitignore
├── hardware/
│   ├── spec_sheet.md        ← Sensor specs, pin mappings, power
│   └── bom.md               ← Bill of materials
├── firmware/
│   └── main/
│       └── main.ino         ← ESP32 Arduino sketch
├── algorithm/
│   └── cli_algorithm.md     ← CLI formula, weights, state thresholds
├── docs/
│   └── literature_notes.md  ← Literature review summary
└── references/
    └── papers.md            ← Cited sources with links
```

---

## 🔬 Sensor Placement Rationale

Wrist placement is justified not by any single sensor being optimal there, but by the **combined tradeoff argument**: each sensor performs adequately at the wrist, and multi-sensor fusion compensates for individual signal quality limitations.

---

## 📚 Literature Basis

Key themes reviewed:
- ANS biology & physiological basis of stress
- EDA effectiveness (highest-weight sensor validation)
- HRV via PPG (wrist-based validation)
- Skin temperature as peripheral vasoconstriction marker
- Accelerometer / fidgeting as behavioral load signal
- Wrist vs. finger vs. chest sensor placement tradeoffs
- Existing wristbands: Empatica E4, Fitbit, etc.
- Multi-sensor fusion approaches
- **Nature 2024 open dataset paper** — confirmed sampling rates

---

## 🚧 Status

- [x] Hardware stack defined
- [x] Algorithm design confirmed
- [x] Sensor weights and sampling rates locked
- [x] Literature reviewed
- [ ] Firmware implementation
- [ ] PCB schematic
- [ ] Prototype testing
- [ ] Validation study
