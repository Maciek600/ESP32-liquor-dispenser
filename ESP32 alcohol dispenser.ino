#include <LiquidCrystal.h>
#include "HX711.h"

// Piny do LCD
LiquidCrystal lcd(16, 17, 21, 19, 18, 5);

// Piny HC-SR04
#define TRIG_PIN 25
#define ECHO_PIN 26

// Piny przycisków
#define BUTTON_30ML 3
#define BUTTON_60ML 1
#define BUTTON_70ML 22
#define BUTTON_80ML 23

// Pompka
#define PUMP_PIN 13

// Belka tensometryczna
#define DT 2
#define SCK 4
HX711 scale;
float tara_waga;

void setup() {
    lcd.begin(16, 2);
    lcd.print("Poloz szklanke");

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, LOW);

    pinMode(BUTTON_30ML, INPUT_PULLUP);
    pinMode(BUTTON_60ML, INPUT_PULLUP);
    pinMode(BUTTON_70ML, INPUT_PULLUP);
    pinMode(BUTTON_80ML, INPUT_PULLUP);

    scale.begin(DT, SCK);
    scale.set_scale(401130.50 / 186.0);
    scale.tare();
}

float measureDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2;
}

void pourLiquid(float targetWeight) {
    digitalWrite(PUMP_PIN, HIGH);
    while (abs(scale.get_units() - tara_waga) < targetWeight) {
        delay(100);
    }
    digitalWrite(PUMP_PIN, LOW);
    lcd.clear();
    lcd.print("Gotowe :)");
    delay(2000);
}

void loop() {
    float distance = measureDistance();
    if (distance > 5) {
        lcd.clear();
        lcd.print("Poloz szklanke");
    } else {
        delay(2000); // Odczekaj 2 sekundy przed tarowaniem
        scale.tare();
        tara_waga = scale.get_units();

        lcd.clear();
        lcd.print("Wybierz ml");
        lcd.setCursor(0, 1);
        lcd.print("30 60 70 80");

        while (true) {
            if (digitalRead(BUTTON_30ML) == LOW) {
                pourLiquid(30);
                break;
            } else if (digitalRead(BUTTON_60ML) == LOW) {
                pourLiquid(60);
                break;
            } else if (digitalRead(BUTTON_70ML) == LOW) {
                pourLiquid(70);
                break;
            } else if (digitalRead(BUTTON_80ML) == LOW) {
                pourLiquid(80);
                break;
            }
            delay(100);
        }
    }
    delay(500);
}
