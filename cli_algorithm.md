# Cognitive Load Index (CLI) Algorithm

## Overview

The CLI is a fused real-time score computed from four physiological signals. It classifies the wearer's cognitive state into one of four levels.

---

## Pipeline

```
1. Baseline Calibration (2–3 min at startup, relaxed state)
         ↓
2. Raw Sensor Readings (at respective sampling rates)
         ↓
3. Z-score Normalization (per sensor, against baseline mean/std)
         ↓
4. Weighted Fusion → CLI score
         ↓
5. State Classification (thresholds → Level 0–3)
         ↓
6. Feedback Output (LED color + vibration pattern)
```

---

## Step 1: Baseline Calibration

- Duration: 2–3 minutes
- User should be seated, relaxed
- During calibration, compute:
  - `mean_i` = mean of sensor i over calibration window
  - `std_i`  = standard deviation of sensor i over calibration window
- Store these as personal baseline parameters

---

## Step 2: Z-score Normalization

For each sensor reading `x_i` at time `t`:

```
z_i(t) = (x_i(t) - mean_i) / std_i
```

This normalizes each sensor to a common scale, accounting for individual physiological differences.

---

## Step 3: Weighted CLI Fusion

```
CLI(t) = w_GSR * z_GSR(t)
       + w_HRV * z_HRV(t)
       + w_TEMP * z_TEMP(t)
       + w_ACC * z_ACC(t)
```

### Sensor Weights (from literature)

| Sensor           | Symbol   | Weight (midpoint) |
|------------------|----------|-------------------|
| GSR / EDA        | w_GSR    | 0.375 (range: 0.35–0.40) |
| HRV (PPG)        | w_HRV    | 0.325 (range: 0.30–0.35) |
| Skin Temperature | w_TEMP   | 0.175 (range: 0.15–0.20) |
| Accelerometer    | w_ACC    | 0.125 (range: 0.10–0.15) |

> Weights must sum to 1.0

---

## Step 4: State Classification

| Level | State       | CLI Threshold | LED Color | Vibration         |
|-------|-------------|---------------|-----------|-------------------|
| 0     | Calm        | CLI < 1.0     | Green     | None              |
| 1     | Elevated    | 1.0 ≤ CLI < 2.0 | Yellow  | None              |
| 2     | High Load   | 2.0 ≤ CLI < 3.0 | Orange  | Short pulse       |
| 3     | Overload    | CLI ≥ 3.0     | Red       | Repeated pulses   |

> Thresholds are initial estimates — subject to tuning during validation.

---

## Sampling Rates (Nature 2024 dataset)

| Sensor           | Rate   | Notes                              |
|------------------|--------|------------------------------------|
| EDA              | 4 Hz   | 1 sample per 250ms                 |
| Skin Temperature | 4 Hz   | 1 sample per 250ms                 |
| PPG              | 64 Hz  | IBI extracted for HRV computation  |
| Accelerometer    | 32 Hz  | Magnitude: √(ax²+ay²+az²)          |

---

## HRV Computation from PPG

- Detect R-peaks (pulse peaks) in the PPG signal
- Compute Inter-Beat Intervals (IBI): time between consecutive peaks
- RMSSD = √( mean( (IBI[n+1] - IBI[n])² ) ) over a sliding window
- Higher RMSSD → lower stress; invert for z-score direction consistency

---

## Notes

- CLI is computed on a **sliding window** (e.g. 10–30 seconds) to smooth noise
- Hysteresis may be applied to prevent rapid state switching
- Weights can be tuned post-validation using labeled ground-truth data
