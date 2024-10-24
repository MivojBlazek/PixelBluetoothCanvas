# PixelBluetoothCanvas

This application implemented in C++ Qt framework can send data as text or image to another device connected via Bluetooth.

I am free to any suggestions that can make my coding better and cleaner.

## Running application

### Linux

>   Program was tested on Ubuntu 22.04.4 LTS so there can be some issues with different OS.

After downloading and extracting .zip file from GitHub use Makefile to compile and run application.

| Commands            | Description |
| ------------------- | ----------- |
| make / make compile | Uses first target in Makefile that should compile source files |
| make run            | Runs compiled program (GUI support is required) |
| make all            | Compiles and runs program after that |
| make clean          | Removes build from ./build/ directory |

### Windows

>   Program was NOT tested on any Windows OS.

## Controls

Application has GUI with buttons and canvas but can be controled via keyboard too. This program has been mainly created for sending data to ESP32 with TFT display.

At the start program asks for Bluetooth address of device which we want connect to. It has not any validation check, so always double check your address.

There are 3 main parts of window:
* the first is black canvas, where you can draw anything and send it then via Bluetooth,
* the second part is small text input to send text,
* and the third part are just 2 buttons (Left and Right).

Some buttons are binded to keyboard too:

| Key                 | Description |
| :-----------------: | ----------- |
| Enter in text input | Sends current text |
| Left arrow  	      | Sends byte indicating button with left arrow |
| Right arrow  	      | Sends byte indicating button with right arrow |

## Data format

Application can send data via Bluetooth but what is the data format? Data are sent like QByteArray so byte after byte in format:

| Command              | Data format            | Description |
| -------------------- | ---------------------- | ----------- |
| Image (1. chunk)     | 0x00 "image data"      | Added 0x00 byte to the start to determine 1. chunk of image |
| Image (other chunks} | 0x01 "image data"      | Added 0x01 byte to the start to determine that image is not only in 1 chunk |
| Text                 | 0x02 "text from input" | Added 0x02 byte that determines text from input |
| Left button          | 0x03                   | Just sends one byte 0x03 |
| Right button         | 0x04                   | Just sends one byte 0x04 |
