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

## 2 Hardware Connections
### 2.1 WIFI LoRa 32 (V2) Board Pinouts
The originial pinout diagram provided by Heltec can be accessed [here](https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/blob/master/PinoutDiagram/WIFI_LoRa_32_V2.pdf). Below is a snapshot of the diagram.
![Board pinouts](https://github.com/emrp/emrp2018_Moers_Trashbins/blob/master/pictures/sensor_node_ttn/WIFI_LoRA_32_V2_Pinouts.jpg)The pins used by the OLED module are fixed and are taken care of by the Heltec library.\
The pins used by the LoRa module are fixed and must be explicitly defined in the code to properly interface with the LMIC library (see [section 5.1.1](#511-overview)).

### 2.2 VL53L0X Connections
The VL53L0X sensor uses I2C to communicates with the microcontroller, this case being the ESP32 microcontroller on the Heltec LoRa Board. The I2C bus consists of two lines: SCL for clock and SDA for data. More information on the working mechanism of the I2C bus can be found [here](https://robot-electronics.co.uk/i2c-tutorial).

The VL53L0X breakout board provides the following pinouts:

 -  VDD: positive supply voltage, to be connected to a power supply (2.6V to 3.5V)
 - GND: ground
 - SCL: clock line for I2C
 - SDA: data line for I2C
 - GPIO1: Interrupt output
 - XSHUT: shutdown pin, active low. Driving this pin LOW will put the sensor to standby mode.
 
The wiring between the VL53L0X breakout board and the WIFI LoRa 32 (V2) board should be as in the figure below.

<img src="https://github.com/emrp/emrp2018_Moers_Trashbins/blob/master/pictures/sensor_node_ttn/vl530x_esp32_wiring.jpg" height=70% width=70%>

Note that the GPIO1 pin should be left unconnected as it is not used within the scope of this application.
