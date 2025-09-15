# Nantrobot-Initiation-project

Welcome to the Nantrobot Club ! This project serves as an initiation for first-year students at Centrale Nantes to learn the basics of Arduino programming by building a line-following robot.

This repository contains all the resources needed to build and program a functional robot, including:

**CAD files** for the robot
**Documentation** to guide students at different skill levels
**Example code** for individual components (sensors and motors) and the full robot
**Hardware overview** (Arduino, L298N motor driver, IR sensors, DC motors, and 9V battery)
The documentation is designed to be progressive:
-If you already have some Arduino experience, just read the first section, which provides an overview of the robot.
-For those less familiar with Arduino, follow the full documentation on how to wire the robot and write the code.

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="##Introduction">Introduction</a></li>
  </ol>
</details>

### Table of Contents
1. [Introduction](#introduction)
2. [Wiring](#wiring)
   1. [Step-by-Step Wiring Guide](#step-by-step-wiring-guide)
   2. [Full Schematic](#full-schematic)




## Introduction
The robot moves using two **DC motors** attached to wheels and one **castor wheel** for stability. These motors are powered by a **9V battery** and controlled by the Arduino through a **motor driver** (L298N). The motor driver acts as a bridge, allowing the Arduino to control the speed and direction of the motors while providing the necessary power from the battery.

To detect the line, the robot uses two **infrared (IR) sensors**. Each IR sensor has two parts:

- An IR LED that shines infrared light onto the ground.
- An IR receiver that measures how much of that light is reflected back.
The sensors can tell the difference between the black line and the lighter floor:

- **Black absorbs more light**, so less is reflected back.
- **The lighter floor reflects more light**, so the sensor detects a stronger signal.
By constantly reading the sensors, the robot can "see" the line and adjust its movement to stay on track.

Finally to make the robot follow the line we just need to adjust it's trajectory based on which sensor is detecting the line : 
- none of them = moving forward
- one of them = turning in the opposite direction (this can be done with many ways like only activating on motor or slowing just one motor etc...)
- both motor = stop you've succesfully arrived to the finish line !
![Logic](https://github.com/user-attachments/assets/50dcd3e0-1759-4c92-8070-2c8b08c522ae)


Before diving into the details, take a look at the 3D rendering of the robot below. This will give you a clear understanding of how everything fits together.

![assembly detail](https://github.com/user-attachments/assets/7a5bcbd7-bee0-4ddb-a628-69a2c5180cea)


For those who already have experience with Arduino and robotics, this overview should be enough to get you started. If you need more specific details on any component, feel free to look them up on google as that's how we usualy work on project.

## Wiring

### Step-by-Step Wiring Guide
**Power Connections**

- Connect the 9V battery to the L298N motor driver's power terminals to provide power to the motors.
- Connect the GND (ground) pin of the motor driver to the GND pin on the Arduino.


**Motor Connections**

- Attach the two DC motors to the OUT1 and OUT2 terminals on the motor driver (for one motor), and OUT3 and OUT4 for the second motor.
- This allows the motor driver to control the motors' speed and direction.


**Motor Driver to Arduino**

- Use jumper wires to connect the input pins (IN1, IN2, IN3, IN4) on the motor driver to the digital pins on the Arduino (e.g., D2, D3, D4, D5). These connections will allow the Arduino to control the motor driver and, in turn, the motors.
- Use jumper wires to conntect the enable pins A and B on the motor driver to the digital pins on the Arduino (e.g., D9, D10). These connections will allow to control the speed of the motors.


**IR Sensor Connections**

- Connect the VCC pin of each IR sensor to the **3.3V pin** on the Arduino, and the GND pin of each sensor to the Arduino’s GND.
- Attach the A0 pin of each sensor to an available analog pin on the Arduino (e.g., A0 for the left sensor and A1 for the right sensor). This will let the Arduino read the sensor values to detect the line.
(Note: On some sensors, you will also find a D0 pin, which outputs a digital signal that simply indicates whether or not the line is detected. The sensitivity can be adjusted using a built-in potentiometer. However, since not all sensors have this option, we will not be using the D0 pin for this project to keep things consistent and fair for everyone.)

**Final Check**

Make sure all your connections are secure and match the schematic. The motors should be powered through the motor driver, and both the sensors and Arduino should be connected to the correct pins.

### Full Schematic

![schematics](https://github.com/user-attachments/assets/00a609c8-6228-4e16-ad74-812fd70c3853)
