# ESP32_WiFi_Demo
## 1 Software Installation
This section is taken from another project that I took part in, [here](https://github.com/emrp/emrp2018_Moers_Trashbins)

### 1.1 Arduino IDE
Download and install the Arduino IDE from: https://www.arduino.cc/en/main/software

### 1.2 Heltec Libraries
Heltec support two sets of libraries to simplify the use of the integrated OLED, LoRa and other modules of the WIFI LoRa 32 (V2) board.

#### 1.1.1 Heltec Board Support Package
[Note: this section is adapted from Heltec's instructions which can be accessed [here](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/master/InstallGuide/windows.md)]

Download the repository [WiFi_Kit_series](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series) as zip and extract it to `/Documents/Arduino/hardware/heltec`. Create the folders manually if they have not been created.

Navigate to `/Documents/Arduino/hardware/heltec/esp32/tools`, double-click on `get.exe` and wait for the script to finish.

Make sure the following folders are generated:

![tools folder](https://github.com/emrp/emrp2018_Moers_Trashbins/blob/master/pictures/sensor_node_ttn/tools_folder.jpg)

#### 1.1.2 Heltec Extended Libraries
Download the repository [Heltec_ESP32](https://github.com/HelTecAutomation/Heltec_ESP32) as zip and extract it to /Documents/Arduino/.

Plug in the heltec board and wait for the drivers to install (if needed).

Open the Arduino IDE, click on `Tools->Boards` and choose `Wifi_LoRa_32_V2`.

Click on `Sketch->Include Library->Add .Zip Libaries...`.

In the pop-up window, navigate to `/Documents/Arduino/` and choose `Heltec_ESP32-master.zip`.

#### 1.1.3 Running an OLED Example
Make sure the chosen board is `Wifi_LoRa_32_V2`.

![choose_board](https://github.com/emrp/emrp2018_Moers_Trashbins/blob/master/pictures/sensor_node_ttn/choose_board.jpg)

Click on \
`File->Examples->(Example from Custom Libraries)->Heltec ESP32 Dev-Boards->OLED->SSD1306SimpleDemo`.

![choose_example](https://github.com/emrp/emrp2018_Moers_Trashbins/blob/master/pictures/sensor_node_ttn/choose_example.jpg)

Click the `Upload` button to upload the program to the board. Check the OLED display to see if it works.

Open `Tools->Serial Monitor` to see the printed messages. Make sure the baudrate is set to `115200`. To reset the program, simply upload the program again or press the hardware reset button on the board.

Other examples are available within `Heltec ESP32 Dev-Boards`.

### 1.3 Sensor Libraries
#### 1.3.1 Installing the VL53L0X Adafruit Library
Click on `Tools -> Manage Libraries...` and search for `VL53L0X`. Choose and install the `Adafruit_VL53L0X` library by Adafruit.

#### 1.3.2 Installing the DHT Adafruit Library
Click on `Tools -> Manage Libraries...` and search for `DHT`. Choose and install the `DHT sensor` library by Adafruit.
