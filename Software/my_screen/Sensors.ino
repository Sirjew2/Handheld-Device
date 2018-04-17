
void initSensor() {
  if (sensorValue2 > thresh) {
    Serial.print("sensor 2: "); Serial.println(sensorValue2);
    Serial.print("sensor 3: "); Serial.println(sensorValue3);

    //Serial.println(count++);
    delay(10);
  }
}
