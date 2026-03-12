// Incluimos librería
#include <DHT.h>
#include "LiquidCrystal.h"


#define LED_ROJO 10

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11


// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);
 
int rs = 8;
int enable = 9;
int d4 = 4;
int d5 = 5;
int d6 = 6;
int d7 = 7;
int humedad_requerida = 36;

LiquidCrystal lcd(rs, enable, d4, d5, d6, d7);


void setup() {
  // Inicializamos comunicación serie
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.begin(16, 2);
  pinMode(LED_ROJO,OUTPUT);
  // Comenzamos el sensor DHT
  dht.begin();
  byte circulo[] = { B00111, B00101, B00111, B00000, B00000, B00000, B00000, B00000 };  
  lcd.createChar(0, circulo);
}
 
void loop() {
    // Esperamos 5 segundos entre medidas
  delay(1000);
  digitalWrite(LED_ROJO, LOW);
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahreheit
  float f = dht.readTemperature(true);
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  // Calcular el índice de calor en Fahreheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);
 
  lcd.setCursor(0, 0);
  lcd.write("Humedad: ");
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.write("Temp: ");
  lcd.print(t);
  lcd.write(byte(0));
  lcd.write("C ");

  if (h<humedad_requerida) {
     digitalWrite(LED_ROJO, HIGH);
  }


}