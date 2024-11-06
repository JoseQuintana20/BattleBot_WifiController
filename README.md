# Karonte BattleBot Control with ESP32

This repository contains the source code for **Karonte**, a BattleBot controlled in real-time via a responsive web interface hosted on an ESP32. The robot uses an H-bridge (**L298N**) for motor control and allows you to activate or deactivate a weapon through a relay from the same interface. The relay used is a single-module, inverse logic (active-low) relay.

## Features

- **Real-time Control via Web Page:** Control the robot from any device with a web browser, thanks to a responsive web interface.
- **Responsive Web Interface:** The design adapts to mobile and desktop devices, making it easy to control from smartphones, tablets, or computers.
- **Weapon Activation:** Control a weapon mechanism using a relay module directly from the web interface.
- **Simple Setup:** Code developed in Arduino IDE with support for ESP32, using the **DOIT ESP32 DEVKIT V1** board.

## Hardware Requirements

- **ESP32** (recommended **DOIT ESP32 DEVKIT V1**)
- **L298N H-bridge Module**
- **Motors** compatible with L298N
- **Single-Module Relay** (inverse logic or active-low relay) used to activate a weapon
- **Weapon Mechanism** controlled by the relay
- **Indicator LED** (optional)
- **Cables** and additional components as specified in the code pins

## Environment Setup

1. **Install Arduino IDE:** If you don't have it yet, download it from the [official Arduino website](https://www.arduino.cc/en/software).

2. **Add ESP32 Support:**

   - Open Arduino IDE and go to `File` > `Preferences`.
   - In the "Additional Boards Manager URLs" field, add the following URL:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Go to `Tools` > `Board` > `Boards Manager`.
   - Search for `esp32` and install **esp32 by Espressif Systems**.

3. **Select the Correct Board:**

   - Go to `Tools` > `Board` and select **DOIT ESP32 DEVKIT V1**.

## Hardware Connection

Connect the components according to the following pins specified in the code:

- **Left Motors:**
  - `LEFT_ENA` (GPIO 13)
  - `LEFT_IN1` (GPIO 26)
  - `LEFT_IN2` (GPIO 14)
- **Right Motors:**
  - `RIGHT_ENA` (GPIO 33)
  - `RIGHT_IN1` (GPIO 23)
  - `RIGHT_IN2` (GPIO 21)
- **Relay (Weapon Activation):**
  - `RELAY_PIN` (GPIO 18)
  - Connect the control signal (IN) of the relay module to GPIO 18
  - **Note:** Use an active-low relay module (relay is activated when the control signal is LOW)
- **Weapon Mechanism:**
  - Connect the weapon mechanism to the relay module's output terminals
- **Indicator LED (optional):**
  - `LED_INDICATOR` (GPIO 2)

## Using the Code

1. **Download or Clone the Repository:**

   ```bash
   git clone https://github.com/your_username/Karonte-BattleBot-ESP32-Control.git

