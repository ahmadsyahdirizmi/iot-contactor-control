# 🔧 IoT-Based Contactor Control System

## 🎯 System Purpose
The IoT-Based Contactor Control System is designed to provide remote control and monitoring capabilities for industrial contactor panels. The system enables:

1. Remote control of contactors through mobile application
2. Real-time monitoring of contactor status
3. Automated scheduling of contactor operations
4. Integration with existing control systems without modification

<p align="center">
  <img src="https://github.com/ahmadsyahdirizmi/iot-contactor-control/blob/1b29349e94e1202c5205bd0dc61fcf1152e4ce79/images/Rangkaian%20Sistem%20Kontrol%20Kontaktor.png" width="500" alt="Contactor Control System Circuit">
</p>
<p align="center">
  <em>Figure 1: Original Contactor Control System Circuit showing the base system for integration</em>
</p>

### 💡 Proposed Solution
To address the above requirements, the following solutions are implemented:

1. **Hardware:**
   - **Microcontroller:** ESP32 DevkitC V4, which supports Wi-Fi connectivity, controls relays to activate/deactivate the contactor, and supports external antennas for better Wi-Fi coverage.
   - **Sensors:** AC 220V voltage detectors to monitor contactor status.
2. **Relay Setup:**
   - Two relays (NO and NC) are used to control a single contactor, functioning like PB NO and PB NC on the panel.
   - The NC relay is connected in series with PB NC, and the NO relay is connected in parallel with PB NO.
3. **Mobile Application:**
   - Blynk Mobile App is used for IoT automation to schedule the contactor's operation.

### 🛠️ Components Used

Below are the hardware components used in the system
- ESP32 DevkitC V4
- Wi-Fi Antenna 5 dBi
- Base Plate
- 9V Adaptor
- Relay 3.3V 4 Channel
- Box Panel 75x120x200 mm
- Spacer + Nut 10mm x 3mm
- Female-to-Female Jumper Cable
- Single-core Cable 1.5mm (Black and Red)
- Perforated PCB
- 220V Voltage Detector
- Solder Tin
- Adhesive (Alteco)
- Terminal Block 8p and 4p
- RGB LED

## ⚙️ Hardware Workflow
<p align="center">
  <img src="https://github.com/ahmadsyahdirizmi/iot-contactor-control/blob/1b29349e94e1202c5205bd0dc61fcf1152e4ce79/images/Flowchart%20Cara%20Kerja%20Hardware.png" width="400" alt="Hardware Workflow Flowchart">
</p>
<p align="center">
  <em>Figure 1: Hardware System Workflow Diagram showing the operational sequence of the IoT Contactor Control System</em>
</p>

The workflow involves several processes, including:
1. Configuring the Wi-Fi connection.
2. Controlling relays to manage the contactor's status.
3. Monitoring the contactor's condition (on/off).

## 📝 Wiring Diagram
<p align="center">
  <img src="https://github.com/ahmadsyahdirizmi/iot-contactor-control/blob/1b29349e94e1202c5205bd0dc61fcf1152e4ce79/images/Wiring%20Diagram%20Alat.png" width="600" alt="System Wiring Diagram">
</p>
<p align="center">
  <em>Figure 2: Detailed Wiring Diagram showing connections between ESP32, relays, sensors, and other components</em>
</p>

### 🔌 Component Functions:
- **ESP32 DevkitC V4:** Central controller for the system.
- **Relay NO (NO1-4):** Acts as the start push button on the panel.
- **Relay NC (NC1-4):** Acts as the stop push button on the panel.
- **Sensors (1-4):** Detects voltage on the LED indicator to determine the contactor's status.
- **RGB LED:** Indicates the system's status:
  - 🔴 **Red:** System is powered but not connected to Wi-Fi or server.
  - 🔵 **Blue:** System is connected to Wi-Fi but not to the server.
  - 🟢 **Green:** System is connected to the server and operational.
  - ⚪ **White:** Wi-Fi Manager mode indicates the system cannot connect to the target Wi-Fi.

## ✨ Project Features

<p align="center">
  <img src="https://github.com/ahmadsyahdirizmi/iot-contactor-control/blob/d2a2def4588204ed5ccee3901bdf0465732898b9/images/Alat%20Dengan%20Enclosure.png" width="500" alt="Device with Enclosure">
</p>
<p align="center">
  <em>Figure 3: IoT Contactor Control Device with Enclosure</em>
</p>

1. **Control and Monitoring:**
   - The system can turn contactors on/off and monitor their status in real time.
2. **Automation:**
   - Automation via the Blynk app to schedule contactor operations.
3. **Hardware Design:**
   - Unit can control and monitor up to 4 contactors.
   - Uses a 5 dBi antenna for Wi-Fi connectivity.
   - RGB LEDs provide status indicators.

### 📱 Dashboard on Blynk Mobile

<p align="center">
  <img src="https://github.com/ahmadsyahdirizmi/iot-contactor-control/blob/bdafd5aeedc052477e14e77f806ebba7537feca5/images/Dashboard%20Aplikasi%20Blynk%20Mobile.jpg" width="300" alt="Blynk Mobile Dashboard">
</p>
<p align="center">
  <em>Figure 4: Blynk Mobile App Dashboard used to control and monitor the IoT-based contactor control system</em>
</p>

- **Communication Protocol:** MQTT with port 8883 for encrypted data communication.
- **Features:**
  - Buttons to control contactors (ON/OFF and All ON/All OFF).
  - LED indicators for contactor status.
  - Automation button for scheduling contactor operations.

---
📞 For more information, refer to the system's documentation or contact the project maintainer.
