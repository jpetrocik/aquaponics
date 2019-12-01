# Aquaponic's Firmware For Sonoff Dual R2

Firmware to control an aquaponics system using Sonoff Dual R2.  The Sonoff Dual R2 has two relays to control the pumps, the firmware acts as a timer to control the rely and provides a RestApi to control the pumps from OpenHab or HomeAssistant. The Sonoff curcuit board is removed from the orginal Sonoff enclosure and put into a weather proof enclosure ordered from Amazon.

### Sonoff Dual R2

![Dual R2](https://github.com/jpetrocik/aquaponics/raw/master/sonoff_dual_r2.png)

## Flashing Firmware

The Sonoff uses a ESP8266 Wifi chip, so this section discusses flashing the ESP8266 chip on the Sonoff Dual R2. For more details google: "Arduino ESP8266"

### Setup the Arduino IDE

* Download Arduino IDE.

* Open you IDE and click on "File -> Preferences".

* In  "Aditional Boards Manager URLs" add this line and click on "OK": "http://arduino.esp8266.com/stable/package_esp8266com_index.json"

* Go to "Tools -> Board -> Boards Manager", type "ESP8266" and install it.

* Go again to "Tools -> Board" and select "Generic ESP8266 Module".

### Flashing

* Place a jumper on the pins labeled BUTTON 0 and GND, without this the Sonoff does not enter flash mode.

* Connect the TTL programmer to programming header pins on the Sonoff.  You must cross over the RX->TX and TX-RX.  So from the promgrammer connect TX -> RX on the Sonoff and RX to TX on the Sonoff.  Connect 3.3v and GND.

* Plug in the programmer your computer.

* Using Adruino IDE, open "firmware.ino" from this project.

* From the menu: Tool -> Boards -> "Generic ESP8266 Module"

* After selecting the board change the following defaults from the Tool menu:

Flash Mode: DOUT (compatiable)

FLash Size: 1M (no spiff)

Port: <select your programmer from the list>
  

* Programming the Sonoff by clickign to "Upload" icon


### Sonoff Dual R2 Programming Headers 

![Dual R2 Programming Headers](https://github.com/jpetrocik/aquaponics/raw/master/sonoff_dual_r2_pins.png)

### Enclosure

![Enclosure](https://github.com/jpetrocik/aquaponics/raw/master/enclosure.jpg)

### Programmer

![Programmer](https://github.com/jpetrocik/aquaponics/raw/master/programmer.jpg)



