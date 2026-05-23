/*
 * Cognitive Overload Wristband — ESP32 Firmware
 * ------------------------------------------------
 * Sensors:
 *   - GSR/EDA  → GPIO34 (analog)
 *   - MAX30102  → I2C (SDA: 21, SCL: 22)
 *   - MLX90614  → I2C (SDA: 21, SCL: 22)
 *   - MPU6050   → I2C (SDA: 21, SCL: 22)
 *
 * Feedback:
 *   - RGB LED   → GPIO25
 *   - Vibration → GPIO26
 *
 * Status: SCAFFOLD — sensor reads and CLI logic to be implemented
 */

#include <Wire.h>
// TODO: Add sensor libraries
// #include "MAX30105.h"
// #include <Adafruit_MLX90614.h>
// #include <MPU6050.h>

// ─── Pin Definitions ────────────────────────────────────────────
#define GSR_PIN       34
#define LED_PIN       25
#define VIBRATION_PIN 26

// ─── Sampling Rates (Hz) ────────────────────────────────────────
#define EDA_SAMPLE_RATE    4
#define TEMP_SAMPLE_RATE   4
#define PPG_SAMPLE_RATE    64
#define ACCEL_SAMPLE_RATE  32

// ─── Sensor Weights ─────────────────────────────────────────────
const float W_GSR  = 0.375;
const float W_HRV  = 0.325;
const float W_TEMP = 0.175;
const float W_ACC  = 0.125;

// ─── Baseline Calibration ───────────────────────────────────────
#define BASELINE_DURATION_MS  (2 * 60 * 1000)  // 2 minutes

float baseline_mean_gsr  = 0, baseline_std_gsr  = 1;
float baseline_mean_hrv  = 0, baseline_std_hrv  = 1;
float baseline_mean_temp = 0, baseline_std_temp = 1;
float baseline_mean_acc  = 0, baseline_std_acc  = 1;

// ─── CLI State Thresholds ───────────────────────────────────────
// Level 0: Calm        CLI < 1.0
// Level 1: Elevated    1.0 <= CLI < 2.0
// Level 2: High Load   2.0 <= CLI < 3.0
// Level 3: Overload    CLI >= 3.0

// ─── Setup ──────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  Wire.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(VIBRATION_PIN, OUTPUT);
  pinMode(GSR_PIN, INPUT);

  Serial.println("Cognitive Overload Wristband — Initializing...");

  // TODO: Initialize sensors
  // initMAX30102();
  // initMLX90614();
  // initMPU6050();

  Serial.println("Starting baseline calibration (2 min)...");
  runBaselineCalibration();
  Serial.println("Calibration complete. Monitoring started.");
}

// ─── Main Loop ──────────────────────────────────────────────────
void loop() {
  // Read sensors
  float gsr_raw  = readGSR();
  float hrv_raw  = readHRV();      // RMSSD from PPG
  float temp_raw = readSkinTemp();
  float acc_raw  = readAccel();    // Acceleration magnitude

  // Z-score normalization
  float z_gsr  = zScore(gsr_raw,  baseline_mean_gsr,  baseline_std_gsr);
  float z_hrv  = zScore(hrv_raw,  baseline_mean_hrv,  baseline_std_hrv);
  float z_temp = zScore(temp_raw, baseline_mean_temp, baseline_std_temp);
  float z_acc  = zScore(acc_raw,  baseline_mean_acc,  baseline_std_acc);

  // Weighted CLI
  float cli = (W_GSR  * z_gsr)
            + (W_HRV  * z_hrv)
            + (W_TEMP * z_temp)
            + (W_ACC  * z_acc);

  // Classify state
  int state = classifyState(cli);

  // Output feedback
  setFeedback(state);

  // Debug output
  Serial.print("CLI: "); Serial.print(cli);
  Serial.print(" | State: "); Serial.println(state);

  delay(250); // ~4 Hz main loop
}

// ─── Sensor Read Functions (stubs) ──────────────────────────────
float readGSR() {
  // TODO: Read analog value from GSR sensor
  return analogRead(GSR_PIN);
}

float readHRV() {
  // TODO: Read PPG from MAX30102, extract IBI, compute RMSSD
  return 0.0;
}

float readSkinTemp() {
  // TODO: Read object temperature from MLX90614
  return 0.0;
}

float readAccel() {
  // TODO: Read XYZ from MPU6050, compute magnitude sqrt(ax^2+ay^2+az^2)
  return 0.0;
}

// ─── Baseline Calibration ───────────────────────────────────────
void runBaselineCalibration() {
  // TODO: Collect samples over BASELINE_DURATION_MS
  // Compute mean and std for each sensor
  // Store in baseline_mean_* and baseline_std_* variables
}

// ─── Z-score Normalization ──────────────────────────────────────
float zScore(float value, float mean, float std_dev) {
  if (std_dev == 0) return 0;
  return (value - mean) / std_dev;
}

// ─── State Classification ───────────────────────────────────────
int classifyState(float cli) {
  if (cli < 1.0) return 0;       // Calm
  else if (cli < 2.0) return 1;  // Elevated
  else if (cli < 3.0) return 2;  // High Load
  else return 3;                 // Overload
}

// ─── Feedback Output ────────────────────────────────────────────
void setFeedback(int state) {
  // TODO: Set RGB LED color based on state
  // TODO: Set vibration motor pattern based on state
  switch (state) {
    case 0: // Calm — Green LED, no vibration
      digitalWrite(VIBRATION_PIN, LOW);
      break;
    case 1: // Elevated — Yellow LED, no vibration
      digitalWrite(VIBRATION_PIN, LOW);
      break;
    case 2: // High Load — Orange LED, short pulse
      digitalWrite(VIBRATION_PIN, HIGH);
      delay(100);
      digitalWrite(VIBRATION_PIN, LOW);
      break;
    case 3: // Overload — Red LED, repeated pulses
      for (int i = 0; i < 3; i++) {
        digitalWrite(VIBRATION_PIN, HIGH);
        delay(150);
        digitalWrite(VIBRATION_PIN, LOW);
        delay(100);
      }
      break;
  }
}
