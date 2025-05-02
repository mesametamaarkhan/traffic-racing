# 🚗 Traffic Racing Game (SFML + C++)

A top-down 2D traffic racing game built with C++ and the SFML (Simple and Fast Multimedia Library). Dodge incoming vehicles, switch lanes, and race as far as possible without crashing. Designed for Linux and fully tested on Kali.

---

## 🚀 Features

- Continuous lane-based racing gameplay
- Randomized traffic generation
- Keyboard input for lane switching
- 2D sprite-based rendering with SFML
- Cross-platform (Linux-friendly)

---

## 🛠️ Installation

### Step 1: Install SFML

Make sure the SFML development package is installed:

```bash
git clone https://github.com/mesametamaarkhan/traffic-racing.git
cd traffic-racing
sudo apt update
sudo apt install libsfml-dev
g++ main.cpp -o trafficracer -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./trafficracer
