# Literature Review Notes

## Themes Covered

### 1. ANS Biology
- Physiological basis for stress and cognitive load signals
- Autonomic nervous system (sympathetic vs. parasympathetic branches)
- Stress activates sympathetic branch → triggers EDA, HRV, skin temp changes

### 2. EDA / GSR Effectiveness
- GSR is the highest-weighted sensor in the CLI
- Electrodermal activity reflects sympathetic nervous system arousal
- Well-validated for cognitive load and stress detection
- Signal quality adequate at wrist placement with gel/dry electrodes

### 3. HRV Effectiveness
- HRV is the second-highest-weighted sensor
- PPG-derived HRV (wrist) correlates well with ECG-derived HRV
- RMSSD is the recommended time-domain HRV metric for short-term windows
- Reduced HRV indicates higher sympathetic activity (stress/load)

### 4. Skin Temperature
- Peripheral vasoconstriction during stress reduces skin temperature
- Wrist skin temp is a reliable proxy for peripheral vascular tone
- Slower response than EDA — better for sustained load detection
- MLX90614 non-contact IR sensor is suitable for wristband integration

### 5. Accelerometer / Motion
- Fidgeting (repetitive hand/wrist movement) correlates with cognitive overload
- MPU6050 captures micro-movements not visible to the eye
- Lowest weight sensor but adds behavioral signal orthogonal to physiological ones

### 6. Sensor Placement
- **Wrist** — convenient, acceptable signal quality across all four sensors
- **Finger** — better EDA and PPG quality, but impractical for wearables
- **Chest** — best ECG/HRV, impractical for wristband form factor
- **Justification**: multi-sensor fusion at the wrist compensates for individual signal quality limitations

### 7. Existing Wristbands
- **Empatica E4** — gold standard research wristband; EDA, PPG, temp, accel
- **Fitbit Sense** — consumer grade; EDA sensor added in 2020
- These establish precedent for wrist-based multimodal cognitive/stress sensing

### 8. Multi-Sensor Fusion Approaches
- Early fusion (raw signal level) vs. late fusion (feature/decision level)
- Weighted linear fusion is interpretable and validated for wristband CLIs
- Machine learning approaches (SVM, RF) also common but require labeled data

### 9. Sensor Weighting
- Empirical weight ranges sourced from literature meta-analysis
- EDA consistently ranks highest across studies
- HRV ranks second; skin temp and accel fill out the fusion

---

## Key Source

**Nature 2024 Open Dataset Paper**
- Confirmed sampling rates: EDA 4 Hz, Skin Temp 4 Hz, PPG 64 Hz, Accel 32 Hz
- Multi-sensor wristband design parameters validated
- Open access dataset available for algorithm development and testing
