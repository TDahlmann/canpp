# CAN++ User Manual

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

## CAN hardware configuration

### Activate hardware

Select connected hardware from list
~~~ 
Settings => Hardware Select 
~~~

### Change hardware configuration
Go to
~~~ 
Settings => Channel Configuration
~~~
Select a channel in the list to see its parameters. Pushing **Apply** will set the parameters. The checkbox determines whether the channel is active or not.

![Channel Configuration](img/channel_config.jpg)

#### Dialog data

widget | function | notes |
------ | ------|---------|
Channel Number | logical channel number | This number is used in all other dialogs. So this number maps to the selected physical channel in the list above.
Type | CAN type | CAN classic or CANFD type
Import from DB | import channel settings from DBC |
Adjust bit timings | enable bit timing config | bit timing parameters widget show up
Calculate | calculate bit timing values | values are calculated based on Sample Point value
Reset | undo changes in bit timings

## Options
Go to
~~~ 
Settings => Options
~~~
![Options](img/options.jpg)

### Diagnostic options

widget | function | notes |
------ | ------|---------|
Set Can Ids manually | assign Diagnostic CAN Ids | allows setting  CAN Ids for RX/TX. Otherwise CAN Ids are taken from ODX
CAN Channel | channel for diagnostics
Log Diags to file | log diagnostic data to folder **log**

### CAN sniffer options

widget | function | notes |
------ | ------|---------|
Show RAW values | show signal raw | beside physical signal value show raw bus signal value too
Show Error Frames | error frame enable | if enabled trace performance may go down
Log CAN to file | log CAN data to folder **log**
Start Trigger | Start CAN Id trigger | CAN Id which triggers trace/simulation start, which is chosen in CAN DB tree in left main window by right mouse click
Stop Trigger | Stop CAN Id trigger | CAN Id which triggers trace/simulation stop, which is chosen in CAN DB tree in left main window by right mouse click
