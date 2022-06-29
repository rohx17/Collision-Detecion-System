#include <SoftwareSerial.h>
int Rx_pin = 5;
int Tx_pin = 6;
SoftwareSerial SerialGPS(Rx_pin, Tx_pin);
SoftwareSerial GSM(10, 11);
#define BUZ 7
#define LED 3
int button = 2; 
double roll;
#include <math.h>
const int x_out = A1; /* connect x_out of module to A1 of UNO board */
const int y_out = A2; /* connect y_out of module to A2 of UNO board */
const int z_out = A3; /* connect z_out of module to A3 of UNO board */

void setup() {
  pinMode(button, INPUT); //Set the sensor pin as INPUT
  Serial.begin(9600);//Set baud rate for serial communication
  SerialGPS.begin(9600);
  GSM.begin(9600);   // Setting the baud rate of GSM Module
  delay(100);
  pinMode(BUZ, OUTPUT);
}

void loop(){
  if (digitalRead(button) == LOW){
    Serial.println("Collision");//print collision
    delay(300);
    SendMessage();
    //buzled();
    delay(1000);
    exit(0);}
    axc();
   if (roll<100){
    Serial.println("Car Flipped");//print collision
    delay(300);
    SendMessage();
    //buzled();
    delay(1000);
    exit(0);
   }
  
}


void buzled(){
  while (true) {
    delay(1000);
    digitalWrite(LED, HIGH);
    digitalWrite(BUZ, HIGH);
    delay(1000);
    digitalWrite(BUZ, LOW);
    digitalWrite(LED, LOW);}
    }

void SendMessage(){
  GSM.println("ATD8825413527");
  GSM.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  GSM.println("AT+CMGS=\"8825413527\"\r");
  GSM.println("!!!! There has been as car accident at");// The SMS text you want to send
  gps();
  GSM.println("----------Details of the passenger----------");
  GSM.println("Name: ");
  GSM.println("Blood Group: ");
  GSM.println("Address: ");
  GSM.println("Family phone Number: ");
  GSM.println("Medical Conditions: ");
  GSM.println("--------Vehicle Details-------");
  GSM.println("Car license Number:");
  GSM.println("Car color:");
  axc();  
  GSM.println("!!!!Kindly inform the authorized person to take further actions to save a life!!!! ");
  GSM.println((char)26);// ASCII code of CTRL+Z
}

void axc(){
  int y_adc_value, z_adc_value; 
  double y_g_value, z_g_value;
  int i=0;
  //for(i=0;i<5;i++){
  delay(1000);
  y_adc_value = analogRead(y_out); /* Digital value of voltage on y_out pin */
  z_adc_value = analogRead(z_out); /* Digital value of voltage on z_out pin */ 
  delay(1000);
  y_g_value = ( ( ( (double)(y_adc_value * 5)/1024) - 1.65 ) / 0.330 ); /* Acceleration in y-direction in g units */ 
  z_g_value = ( ( ( (double)(z_adc_value * 5)/1024) - 1.80 ) / 0.330 ); /* Acceleration in z-direction in g units */ 
  roll = ( ( (atan2(y_g_value,z_g_value) * 180) / 3.14 ) + 180 ); /* Formula for roll */
  //Serial.println(roll);
  //}

  if (roll > 100){
    GSM.println("The Car isnt flipped");
    Serial.println("The Car isnt flipped");}
  else if(roll < 100) {
    GSM.println("EMERGENCY: The Car is flipped, call the medical authority and a rescue team immediately to save the person from the car");
    Serial.println("EMERGENCY: The Car is flipped, call the medical authority and a rescue team immediately to save the person from the car");}
  delay(300);
}
void gps(){
  GSM.println("Accident Location: 10.9027N, 76.9006E");
  while(false){
  while (SerialGPS.available() > 0)
  Serial.write(SerialGPS.read());
  }
  
}
