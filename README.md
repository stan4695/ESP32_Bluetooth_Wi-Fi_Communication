# ESP32_Bluetooth_Wi-Fi_Communication

## Introduction

This repository contains an Arduino project developed for a university assignment. The project utilizes an ESP32 module to retrieve data from an API provided by the teacher via Wi-Fi. The data retrieved from the API refer to some South Park episodes. The ESP32 then transmits this data to a mobile application on my phone via Bluetooth.

## Requirements
- ✅ Arduino IDE
- ✅ ESP32 Development Board
- ✅ Mobile phone with Bluetooth capability

## Setup Instructions
1. Clone or download this repository to your local machine.
2. Open the _Arduino IDE_.
3. Install the necessary libraries for _ESP32_ development if you haven't already.
4. Connect your _ESP32_ development board to your computer.
5. Open the `esp32_bluetooth_wi_fi_communication.ino` file in the Arduino IDE.
6. Update the _Wi-Fi credentials_ in the code to match your network settings.
7. Upload the code to your _ESP32_ board.
8. Install the companion [mobile application](http://proiectia.bogdanflorea.ro/app) on your phone.
9. Power on the _ESP32_ board and ensure it's connected to your _Wi-Fi network_.
10. Launch the mobile application and enable _Bluetooth_.
11. The _ESP32_ should now start retrieving South Park episode data from the [provided API](http://proiectia.bogdanflorea.ro/api-routes/12) and transmit it to the mobile application via Bluetooth.

## Additional Notes
### Documentation
Additional information regarding the technologies that I used and the implementation of the app can be found [here](https://github.com/stan4695/ESP32_Bluetooth_Wi-Fi_Communication/files/14278943/Proiect.IA.pdf).

### Demo
[Here](https://youtube.com/shorts/0N3MIIEZQ2g) you can find a video demonstration of the application.
