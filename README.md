#  Grab-It Robotic Arm Project

**Authors:**  
- Vladimir Kambovski – 205014  
- Ognen Ivanov – 211002  

**Project Link:** [Grab-It by Joy-IT](https://joy-it.net/en/products/Robot02)

---

##  Project Overview

The Grab-It project aims to create a fully functional robotic arm system using the **Grab-It Robot Arm Kit** by Joy-IT. The system is controlled using a **PS4 DualShock 4 controller**, with logic split between an **Arduino UNO** and a **Python interface** running on a laptop. Servo motors are managed via a **PCA9685 driver**, powered by a dedicated **DC-DC buck converter**.

---

##  Objectives

1. Develop a user-friendly robotic arm system  
2. Ensure smooth and precise servo movements  
3. Integrate PS4 controller for intuitive control  
4. Provide stable power delivery to prevent system failure  

---

##  Requirements

### Hardware

- Grab-It Robot Arm Kit (6 servo motors)  
- Arduino UNO  
- PCA9685 Servo Driver  
- 12V 6A Power Supply  
- 300W 20A DC-DC Step Down Buck Converter  
- DualShock 4 PS4 Controller  
- Laptop with USB and DS4 Windows  

### Software

- Arduino IDE  
- Python with `pygame` library  
- DS4 Windows (PS4 Controller Drivers)

---

### System Architecture

- **Input:** DualShock 4 Controller (USB-connected)  
- **Processing:** Python script captures inputs and sends via serial  
- **Actuation:** Arduino reads serial data and controls servos via PWM  
- **Power:** 12V input regulated down to 5.5V for PCA9685 and servos  

---

### Implementation

###  Hardware Setup

1. **Servo Calibration:** All servos set to midpoint (90°)  
2. **Robot Assembly:** Assembled using official manual  
3. **Power Wiring:**
   - 12V power input to buck converter  
   - Output: 5.5V @ 13A (6 servos × 2A + margin)  
   - Buck output → PCA9685  
   - PCA9685 → Servos (V+ and GND)  
   - Common ground with Arduino  
4. **Signal Wiring:**
   - PWM outputs from PCA9685 to Arduino digital PWM pins  
   - Serial COM link: Arduino ↔ Laptop  
5. **Controller:**
   - PS4 controller connected to laptop via USB  

###  Software

- **Python Script:**
  - Uses `pygame` to read controller inputs  
  - Sends serial commands to Arduino  
- **Arduino Code:**
  - Reads serial data  
  - Controls each servo with mapped values  
  - Implements smooth incremental motion  

---

### Testing & Debugging

-  Verified PS4 inputs via DS4Windows and Python  
-  Checked serial communication accuracy  
-  Tuned servo motion for smooth and jitter-free behavior  
-  Ensured each input led to correct servo response  

---

### Final Production & Testing

##  System Integration

- Finalized wiring and physical layout  
- Verified clean power distribution  
- Ensured stable controller ↔ Python ↔ Arduino communication  

##  Final Testing

- Full system test from input to servo motion  
- Measured and optimized response time  
- Implemented safety margins for current/temperature  

---

## Deployment & Documentation

- Created user guide for setting up and using the system  
- Demonstrated usage to potential users for feedback  

---

##  Future Enhancements

- Increase servo voltage from 5.5V to 7.4V for better torque  
- Replace Arduino with a faster MCU for parallel servo movement  
- Add Bluetooth support for wireless control  
- Upgrade to servos with 360° rotation where needed  
- Add machine vision for automation and object tracking  

---
### Wiring and Circuit Diagram
![SCHEMEARDUINO](https://github.com/user-attachments/assets/75cfe6b0-6e5f-4991-b18d-b3e66acadd8d)

### ROBOTARM Showcase
![image](https://github.com/user-attachments/assets/1ad44b90-c487-4374-863a-58ce5b3a1403)
![image](https://github.com/user-attachments/assets/b4886341-f6e6-43c2-99e0-8f0833734c27)
![image](https://github.com/user-attachments/assets/2e7dba44-6d9a-4750-b896-cdd4f8e47266)


