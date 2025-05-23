## RoboSniper
## Description
This is a project was made due to the course requirment of making a line follower bot with a <b>special feature</b>.This is a  line-following robot equipped with ultrasonic distance sensor for enemy detection and a servo mounted gun to auto-target and fire. Combines autonomous navigation with active defense.
<br>

## Table of Contents 
1. [Hardware_Materials](#Hardware_Materials)
1. [SETUP](#setup)
2. [Usage](#usage)
3. [Suggestions](#suggestions)
4. [Gallery](#Gallery)

##  [Hardware_Materials](#Hardware_Materials)

Below is a list of components and materials used in the RoboSniper project:

###  Electronics
- **Arduino Uno** – Main microcontroller
- **SG90 Servo Motors** (x3) – For radar sweep, gun aiming, and trigger pull
- **HC-SR04 Ultrasonic Sensor** – For enemy detection
- **L298N Motor Driver Module** – For controlling line-following motors
- **IR Sensors** (x3) – For line detection
- **9V Battery / Power Bank** – For powering the bot
- **Jumper Wires**, **Breadboard** or **Custom PCB**

###  Mechanical / Printed Parts
- **3D Printed Mounts** – For gun, servos, and sensor holders
- **Wheels & Chassis** – DIY or purchased
- **General-purpose fasteners** – Screws, bolts, rubber bands, double-sided tape, etc.

### Materials
- **PLA Filament** – Used for all 3D printed parts
- **Rubber Bands** – Used as safe, low-cost projectiles for the gun mechanism

##  [SETUP](#setup)

1. **Open the Arduino code:**
   - Open either `gun_code.ino` or `ultrasonic_test.ino` in the **Arduino IDE** depending on what you want to test.
   - Make sure your board is set to the correct model (e.g., Arduino Uno).

2. **Install required libraries:**
   - This project uses the built-in **Servo** library, which is usually included with the Arduino IDE.
   - No additional libraries are required unless you're adding custom features.

3. **Upload the code to your Arduino board:**
   - Open the **Serial Monitor** (`Ctrl + Shift + M`) to see real-time distance readings and debug info.

4. **3D Print and assemble the components:**
   - Go to the `3d_designs/` folder for STL and Fusion 360 files.
   - Prepare and print the parts.
   - Mount your servo motors and gun as per your design.
   - Connect the electronics according to the code.

5. **Upload the final code in UNO**
- Upload the `gun_code.ino` and `Linefollowingcode.ino` (We uploaded them in 2 seperate arduinos)

## [Usage](#Usage)

This bot can be used for:

- **Surveillance** in small indoor environments.
- **Autonomous enemy detection** using ultrasonic sensors.
- **Demonstrating Arduino-based servo control and robotics.**

**To run the bot**:

1. Place the robot on a black line track.
2. Upload `gun_code.ino` via Arduino IDE.
3. Power the bot using USB or a battery pack.
4. Monitor distance readings and gun activity via the Serial Monitor. 
 
 ## [Suggestions](#suggestions) 

 Here are some potential improvements and advanced features you can add:

- **Use an ESP32 board** instead of Arduino UNO to take advantage of dual-core processing:
  - Assign **Core 0** for line-following logic.
  - Assign **Core 1** for ultrasonic enemy detection and gun control.
  
- **Add a Bluetooth trigger** to manually fire the gun or override the auto-fire mechanism:
  - Send a `"KILL"` command from a phone or Bluetooth app.
  - ESP32 can use the `BluetoothSerial` library for easy integration.

- **Pause the bot's movement when an enemy is detected**:
  - Once the ultrasonic sensor identifies a threat, halt all line-following logic.
  - Resume only after the enemy is neutralized or cleared from range.

These upgrades can enhance both performance and control, while demonstrating multitasking and wireless interaction with embedded systems.

## [Gallery](#gallery)

### RoboSniper in Action

**Side View**
![Image](https://github.com/user-attachments/assets/de601dcd-72ba-4125-81e0-845ba07b8073)

**Front View**
![Image](https://github.com/user-attachments/assets/1a9e22a5-df06-4ff4-a202-3298271f2a32)

**Angled View**
![Image](https://github.com/user-attachments/assets/3af157b2-aa5f-4287-837f-6bc9fd619225)


