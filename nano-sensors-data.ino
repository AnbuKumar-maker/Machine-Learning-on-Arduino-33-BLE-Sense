#include <Arduino_LSM9DS1.h> //IMU library
#include <Arduino_HTS221.h> //Temperature and Humidity library
#include <Arduino_APDS9960.h> //library for colour, proximity and gesture recognition sensors
#include <Arduino_LPS22HB.h> // for pressure 


// error in sensor initialization function
void setup(){
  Serial.begin(9600); //Serial monitor display 

  if (!IMU.begin()) //Initialize IMU sensor 
  { Serial.println("Failed to initialize IMU!"); while (1);}

  if (!BARO.begin()) //Initialize Pressure sensor 
  { Serial.println("Failed to initialize Pressure Sensor!"); while (1);}

  if (!HTS.begin()) //Initialize Temperature and Humidity sensor 
  { Serial.println("Failed to initialize Temperature and Humidity Sensor!"); while (1);}

  if (!APDS.begin()) //Initialize Colour, Proximity and Gesture sensor 
  { Serial.println("Failed to initialize Colour, Proximity and Gesture Sensor!"); while (1);}
 }

//declaration and initialization
float accel_x, accel_y, accel_z;
float gyro_x, gyro_y, gyro_z;
float mag_x, mag_y, mag_z;
float Pressure;
float Temperature, Humidity;
int Proximity;

//Read data from sensors
void loop()
{
  //Accelerometer 
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accel_x, accel_y, accel_z);
    Serial.print("Accelerometer = ");Serial.print(accel_x); Serial.print(", ");Serial.print(accel_y);Serial.print(", ");Serial.println(accel_z);
  }
delay (200);

  //Gyroscope  
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
    Serial.print("Gyroscope = ");Serial.print(gyro_x); Serial.print(", ");Serial.print(gyro_y);Serial.print(", ");Serial.println(gyro_z);
  }
delay (200);

  //Magnetometer
  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(mag_x, mag_y, mag_z);
    Serial.print("Magnetometer = ");Serial.print(mag_x); Serial.print(", ");Serial.print(mag_y);Serial.print(", ");Serial.println(mag_z);
  }
delay (200);

  //Pressure 
  Pressure = BARO.readPressure();
  Serial.print("Pressure = ");Serial.println(Pressure);
  delay (200);

  //Temperature
  Temperature = HTS.readTemperature();
  Serial.print("Temperature = ");Serial.println(Temperature);
  delay (200);

  //Humidity
  Humidity = HTS.readHumidity();
  Serial.print("Humidity = ");Serial.println(Humidity);
  delay (200);

  //Proximity
  if (APDS.proximityAvailable()) {
    Proximity = APDS.readProximity();
    Serial.print("Proximity = ");Serial.println(Proximity); 
    }
  delay (200);

  Serial.println("_____________________________________________________"); 
  delay(1000);
}
