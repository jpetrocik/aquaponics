ESP8266WebServer server(80); 


void webServerSetup() {
  Serial.println("Starting web server on port 80");
   server.on("/", handleStatus); 
   server.on("/pump/on", handleStartPump); 
   server.on("/pump/off", handleStopPump); 
   server.on("/restart", HTTP_POST, handleRestart); 
   server.on("/factoryreset", HTTP_POST, handleFactoryReset); 
   
   server.begin();
}

void webServerLoop() {
  server.handleClient();
}

void handleStartPump() {
  startPump();
  handleStatus();
}

void handleStopPump() {
  stopPump();
  handleStatus();
}

void handleStatus() {
  char jsonStatusMsg[140];
  
  sprintf (jsonStatusMsg, "{\"pump\":%s,\"timer\":\"%i\",\"next\":\"%i\"}", pumpStatus ? "\"ON\"" : "\"OFF\"", remainingTime>0?remainingTime:0, nextStart);
  server.send(200, "application/json",  (char *)jsonStatusMsg);
}

void handleRestart() {
  server.send(200, "application/json",  "{\"message\":\"Restarting\"}");
  delay(1000);
  ESP.restart();
}

void handleFactoryReset() {
  factoryReset();
  delay(1000);
  server.send(200, "application/json",  "{\"message\":\"Factory Reset\"}");
}



