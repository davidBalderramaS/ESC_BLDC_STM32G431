# 🚀 **Custom ESC For BLDC Motor (STM32G431RB)**

## 📌 Overview
This project is a custom-built Electronic Speed Controller (ESC) for brushless DC (BLDC) motors, developed from scratch using the STM32G431RB microcontroller. The goal is to design and implement a high-performance ESC as part of a larger project: a fully custom drone system, including remote control and real-time telemetry.

## 🛠 Features
- BLDC motor control with **STM32G431RB**
- Custom 6-layer PCB design
- PWM generation for MOSFET drivers
- Comparator + ADC integration for motor control
- Potentiometer-based speed control for testing
- **Future**: 4-in-1 ESC + wireless remote telemetry

## ⚡ Hardware
- **Microcontroller**: STM32G431RB
- **Motor Drivers**: ir2110
- **Motors**: BLDC motors (tested with EMAX ECO II Series 2306 Brushless Motor)  
- **Power Supply**: 4S LiPo (14.8V), Lab Bench PS  
- **Board**: Custom 6-layer PCB  
  - Layer stackup: Signal / GND / 3.3V / 14.8V / GND / Signal  

<img width="720" height="558" alt="image" src="https://github.com/user-attachments/assets/639f9eed-4c13-4b8c-a5ed-e8cb37e80ad8" />

<img width="720" height="558" alt="image" src="https://github.com/user-attachments/assets/5eb03023-227d-4d3c-97fa-47defdb01d46" />



## 💻 Firmware/Software
- Baremetal programming written in **C** for STM32 (using STM32CubeIDE toolchain)  
- Peripherals used:
  - **Timers** → PWM generation for motor drivers
  - **Comparators** → For closed-loop feedback (emf zero-crossing detection)
  - **ADC** → Controlling motor speed  
  - **GPIO & interrupts** → control logic  
- Current capability: single ESC + motor test with potentiometer input  
- Roadmap: expand to 4-in-1 ESC and integrate wireless telemetry

## ▶️ Getting Started
1. Clone repo:
   ```bash
   git clone https://github.com/davidBalderramaS/ESC_BLDC_STM32G431.git
2. Open in STM32CubeIDE (or your IDE of choice).
3. Compile and flash firmware to STM32G431RB (Nucleo board or custom PCB).
4. If not using custom PCB, contruct circuit on breadboard 
5. Connect BLDC motor + LiPo battery / power supply.
6. Use a potentiometer to control input for speed control.





