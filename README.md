# esp-idf-vcp2ble
VCP(Virtual COM Port) to Bluetooth bridge for ESP-IDF.

ESP-IDF supports VCP hosts.   
Representative VCP devices include Arduino Uno and Arduino Mega.   
ESP-IDF can communicate with VCP devices using the USB port.   
I based it on [this](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/usb/host/cdc/cdc_acm_vcp).   

# BLE host stack
ESP-IDF can use either the ESP-Bluedroid host stack or the ESP-NimBLE host stack.   
The differences between the two are detailed [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/ble/overview.html).   
This project uses the ESP-NimBLE host stack.   

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   


# Hardtware requirements
This project only works with ESP32S3.   
The ESP32S3 has both USB and BLE capabilities.   
The ESP32S2 also has USB capabilities, but does not have BLE capabilities.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-vcp2ble
cd esp-idf-vcp2ble
idf.py set-target esp32s3
idf.py menuconfig
idf.py flash
```

# Configuration   
![Image](https://github.com/user-attachments/assets/e5286aeb-81ed-4289-8d1b-497f16f3ad88)
![Image](https://github.com/user-attachments/assets/62f95676-20f2-48d4-a8f2-a60688fa99c8)

# Write this sketch on Arduino Uno.   
You can use any AtMega microcontroller that has a USB port.   

```
unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  while (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    Serial.println(command);
  }

  if(lastMillis + 1000 <= millis()){
    Serial.print("Hello World ");
    Serial.println(millis());
    lastMillis += 1000;
  }

  delay(1);
}
```

# Wireing   
Arduino Uno connects via USB connector.   
The USB port on the ESP32S3 development board does not function as a USB-HOST.   

```
+---------+  +-------------+  +-----------+
|ESP BOARD|==|USB CONNECTOR|==|Arduino Uno|
+---------+  +-------------+  +-----------+
```

```
ESP BOARD          USB CONNECTOR (type A)
                         +--+
5V        -------------> | || VCC
[GPIO19]  -------------> | || D-
[GPIO20]  -------------> | || D+
GND       -------------> | || GND
                         +--+
```

![Image](https://github.com/user-attachments/assets/7bf405af-b1ec-4c7c-87d1-8bbe176e807b)


# Android Application   
I used [this](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal) app.   

# iOS Application   
[This](https://apps.apple.com/jp/app/bluetooth-v2-1-spp-setup/id6449416841) might work, but I don't have iOS so I don't know.   


# How to use
- pair with ESP_NIMBLE_SERVER   

- Launch the app and select device  
Menu->Devices->Bluetooth LE   

- Long press the device and select the Edit menu   
![Image](https://github.com/user-attachments/assets/2d36b757-585a-4310-919c-a57f136c7f20)

- Select Custom and specify UUID   
The UUIDs are different for ESP-Bluedroid and ESP-NimBLE.   
![Image](https://github.com/user-attachments/assets/9b0f23bc-86f4-4631-81e6-1df8d876f41b)

- Connect to device   
You can communicate to UNO using android.   
![Image](https://github.com/user-attachments/assets/e84fa3b1-a0ee-4af3-a64c-695a5b383857)


# Concurrent connection
Unlike ESP-Bluedroid host stack, ESP-NimBLE host stack allows concurrent connections.   
The maximum number of simultaneous connections is specified here.   
![Image](https://github.com/user-attachments/assets/9d1e1182-ed41-4b9e-bc55-bb3c75dd4745)   
![Image](https://github.com/user-attachments/assets/4d84823a-69c4-48bf-9671-64644f048ccd)   

