# esp-idf-vcp2ble
VCP(Virtual COM Port) to Bluetooth bridge for ESP-IDF.

![Image](https://github.com/user-attachments/assets/61209e18-d390-4eec-875d-9fc82cad105a)

ESP-IDF supports VCP hosts.   
Representative VCP devices include Arduino Uno and Arduino Mega.   
ESP-IDF can communicate with VCP devices using the USB port.   
I based it on [this](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/usb/host/cdc/cdc_acm_vcp).   

This project uses the following components.   
Other UART-USB converter chips are not supported.   
- https://components.espressif.com/components/espressif/usb_host_ch34x_vcp   
- https://components.espressif.com/components/espressif/usb_host_cp210x_vcp   
- https://components.espressif.com/components/espressif/usb_host_ftdi_vcp   


# BLE host stack
ESP-IDF can use either the ESP-Bluedroid host stack or the ESP-NimBLE host stack.   
The differences between the two are detailed [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/ble/overview.html).   
This project uses the ESP-NimBLE host stack.   

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   


# Hardtware requirements

## ESP32-S3
This project only works with ESP32S3.   
The ESP32S3 has both USB and BLE capabilities.   
The ESP32S2 also has USB capabilities, but does not have BLE capabilities.   

## USB Type-A Femail connector
USB connectors are available from AliExpress or eBay.   
I used it by incorporating it into a Universal PCB.   
![USBConnector](https://github.com/user-attachments/assets/8d7d8f0a-d289-44b8-ae90-c693a1099ca0)

We can buy this breakout on Ebay or AliExpress.   
![usb-conector-11](https://github.com/user-attachments/assets/848998d4-fb0c-4b4f-97ae-0b3ae8b8996a)
![usb-conector-12](https://github.com/user-attachments/assets/6fc34dcf-0b13-4233-8c71-07234e8c6d06)

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

VCP communication stop bits. 0: 1 stopbit, 1: 1.5 stopbits, 2: 2 stopbits   
VCP communication parity. 0: None, 1: Odd, 2: Even, 3: Mark, 4: Space   
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

The string input from VCP is terminated with CR(0x0d)+LF(0x0a).   
```
I (2342) VCP: 0x3fcba0a8   48 65 6c 6c 6f 20 57 6f  72 6c 64 20 33 30 30 30  |Hello World 3000|
I (2342) VCP: 0x3fcba0b8   0d 0a
```

The string output to VCP must be terminated with LF(0x0a).  
If the string output to the VCP is not terminated with LF(0x0a), the Arduino will complete the input with a timeout.   
The string output to the VCP is echoed back.   
```
I (76092) VCP: 0x3fcb7930   61 62 63 64 65 66 67 0a                           |abcdefg.|
I (76112) VCP: 0x3fcba0a8   61 62 63 64 65 66 67 0d  0a                       |abcdefg..|
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

- pair with ESP_NIMBLE_SERVER   

- Launch the app and select device  
	Menu->Devices->Bluetooth LE   

- Long press the device and select the Edit menu   
	![Image](https://github.com/user-attachments/assets/2d36b757-585a-4310-919c-a57f136c7f20)

- Select Custom and specify UUID   
	![Image](https://github.com/user-attachments/assets/9b0f23bc-86f4-4631-81e6-1df8d876f41b)

- Connect to device   
	You can communicate with UNO via BLE.   
	![Image](https://github.com/user-attachments/assets/e84fa3b1-a0ee-4af3-a64c-695a5b383857)

- Concurrent connection   
	Unlike ESP-Bluedroid host stack, ESP-NimBLE host stack allows concurrent connections.   
	The maximum number of simultaneous connections is specified here.   
	![Image](https://github.com/user-attachments/assets/9d1e1182-ed41-4b9e-bc55-bb3c75dd4745)   
	![Image](https://github.com/user-attachments/assets/4d84823a-69c4-48bf-9671-64644f048ccd)   

# iOS Application   
[This](https://apps.apple.com/jp/app/bluetooth-v2-1-spp-setup/id6449416841) might work, but I don't have iOS so I don't know.   

