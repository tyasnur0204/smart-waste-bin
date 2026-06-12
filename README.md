# Automated 3-Category Waste Sorting Bin Prototype

An automated, smart waste management prototype powered by the **Arduino Uno** architecture. This system intelligently detects, classifies, and sorts waste into three distinct categories: **Metal**, **Wet (Organic)**, and **Dry (Inorganic)** using inductive proximity routing and moisture analytics.

## 🚀 Features
- **Automated 3-Way Classification:** Seamlessly routes garbage into Metal, Wet, or Dry compartments.
- **Real-Time Sensor Integration:** Employs high-precision sensors for instantaneous material identification.
- **Dual-Servo Mechanism:** Responsive mechanical actuation using dual servo motors for precise sorting gates and platform positioning.

## 🛠️ Hardware Components
- **Microcontroller:** Arduino Uno R3
- **Sensors:**
  - `LJ18A3-8-Z/BX` Inductive Proximity Sensor (Metal Detection)
  - Soil Moisture Sensor (Wet/Organic Waste Detection)
  - `HC-SR04` Ultrasonic Sensor (Optional: for automated lid opening)
- **Actuators:**
  - 2x Servo Motors (e.g., MG996R / SG90 for sorting and positioning)
- **Power Supply:** 12V/2A DC Power Source

## 📊 System Architecture & Workflow
1. **Detection Phase:** Waste is placed on the scanning platform. The system initiates the scanning sequence.
2. **Analysis Phase:**
   - **Metal Check:** The inductive proximity sensor tests for metallic properties. If triggered, the item is classified as **Metal**.
   - **Moisture Check:** If no metal is detected, the moisture sensor analyzes the water content. If the reading exceeds the predefined threshold, it is classified as **Wet**; otherwise, it is classified as **Dry**.
3. **Actuation Phase:** The dual-servo mechanism activates, tilting the platform or moving the guide rails to drop the waste into the designated internal compartment.

## 💻 Circuit Pin Configuration
| Component | Arduino Pin | Type | Description |
|---|---|---|---|
| LJ18A3 Proximity Sensor | D2 | Digital Input | Metal detection signal |
| Soil Moisture Sensor | A0 | Analog Input | Moisture level reading |
| Servo 1 (Base/Sorter) | D9 | PWM Output | Controls sorting angle |
| Servo 2 (Lid/Flap) | D10 | PWM Output | Controls sorting flap |

## 🔧 Installation & Setup
1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/tyasnur0204/smart-waste-bin
