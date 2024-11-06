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

2. **Open the File in Arduino IDE:**

   Navigate to the repository folder and open `Karonte_BattleBot_Control.ino` in Arduino IDE.

3. **Configure Wi-Fi Parameters (optional):**

   The ESP32 is set up as an access point with SSID `Karonte` and password `123456789`.

   You can modify these credentials in the following lines of the code:

   ```cpp
   const char* ssid = "Karonte";
   const char* password = "123456789";

4. **Compile and Upload the Code to the ESP32:**

   - Connect your ESP32 to the computer via a USB cable.
   . In Arduino IDE, select the appropriate port under Tools > Port.
   - Click the Upload button (rightward arrow) to compile and upload the code.
  
5. **Connecting and Controlling the BattleBot:**

   - Power on the ESP32 and wait for the WiFi access point to start.
   - Connect your device (smartphone, tablet, PC) to the WiFi network Karonte using the password 123456789.
   - Open a web browser and go to the IP address 192.168.4.1 (the default IP for the access point).
   - Use the responsive web interface to control the BattleBot in real-time.
  
## Using the Code

   **Movement Controls:**
   
      - **Forward, Backward, Left, Right:** Buttons arranged in a cross layout for intuitive control.
      - **Stop:** The robot stops when any movement button is released.
      - 
   **Weapon Activation (Relay Control):**
   
      - **ON/OFF Switch:** Allows activation or deactivation of the weapon via the relay connected to the ESP32.
      - **isual Indicator:** The switch changes color to indicate the state (green for deactivated, red for activated).
      - **Active-Low Relay Note:** Since the relay is active-low, turning the switch ON will deactivate the weapon, and turning it OFF will activate it. The web interface accounts for this logic inversion.

### Customizing the Code

#### Adjusting Speeds:

You can modify the PWM value to control motor speed by changing the value in `analogWrite()`.

#### Modifying the Interface:

The HTML page and CSS styling are located in the code under the client response generation section. You can customize the web interface to your liking.

#### Relay Logic Adjustment:

If you're using a different type of relay (e.g., active-high), you may need to adjust the relay control logic in the code. Currently, the code is set up for an active-low relay.
   ```cpp
   // Relay control
   if (request.indexOf("/relay_on") != -1) {
     digitalWrite(RELAY_PIN, LOW);  // Activate the relay (active-low)
   }
   if (request.indexOf("/relay_off") != -1) {
     digitalWrite(RELAY_PIN, HIGH); // Deactivate the relay (active-low)
   }
   ```

### Additional Notes

#### Active-Low Relay Behavior:

The relay module used is an inverse logic (active-low) relay, meaning it is activated when the control signal is **LOW** (0V) and deactivated when the control signal is **HIGH** (3.3V). Keep this in mind when connecting your weapon mechanism and interpreting the relay's behavior.

#### Safety Precautions:

- Ensure all connections are secure and correct before powering the system.
- Be cautious when operating the weapon mechanism to prevent injuries or damage.

#### Security:

Operating in access point mode, the control is local and does not require an internet connection, minimizing security risks.

#### Compatibility:

Ensure that the motors, the H-bridge, and the relay module are compatible in terms of voltage and current.

### Troubleshooting

#### Connection Issues:

If you can't connect to the access point, verify that the ESP32 is properly powered and that the code has been uploaded without errors.

#### Motors Not Responding:

- Check the connections between the ESP32 and the H-bridge.
- Make sure the power supply for the motors is adequate.

#### Relay Not Activating the Weapon:

- Verify that the relay module is connected correctly to the ESP32.
- Ensure that the weapon mechanism is properly connected to the relay's output terminals.
- Check that the relay module is compatible with the ESP32's voltage levels.

### License

This project is distributed under the MIT License. See the [LICENSE](LICENSE) file for more details.

### Credits

Developed by Jose Quintana.
