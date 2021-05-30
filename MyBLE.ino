#include <ArduinoBLE.h>           // Bluetooth Library
#include <Arduino_HTS221.h>       // Pressure Sensor Library
#include <Arduino_LPS22HB.h>      // Temperature Sensor Library
#include <Arduino_LSM9DS1.h>      // Magnetometer Sensor Library

// Initalizing global variables for sensor data to pass onto BLE
String p, t, m;

// BLE Service Name
BLEService customService("180C");

// BLE Characteristics
// Syntax: BLE<DATATYPE>Characteristic <NAME>(<UUID>, <PROPERTIES>, <DATA LENGTH>)
BLEStringCharacteristic ble_pressure("2A56", BLERead | BLENotify, 13);
BLEStringCharacteristic ble_temperature("2A57", BLERead | BLENotify, 13);
BLEStringCharacteristic ble_magnetic("2A58", BLERead | BLENotify, 20);

// Function prototype
void readValues();

void setup()
{
    // Initalizing all the sensors
    HTS.begin();
    BARO.begin();
    IMU.begin();
    Serial.begin(9600);
    while (!Serial);
    if (!BLE.begin())
    {
        Serial.println("BLE failed to Initiate");
        delay(500);
        while (1);
    }

    // Setting BLE Name
    BLE.setLocalName("Arduino Environment Sensor");
    
    // Setting BLE Service Advertisment
    BLE.setAdvertisedService(customService);
    
    // Adding characteristics to BLE Service Advertisment
    customService.addCharacteristic(ble_pressure);
    customService.addCharacteristic(ble_temperature);
    customService.addCharacteristic(ble_magnetic);

    // Adding the service to the BLE stack
    BLE.addService(customService);

    // Start advertising
    BLE.advertise();
    Serial.println("Bluetooth device is now active, waiting for connections...");
}

void loop()
{
    // Variable to check if cetral device is connected
    BLEDevice central = BLE.central();
    if (central)
    {
        Serial.print("Connected to central: ");
        Serial.println(central.address());
        while (central.connected())
        {
            delay(200);
            
            // Read values from sensors
            readValues();

            // Writing sensor values to the characteristic
            ble_pressure.writeValue(p);
            ble_temperature.writeValue(t);
            ble_magnetic.writeValue(m);

            // Displaying the sensor values on the Serial Monitor
            Serial.println("Reading Sensors");
            Serial.println(p);
            Serial.println(t);
            Serial.println(m);
            Serial.println("\n");
            delay(1000);
        }
    }
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
}

void readValues()
{
    // Reading raw sensor values from three sensors
    float x, y, z;
    float pressure = BARO.readPressure();
    float temperature = HTS.readTemperature();
    if (IMU.magneticFieldAvailable()) {
      IMU.readMagneticField(x, y, z);

    // Saving sensor values into a user presentable way with units
    p = String(pressure) + " kPa";
    t = String(temperature) + " C";
    m = "X:" + String(x) + ", Y:" + String(y);
    }
}
