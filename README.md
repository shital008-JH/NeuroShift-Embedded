### 🧠 NeuroShift

Focus • Adapt • Survive

---
## 📌 Project Overview

NeuroShift is a dual-mode cognitive reaction game designed to test and improve reflexes, focus, adaptability, and decision-making under time pressure.

The project consists of:

🌐 A browser-based web game

🔌 An ESP32 hardware simulation using Wokwi

Both versions follow the same core idea: react correctly to changing rules as fast as possible.

---
## 🚀 Key Features

🌐 Web Game Features

- Dynamic visual stimuli (shapes & colors)

- Progressive difficulty levels

- 90-second timed gameplay

- Combo and life (heart) system

- Reaction time measurement

- Final Neuro Profile score generation

🔌 Hardware Simulation Features

ESP32-based reaction game

- Dual OLED displays

- Command Display

- HUD (Lives & Time)

- RGB LED visual feedback

- Buzzer sound feedback

- Physical push-button interaction

Life-based and time-based game logic

---
## 🌐 Web Game Explanation

🎮 Gameplay Logic:

Random shapes (● ■ ▲) with random colors

A rule is displayed telling when to take action

Correct actions:

+ Increase score

+ Increase combo

+ Wrong actions:

+ Reduce lives

+ Reset combo

Game ends when:

+ Time reaches zero (win)

+ All lives are lost (game over)

---
## 🧠 Neuro Profile Metrics

⚡ Reflex → Average reaction speed

🎯 Focus → Remaining lives

🔁 Adaptability → Difficulty level reached

🧘 Stability → Highest combo achieved

---
## 🔌 Hardware Simulation Explanation
🧩 Components Used:

1. ESP32 Dev Module

2. 2 × SSD1306 OLED Displays (I2C)

3. RGB LED (Common Anode)

4. Push Button

5. Buzzer

6. Current-limiting resistors

---
## 🎮 Hardware Gameplay Logic

OLED shows a command:

1.PRESS BUTTON

2-DO NOT PRESS

3.PRESS FAST

4.WAIT

5.RGB LED indicates command type

Button press is evaluated:

-Correct → Success feedback

-Wrong → Life lost

Game ends when:

-Time expires → YOU WIN

-Lives reach zero → GAME OVER

---
## 📷 Circuit Diagram

Refer to diagram.json for the complete ESP32 wiring and component layout used in Wokwi.
<img width="235" height="218" alt="image" src="https://github.com/user-attachments/assets/ad9b4325-c2aa-4d3f-b930-3595aabfc519" />

---
## 🎯 Purpose of the Project

Demonstrates human–computer interaction

Combines web development + embedded systems

Useful for:

1).Cognitive games

2).Reaction testing

3).Brain–machine interface concepts

---
## 👤 Author

Shital Singh
ESP32 • Embedded Systems • Web Development • Security Enthusiast
---
