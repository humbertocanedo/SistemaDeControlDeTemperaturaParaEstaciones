#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 4          // Pin D2 en el ESP8266 (GPIO 4)
#define DHTTYPE DHT11     // Tipo de sensor
#define LED_PIN 12        // Pin D6 en el ESP8266 (GPIO 12)
#define TEMP_THRESHOLD 20 // Temperatura a la que se enciende el LED

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  delay(3000);  // Espera 3 segundos entre lecturas

  float humedad = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // Verifica si hay error de lectura
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Error al leer el sensor DHT11");
    return;
  }

  // Muestra la humedad y temperatura en el Serial Monitor
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  // Control del LED basado en la temperatura
  if (temperatura >= TEMP_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);   // Enciende el LED
    Serial.println("LED Encendido");  // Indica que el LED está encendido
  } else {
    digitalWrite(LED_PIN, LOW);    // Apaga el LED
    Serial.println("LED Apagado");  // Indica que el LED está apagado
  }
}
