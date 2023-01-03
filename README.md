 CAN++

## Overview
CAN++ is a free Windows program for receiving, transmitting and analyzing (*.asc, *.blf) CAN bus messages (CAN Classic and **CAN FD**) for using with [SuperCAN](https://github.com/jgressmann/supercan) devices or without CAN hardware (virtual bus). After import of CAN data base files (*.**dbc**, *.**arxml**) CAN signals are shown in symbolic form. Signals can be presented as graphics (wave forms) too.

Furthermore:
- **CAN simulation** is possible by programming CAN behaviour in C++. 
- **CAN traces** can be generated, imported and replayed (*.asc format, *.blf can be imported).
- **Diagnostics** can be performed (PDX import, fault memory, measurement and identification data)

There are several devices which are supported by SuperCAN firmware and can be used with CAN++. For example:
- Open Source Hardware: [USB_CAN-FD](https://github.com/RudolphRiedel/USB_CAN-FD)
- Off the shelf: [Adafruit Feather M4 CAN Express](https://www.adafruit.com/product/4759) (simple [drag & drop](#tips) of firmware)

CAN++ can be just started (no installation).   
The user manual is located in sub folder `doc/user_manual` (Markdown and HTML version, work in progress). 


![Main screen](doc/screens/main2.jpg)
![Main screen](doc/screens/graph.jpg)

## Traces
CAN traces can be generated, imported and replayed (*.asc format). Import and replay is possible with BLF files too (*.blf).

## CAN transmit

- cyclic, once, with time offset
- define signals as raw or physical values
- or define signals with wave configurator

![Main screen](doc/screens/tx.jpg)
![Main screen](doc/screens/wave.jpg)

## CAN simulation in C++

- one .cpp file per CAN node (see Example ECU_main.cpp)
- react on CAN-Messages (::onMessage()) or signals
- send CAN messages
- Timers (can be used for cyclic sending of CAN messages)
- print text
- integrated IDE and integrated C++ Compiler (DMC)
- react on key presses
- react on commands received from remote client program (See chapter "Remote control")

![Main screen](doc/screens/canpr_context_with_build.jpg)

Instead of the CAN++ IDE you can use your own of course. After first compiling of code CAN++ generates C++ classes for all CAN messages and signals (see canl/canl_data.cpp) so another IDE will give context input support too.

## Remote control

CAN++ can be remote controlled. To do so start CAN++ with option `-server` on command line:
~~~
can++.exe -server
~~~
Currently following actions can be taken:  

- Start CAN bus  
- Stop CAN bus  
- Send a generic command to C++ simulation, which can be used to trigger self-defined actions, examples may be:  

    - call a test function  
    - set a global variable to switch behaviour  
    - send a CAN message provided by command string  
    - etc.  

Please see client example source code (Python, C# and C++) in folder examples/remote_control.

## CAN statistics

![Main screen](doc/screens/statistics.jpg)

## CAN diagnostics
- faultmemory
- measurement data
- identification
- import PDX files

![Main screen](doc/screens/faultmem.jpg)
![Main screen](doc/screens/measurements.jpg)

## Installation

CAN++ can be used without installation. It should not be placed in system folders like "C:\Programs". Path should contain "A-Za-z0-9_" only. Otherwise integrated Compiler will not work. By calling "INSTALL.bat" a shortcut is created on desktop.

## Tips
### How to flash SuperCAN firmware on Adafruit Feather M4 CAN Express (on Windows)
- download SuperCAN firmware file supercan-firmware.tar.xz from https://github.com/jgressmann/supercan/releases/tag/latest-master
- Unpack supercan-firmware.tar.xz (7-Zip could be used), needed file is supercan.uf2
- plug in device
- push the button on the device twice
- a drive "FTHRBOOT" will show up in file explorer
- drop the file supercan.uf2 on this drive
- after 10 seconds replug the device
