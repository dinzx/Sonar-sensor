#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the sensor.
#define MAX_DISTANCE 70 // Maximum distance we want to ping for (in centimeters).

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
}

void loop() {
  delay(1000); // Wait 1000ms between pings (about 1 ping/sec).
  unsigned int distance = sonar.ping_cm(); // Send ping, get distance in centimeters.
  
  // Check if the distance is within the range.
  if (distance > 0) {
    Serial.print("Fill level: ");
    Serial.print(MAX_DISTANCE - distance); // The distance in centimeters.
    Serial.println("cm");
    // Determine fill status based on distance
    if (distance <= 20) {  // Assuming sensor is just under the lid.
      Serial.println("Warning: Bin is Full!");
    } else if (distance > 45) {
      Serial.println("Bin is almost Empty");
    } else if (distance <= 45 && distance > 20) {
      // Roughly halfway full
      if (distance >= 30 && distance < 45) {
        Serial.println("Bin is roughly Halfway Full");
      }
    }
  } else {
    Serial.println("Out of range");
  }
}
