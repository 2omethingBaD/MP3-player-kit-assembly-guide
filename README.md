# MP3 Player Kit Assembly Guide

This project is designed to play a single MP3 file with volume control, replay control, and pause/play functionality. Follow this guide to get the best experience from your MP3 player.

---

## 📋 Table of Contents
- [Features](#features)
- [Assembly](#assembly)
  - [The Microcontroller](#the-microcontroller)
  - [The Capacitor, LED, and 5V Linear Regulator](#the-capacitor-led-and-5v-linear-regulator)
  - [The Speaker](#the-speaker)
  - [The MP3 File Reader and Micro SD Card](#the-mp3-file-reader-and-micro-sd-card)
  - [The Battery](#the-battery)
- [Other Notes](#other-notes)

---

## ⚙️ Features

- **Automatic Play & Pause** – The MP3 player starts playing automatically but can be paused when a magnet is brought close to the reed sensor.  
- **Power Indicator** – A yellow LED indicates when the system is powered on.  
- **Volume Control** – Four adjustable volume levels to suit your preference.  
- **Audio Reset** – Restart the audio with a long press (2 seconds) or by bringing a magnet close to the reed sensor once the song has ended.  
- **System Reset** – Reset the system for troubleshooting using the second button.

---

## 🧰 Assembly

> You can complete these steps in any order.

<details>
<summary><strong>The Microcontroller</strong></summary>

The **ATtiny85** used in this project includes an 8-pin DIP socket, allowing the completely open-source code to be modified and re-flashed without resoldering (this socket is optional).  

When soldering, the 8-pin DIP does not need to be oriented in a specific direction, but when placing or soldering the ATtiny85 into the PCB or DIP socket, the small circle on the ATtiny85 must align with the circle marking on the PCB to avoid damaging the microcontroller or other components.

![ATtiny85 installation step 1](https://github.com/2omethingBaD/MP3-player-kit-assembly-guide/blob/main/GITimg/20251022_152217.jpg?raw=true)
![ATtiny85 installation step 2](https://github.com/2omethingBaD/MP3-player-kit-assembly-guide/blob/main/GITimg/20251022_152250.jpg?raw=true)
![ATtiny85 installation step 3](https://github.com/2omethingBaD/MP3-player-kit-assembly-guide/blob/main/GITimg/20251022_152402.jpg?raw=true)
</details>

---

<details>
<summary><strong>The Capacitor, LED, and 5V Linear Regulator</strong></summary>

The polarity of the **1000 µF capacitor** and **LED** can be identified by their legs:
- The **longer leg** is positive (+)
- The **shorter leg** is negative (−)

Insert the longer leg into the hole marked with a **+** on the PCB.  
You can replace the LED with any other 3 mm color, but note that the **150 Ω resistor** may need adjustment depending on the LED chosen.  

The **5 V linear regulator** should be placed with its back facing the ATtiny85.

![Capacitor and LED placement](https://github.com/2omethingBaD/MP3-player-kit-assembly-guide/blob/main/GITimg/20251022_152604.jpg?raw=true)
![Regulator placement](https://github.com/2omethingBaD/MP3-player-kit-assembly-guide/blob/main/GITimg/20251022_152923.jpg?raw=true)
</details>

---

<details>
<summary><strong>The Speaker</strong></summary>

The speaker requires a **male JST connector** to be soldered first.  
Once soldered, the speaker can be plugged in.

![Speaker connection step 1](https://github.com/2omethingBaD/MP3-player-kit-assembly-guide/blob/main/GITimg/20251022_152702.jpg?raw=true)
![Speaker connection step 2](https://github.com/2omethingBaD/MP3-player-kit-assembly-guide/blob/main/GITimg/20251022_152725.jpg?raw=true)
</details>

---

<details>
<summary><strong>The MP3 File Reader and Micro SD Card</strong></summary>

The **DFPlayer Mini** should be soldered with the chip reader facing outward for easy access to the micro SD card and to prevent damage.  

This project includes a **4 GB micro SD card**, which can be swapped for a larger or smaller one.  
MP3 files can be uploaded via a micro SD card reader (not included).

![DFPlayer Mini installation 1](https://github.com/2omethingBaD/MP3-player-kit-assembly-guide/blob/main/GITimg/20251022_153011.jpg?raw=true)
![DFPlayer Mini installation 2](https://github.com/2omethingBaD/MP3-player-kit-assembly-guide/blob/main/GITimg/20251022_153058.jpg?raw=true)
</details>

---

<details>
<summary><strong>The Battery</strong></summary>

The included **9 V battery** can be replaced with any other 9 V battery of your choice.  

- The **red wire** on the battery buckle connector is positive and should be soldered through the PCB hole marked **B+**  
- The **black wire** is negative and should be soldered just below it  

![Battery connection](https://github.com/2omethingBaD/MP3-player-kit-assembly-guide/blob/main/GITimg/20251022_153355.jpg?raw=true)
</details>

---

## 📝 Other Notes

- The **reed sensor**, **1 k Ω resistor**, and **150 Ω resistor** are not polarized and can be soldered into place in either direction.  
- The included battery has a **charge indicator light** — it glows **blue while charging** and turns **green when fully charged**.  
- The included **2-pin buttons** can be swapped or placed in the **RES** and **IN** sections on the PCB:  
  - **RES** → System reset (for troubleshooting)  
  - **IN** → Volume control and song reset  
- The **full ATtiny85 source code** is included in this repository for user customization.

---

💡 *Liked this project? check out my youtube! [SomethingBAD Labs!](https://www.youtube.com/@somethingBAD_Labs) — “BAD ideas, genius built.”*
