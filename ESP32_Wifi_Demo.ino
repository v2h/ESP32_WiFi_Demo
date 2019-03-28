#include <WiFi.h>
#include <WiFiMulti.h>
#include <DHT.h>
#include <heltec.h>
#include <Adafruit_VL53L0X.h>

#define DHTPIN       23
#define DHTTYPE      DHT22
#define BUILTIN_LED  25
#define L0X_SHUTDOWN GPIO_NUM_13
#define VEXT         21
#define OLED_RST     16

WiFiMulti WiFiMulti;
DHT dht(DHTPIN, DHTTYPE); // temperature-humidity sensor
Adafruit_VL53L0X lox; // time-of-flight infarred sensor

const char* ssid     = "BBB-AP"; // Your SSID (Name of your WiFi)
const char* password = "labgateway!"; //Your Wifi password

const char* host = "api.thingspeak.com";
String api_key = "14LIWNAX4YT5JQ67"; // Your API Key provied by thingspeak

void setup() {
  // put your setup code here, to run once:
  Heltec.begin(true /*Display/I2C Enable*/, false, false, 866E6);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Hello world");
  Heltec.display->display();
  
  Serial.begin(115200);
  L0X_init();
  Connect_to_Wifi();
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  Send_Data();
  delay(20000); // Using delay() is simple, but not good practice
}

void Connect_to_Wifi()
{
  // We start by connecting to a WiFi network
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void Send_Data()
{
  Serial.println("Preparing to send data");

  WiFiClient client; // Use WiFiClient class to create TCP connections

  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else
  {
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();
    int16_t distance = L0X_getDistance();

    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += String(temp);
    data_to_send += "&field2=";
    data_to_send += String(hum);
    data_to_send += "&field3=";
    data_to_send += String(distance);
    data_to_send += "\r\n\r\n";

    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(hum);
    Serial.print("Proximity: ");
    Serial.println(distance);

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);

    delay(1000);
    Serial.println("Data sent\n");
  }

  client.stop();
}

// return distance in cm
int16_t L0X_getDistance(void)
{
  VL53L0X_RangingMeasurementData_t measure;
  int16_t distance = 0;
  for (int i = 0; i < 5; i++)
  {
    delay(100);
    Serial.print("Reading a measurement... ");
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

    if (measure.RangeStatus != 4) {  // phase failures have incorrect data
      distance += measure.RangeMilliMeter / 10;
      Serial.print("Distance (cm): "); Serial.println(measure.RangeMilliMeter / 10);
    } else {
      Serial.println(" out of range ");
      return 0;
    }
  }
  return (distance / 5);
}

void L0X_init(void)
{
  pinMode(L0X_SHUTDOWN, OUTPUT);
  digitalWrite(L0X_SHUTDOWN, HIGH);

  delay(100);
  //Wire.begin(21, 22, 100000);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
}
