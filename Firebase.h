#ifndef Firebase_h
#define Firebase_h
#include <HTTPClient.h>

class Firebase{
    public:
        Firebase();
        void ConnectWifi();
        void SendData(String Name,String Data,String jsonName);
};

Firebase::Firebase(){
    
    // Connect to Wi-Fi

    Serial.println("Connected to Wi-Fi");
    ConnectWifi();


}

void Firebase::ConnectWifi(){
    WiFi.begin("Tsinghua-Secure", "*sun103yue");
    int i=0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to Wi-Fi...");
        i++;
        if(i>10){
            Serial.println("Wifi Connection failed");
            break;
        }
    }
}

void Firebase::SendData(String Name,String Data,String jsonName){
  if (WiFi.status() != WL_CONNECTED){
    // Send POST request to Firebase
    Serial.println("Wifi not connected, reconnect...");
    ConnectWifi();
  }
  else{
    HTTPClient http;
    http.begin("https://techin515-74d59-default-rtdb.firebaseio.com/"+jsonName+".json");
    http.addHeader("Content-Type", "application/json");
    String postData = "{\"name\":\"" +Name+"\", \"value\":\""+Data+"\"}";
    int httpResponseCode = http.PUT(postData);
    if (httpResponseCode > 0) {
        ;// Serial.printf("HTTP POST request successful, response code: %d\n", httpResponseCode);
    } else {
        Serial.printf("HTTP POST request failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    http.end();
  }
}


#endif