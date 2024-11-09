// src/dht_sensor.cpp
#include "dht_sensor.h"

DHT dht(DHTPIN, DHTTYPE);
unsigned long lastReadTime = 0;

void setupDHT() {
    // First, set pin to output and force a clean state
    pinMode(DHTPIN, OUTPUT);
    digitalWrite(DHTPIN, HIGH);
    delay(250);  // Hold high for 250ms
    
    // Now initialize DHT
    dht.begin();
    
    // Wait for sensor to stabilize
    delay(2000);
    
    Serial.println("\nDHT22 Sensor initialized!");
}

// Rest of the code remains the same
void readAndDisplayDHT() {
    if (millis() - lastReadTime >= READ_INTERVAL) {
        lastReadTime = millis();
        
        float humidity = dht.readHumidity();
        float tempC = dht.readTemperature();
        float tempF = dht.readTemperature(true);
        
        if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
            Serial.println("Failed to read from DHT sensor!");
            
            // Try to reset the sensor
            pinMode(DHTPIN, OUTPUT);
            digitalWrite(DHTPIN, HIGH);
            delay(250);
            dht.begin();
            
            return;
        }

        float heatIndexC = dht.computeHeatIndex(tempC, humidity, false);
        
        Serial.println("\n=== DHT22 Readings ===");
        Serial.printf("Temperature: %.2f°C (%.2f°F)\n", tempC, tempF);
        Serial.printf("Humidity: %.2f%%\n", humidity);
        Serial.printf("Heat Index: %.2f°C\n", heatIndexC);
        Serial.println("====================\n");
    }
}