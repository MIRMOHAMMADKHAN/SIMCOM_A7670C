#include <SoftwareSerial.h>

SoftwareSerial gsm(9, 10); // RX, TX pins for GSM module

void setup() {
  Serial.begin(115200);   // Serial monitor
  gsm.begin(115200);      // GSM module
}

void loop() {
  // Connect to GPRS
  gsm.println("AT+CGATT=1");
  delay(1000);
  
  // Enable GPRS
  gsm.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);

  // Start task and set APN
  gsm.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");
  delay(2000);
  
  // Get local IP address
  gsm.println("AT+SAPBR=1,1");
  delay(2000);

  gsm.println("AT+SAPBR=2,1");
  delay(2000);
  
  // Initialize HTTP service
  gsm.println("AT+HTTPINIT");
  delay(2000);
 
  // Set CID parameter
  gsm.println("AT+HTTPPARA=\"CID\",1");
  delay(2000);

   // Set the URL
  gsm.println("AT+HTTPPARA=\"URL\",\"http://google.com/\"");
  delay(2000);

  // Execute HTTP GET request
  gsm.println("AT+HTTPACTION=0");
  delay(2000);

  // Read HTTP response
  gsm.println("AT+HTTPREAD");
  delay(2000);

  // Terminate HTTP service
  gsm.println("AT+HTTPTERM");
  delay(2000);
}
