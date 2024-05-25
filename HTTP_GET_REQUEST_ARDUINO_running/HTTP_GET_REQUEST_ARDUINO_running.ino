#include <SoftwareSerial.h>

SoftwareSerial gsm(9, 10); // RX, TX pins for GSM module

void setup() {
  Serial.begin(115200);   // Serial monitor
  gsm.begin(115200);        // SIM900A default baud rate is usually 9600

  // Initialize GSM module
  sendATCommand("AT", "OK", 2000);
  Serial.println("GSM module initialization command sent.");

  // Connect to GPRS
  sendATCommand("AT+CGATT=1", "OK", 1000);
  Serial.println("GPRS attachment command sent.");

  // Configure bearer profile
  sendATCommand("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"", "OK", 2000);
  Serial.println("Bearer profile CONTYPE command sent.");

  sendATCommand("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"", "OK", 2000); // Replace with your APN
  Serial.println("Bearer profile APN command sent.");

  sendATCommand("AT+SAPBR=1,1", "OK", 2000);
  Serial.println("Bearer profile open command sent.");

  sendATCommand("AT+SAPBR=2,1", "+SAPBR:", 2000);
  Serial.println("Bearer profile status command sent.");

  // Initialize HTTP service
  sendATCommand("AT+HTTPINIT", "OK", 2000);
  Serial.println("HTTP initialization command sent.");

  sendATCommand("AT+HTTPPARA=\"CID\",1", "OK", 2000);
  Serial.println("HTTP CID parameter command sent.");

  sendATCommand("AT+HTTPPARA=\"URL\",\"http://www.google.com\"", "OK", 2000); // Replace with your URL
  Serial.println("HTTP URL parameter command sent.");

  // Execute HTTP GET request
  sendATCommand("AT+HTTPACTION=0", "+HTTPACTION:", 10000); // Wait longer for the response
  Serial.println("HTTP GET request command sent.");

  // Read HTTP response
  sendATCommand("AT+HTTPREAD", "+HTTPREAD:", 10000); // Wait longer for the response
  Serial.println("HTTP read command sent.");

  // Terminate HTTP service
  sendATCommand("AT+HTTPTERM", "OK", 2000);
  Serial.println("HTTP termination command sent.");
}

void loop() {
  // Wait before next attempt
  delay(30000);
}

bool sendATCommand(const char* command, const char* expectedResponse, unsigned long timeout) {
  gsm.println(command);
  unsigned long start = millis();
  String response = "";

  while (millis() - start < timeout) {
    while (gsm.available()) {
      char c = gsm.read();
      response += c;
    }
    if (response.indexOf(expectedResponse) != -1) {
      Serial.print("Command: ");
      Serial.print(command);
      Serial.print(" Response: ");
      Serial.println(response);
      return true;
    }
  }

  Serial.print("Command: ");
  Serial.print(command);
  Serial.println(" - No valid response");
  return false;
}
