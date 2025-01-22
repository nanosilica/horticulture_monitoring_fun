# horticulture_monitoring_fun

Plant Monitoring System - Arduino Project

This project monitors soil moisture, temperature, and light levels using sensors connected to an Arduino Uno. It also includes a motor (sprinkler) and a buzzer for feedback based on sensor readings. The system can send data to ThingSpeak via Wi-Fi using the ESP8266 module.

![image](https://github.com/user-attachments/assets/a62bc010-df94-472b-af4a-c7cce8dbcf48)

Apparatus List

    Arduino Uno: The microcontroller board used to control the system.
    Soil Moisture Sensor: Measures the moisture level of the soil to determine when to water the plant.
    TMP36 Temperature Sensor: Measures the ambient temperature.
    Photoresistor (Light Sensor): Measures the ambient light intensity.
    Liquid Crystal Display (LCD): Displays real-time sensor data and status messages.
    ESP8266 Wi-Fi Module: Enables the system to send data to ThingSpeak via Wi-Fi.
    Motor (Sprinkler): Activated when soil moisture is low.
    Buzzer: Provides feedback (for example, when light is low).

Wiring Instructions
1. Arduino to LCD (16x2):

    RS: Pin 5
    EN: Pin 4
    D4: Pin 3
    D5: Pin 2
    D6: Pin A4
    D7: Pin A5

2. Soil Moisture Sensor:

    VCC: 5V (Arduino)
    GND: GND (Arduino)
    Analog Output (A0): Pin A3 (Arduino)

3. TMP36 Temperature Sensor:

    VCC: 5V (Arduino)
    GND: GND (Arduino)
    Analog Output (A0): Pin A2 (Arduino)

4. Photoresistor (Light Sensor):

    One side: 5V (Arduino)
    Other side: Connect to:
        Pin A1 (Arduino) (for analog input)
        A 10kΩ resistor connected between this point and GND to form a voltage divider.

5. Motor (Sprinkler):

    Positive: Pin 12 (Arduino)
    Negative: GND (Arduino)

6. Buzzer:

    Positive: Pin 10 (Arduino)
    Negative: GND (Arduino)

7. ESP8266 Wi-Fi Module:

    VCC: 3.3V (Arduino)
    GND: GND (Arduino)
    TX (ESP8266): Pin 2 (Arduino)
    RX (ESP8266): Pin 3 (Arduino)

Code Explanation
Functions:

    setupESP8266(): Initializes the Wi-Fi connection and establishes communication with the ThingSpeak API.
    readSensors(): Reads the soil moisture, temperature, and light levels, then displays this data on the LCD.
    sendDataToThingSpeak(): Sends sensor data to ThingSpeak using the ESP8266 Wi-Fi module (optional).

Actions:

    If the soil moisture is low, the sprinkler motor is turned on, and the LCD displays "Watering...".
    If the light level is low, the LCD shows "Low light!".
    The temperature is displayed on the LCD in Celsius.

Step-by-Step Instructions

    Wire the Components:
        Follow the wiring instructions above to connect all components to the Arduino.

    Set up the ESP8266:
        Connect the ESP8266 to the Arduino (using the correct pins for TX/RX and 3.3V supply).

    Install the Arduino IDE:
        If you haven't already, install the Arduino IDE from https://www.arduino.cc/en/software.

    Upload the Code:
        Open the Arduino IDE, paste the provided code into a new sketch.
        Select the correct board (Arduino Uno) and port under Tools.
        Upload the code to the Arduino.

    Test the System:
        Once the code is uploaded, the system should display the sensor values on the LCD.
        The motor will activate if the soil moisture is low, and the buzzer will provide feedback if needed.

Notes:

    Ensure your photoresistor is wired in a voltage divider configuration to measure light levels correctly.
    The TMP36 sensor provides an analog output, which is read by the Arduino and converted to a temperature value.
    The soil moisture sensor provides an analog output that the Arduino reads to determine if the soil is dry or wet.
    If you're using ThingSpeak to send data, ensure that the API key and URL are set correctly in the code.

