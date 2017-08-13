//reads 3 accelerometers and repeats
//**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

//Accelerometer Addr Select Pins
int pin_accel0 =2;
int pin_accel1 =3;
int pin_accel2 =4;

void setup() { 
 // initialize digital pin LED_BUILTIN as an output.
  pinMode(pin_accel0, OUTPUT);  // accel 0 select
  pinMode(pin_accel1, OUTPUT);  // accel 1 select
  pinMode(pin_accel2, OUTPUT);  // accel 2 select
  digitalWrite(pin_accel0, HIGH); // HIGH=De-Select
  digitalWrite(pin_accel1, HIGH); // HIGH=De-Select
  digitalWrite(pin_accel2, HIGH); // HIGH=De-Select

  // MMA8452 setup
  Serial.begin(9600);
  Serial.println("Adafruit MMA8451 test!");
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  mma.setRange(MMA8451_RANGE_2_G);
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");
}

void loop() {
  //read accel0
  digitalWrite(pin_accel0,LOW);   // turn ON accel0 addr select
  delay(1);                       // wait for a millisecond
  readAccel(0);
  digitalWrite(pin_accel0,HIGH);  // turn OFF accel0 addr select
  
  //read accel1
  digitalWrite(pin_accel1,LOW);   // turn ON accel0 addr select
  delay(1);                       // wait for a millisecond
  readAccel(1);
  digitalWrite(pin_accel1,HIGH);  // turn OFF accel0 addr select
  
  //read accel2
  digitalWrite(pin_accel2,LOW);   // turn ON accel0 addr select
  delay(1);                       // wait for a millisecond
  readAccel(2);
  digitalWrite(pin_accel2,HIGH);  // turn OFF accel0 addr select
}
  
void readAccel(int N){
  Serial.println("******************************************************");  
  Serial.print("            Accelerometer # "); 
  Serial.println(N); 
  Serial.println("******************************************************");
 
  // Read the 'raw' data in 14-bit counts
  mma.read();
  Serial.print("X:\t"); Serial.print(mma.x); 
  Serial.print("\tY:\t"); Serial.print(mma.y); 
  Serial.print("\tZ:\t"); Serial.print(mma.z); 
  Serial.println();

  /* Get a new sensor event */ 
  sensors_event_t event; 
  mma.getEvent(&event);

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
  Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
  Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
  Serial.println("m/s^2 ");
  
  /* Get the orientation of the sensor */
  uint8_t o = mma.getOrientation();
  
  switch (o) {
    case MMA8451_PL_PUF: 
      Serial.println("Portrait Up Front");
      break;
    case MMA8451_PL_PUB: 
      Serial.println("Portrait Up Back");
      break;    
    case MMA8451_PL_PDF: 
      Serial.println("Portrait Down Front");
      break;
    case MMA8451_PL_PDB: 
      Serial.println("Portrait Down Back");
      break;
    case MMA8451_PL_LRF: 
      Serial.println("Landscape Right Front");
      break;
    case MMA8451_PL_LRB: 
      Serial.println("Landscape Right Back");
      break;
    case MMA8451_PL_LLF: 
      Serial.println("Landscape Left Front");
      break;
    case MMA8451_PL_LLB: 
      Serial.println("Landscape Left Back");
      break;
    }
  Serial.println();
  Serial.println();
  delay(1000);
} 

  

