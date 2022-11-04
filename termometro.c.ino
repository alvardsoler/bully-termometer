#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHTPIN_IN 7
#define DHTPIN_OUT 6
#define DHTTYPE DHT21 // DHT21 (AM2301)

/**
Alimentación de entrada a VIN del arduino y de 5V a los dispositivos
D6 cable amarillo detector OUT
D7 cable amarillo detector IN

A4 al SDA del LCD
A5 añ SCL del LCD
*/


byte house[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B11011,
  B11011,
  B00000
};

byte tree[] = {
  B00000,
  B00100,
  B01110,
  B00100,
  B01110,
  B11111,
  B00100,
  B00100
};

byte grades[] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B01110,
  B00000,
  B00000,
  B00000
};

LiquidCrystal_I2C lcd(0x27,16,2);  
DHT dht_in(DHTPIN_IN, DHTTYPE);
DHT dht_out(DHTPIN_OUT, DHTTYPE);

void setup() {
    // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();

  lcd.createChar(0, house);
  lcd.createChar(1, tree);
  lcd.createChar(2, grades);
  
  //Paso 4
  Serial.begin(9600);
  lcd.print("Holis!");
  dht_in.begin();
  dht_out.begin();
}

void loop() {  
    delay(2000);
    
    float h_in = dht_in.readHumidity();
    float t_in = dht_in.readTemperature();
    float h_out = dht_out.readHumidity();
    float t_out = dht_out.readTemperature();

    //Paso 8
    if (isnan(h_in) || isnan(t_in)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }

     // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
    lcd.setCursor(0, 0);
    // Escribimos el número de segundos trascurridos
    
    lcd.setCursor(0, 0);
    lcd.write(0);

    lcd.print(" ");
    lcd.print(t_in,1);
    lcd.write(2);
    lcd.print("  ");
    lcd.print(h_in);
    lcd.print("%");


    lcd.setCursor(0, 1);
    // Escribimos el número de segundos trascurridos
    lcd.write(1);
    lcd.print(" ");
    lcd.print(t_out,1);
    lcd.write(2);    
    lcd.print("  ");
    lcd.print(h_out);
    lcd.print("%");
}