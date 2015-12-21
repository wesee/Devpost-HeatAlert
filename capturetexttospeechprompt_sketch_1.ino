#include <Temboo.h>

#include <WiFi.h>
#include <WiFiClient.h>

#include <Temboo.h>
#include "TembooAccount.h" // Contains Temboo account information

WiFiClient client;

int numRuns = 1;   // Execution count, so this doesn't run forever
int maxRuns = 1;   // Maximum number of times the Choreo should be executed

int outputPin = 30;

int sensorPin = 6;
int sensorValue = 0;


void setup() {
  Serial.begin(9600);
  
  int wifiStatus = WL_IDLE_STATUS;

  // Determine if the WiFi Shield is present
  Serial.print("\n\nShield:");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("FAIL");

    // If there's no WiFi shield, stop here
    while(true);
  }

  Serial.println("OK");

  // Try to connect to the local WiFi network
  while(wifiStatus != WL_CONNECTED) {
    Serial.print("WiFi:");
    wifiStatus = WiFi.begin(WIFI_SSID, WPA_PASSWORD);

    if (wifiStatus == WL_CONNECTED) {
      Serial.println("OK");
    } else {
      Serial.println("FAIL");
    }
    delay(5000);
  }

  // Initialize pins
  pinMode(outputPin, OUTPUT);
  
  Serial.println("Setup complete.\n");
}

void loop() {
  sensorValue = analogRead(sensorPin);
  float cel = sensorValue * 100.0 / 4095;
  Serial.print("celsius -> "); Serial.println(cel);
  

  if (numRuns <= maxRuns) {
    
    if (cel > 27) {
      Serial.println("Running CaptureTextToSpeechPrompt - Run #" + String(numRuns++));
  
      TembooChoreo CaptureTextToSpeechPromptChoreo(client);
  
      // Invoke the Temboo client
      CaptureTextToSpeechPromptChoreo.begin();
  
      // Set Temboo account credentials
      CaptureTextToSpeechPromptChoreo.setAccountName(TEMBOO_ACCOUNT);
      CaptureTextToSpeechPromptChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
      CaptureTextToSpeechPromptChoreo.setAppKey(TEMBOO_APP_KEY);
  
      // Set Choreo inputs
      String APIKeyValue = "xxxxxxxx";
      CaptureTextToSpeechPromptChoreo.addInput("APIKey", APIKeyValue);
      String ByeTextValue = "goodbye vincent!  thank you.";
      CaptureTextToSpeechPromptChoreo.addInput("ByeText", ByeTextValue);
      
      char TextValue[100];
      sprintf(TextValue, "hello vincent, we detected that the temperature is %f degree celcius.  press 1 to turn on the air-cond or 0 to ignore.", cel);  
      Serial.print("text message -> "); Serial.println(TextValue);
  
  //    String TextValue = "hello vincent, we detected that the temperature is 33 degree celcius.  press 1 to turn on the air-cond or 0 to ignore.";
      CaptureTextToSpeechPromptChoreo.addInput("Text", TextValue);
      
      String ToValue = xxxxxxxxxxx";  // mobile number
      CaptureTextToSpeechPromptChoreo.addInput("To", ToValue);
      String MaxDigitsValue = "1";
      CaptureTextToSpeechPromptChoreo.addInput("MaxDigits", MaxDigitsValue);
      String APISecretValue = "xxxxxxxx";
      CaptureTextToSpeechPromptChoreo.addInput("APISecret", APISecretValue);
  
      // Identify the Choreo to run
      CaptureTextToSpeechPromptChoreo.setChoreo("/Library/Nexmo/Voice/CaptureTextToSpeechPrompt");
  
      // Run the Choreo; when results are available, print them to serial
      unsigned int returnCode = CaptureTextToSpeechPromptChoreo.run();
      
      if (returnCode == 0) {
      
        while(CaptureTextToSpeechPromptChoreo.available()) {
    //      char c = CaptureTextToSpeechPromptChoreo.read();
    //      Serial.print(c);
          
          String name = CaptureTextToSpeechPromptChoreo.readStringUntil('\x1F');
          name.trim();
          
          Serial.println("name -> " + name);
    
          String data = CaptureTextToSpeechPromptChoreo.readStringUntil('\x1E');
          data.trim();
          
          Serial.println("data -> " + data);
    
          if (name == "Digits") {
            if (data.toInt() == 1) {
              digitalWrite(outputPin, HIGH);
            }
          }
        }
      }
      
      CaptureTextToSpeechPromptChoreo.close();
    
    } else {
      Serial.println("Temperature lower than threshold of 27 degree Celsius.");
    }
  } else {
    Serial.println("Skipping to save Temboo calls. Adjust maxCalls as required.");
  }

  Serial.println("\nWaiting...\n");
  delay(5000); // wait 30 seconds between CaptureTextToSpeechPrompt calls
}
