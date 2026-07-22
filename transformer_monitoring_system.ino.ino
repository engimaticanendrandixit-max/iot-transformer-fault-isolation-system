#include <OneWire.h>
#include <DallasTemperature.h>

// -------------------- PIN DEFINITIONS --------------------

// DS18B20 Sensors
#define OIL_TEMP_PIN      4
#define WINDING_TEMP_PIN  5

// ACS712 Current Sensor
#define CURRENT_PIN       34

// HC-SR04
#define TRIG_PIN          18
#define ECHO_PIN          19

// Relay, Buzzer, LEDs
#define RELAY_PIN         23
#define BUZZER_PIN        25
#define GREEN_LED         26
#define RED_LED           27

// -------------------- THRESHOLDS --------------------

const float MAX_TEMP = 85.0;      // °C
const float MAX_CURRENT = 5.0;    // Ampere (change as needed)

const float TANK_HEIGHT = 20.0;   // cm
const float MIN_OIL_LEVEL = 30.0; // percent

// -------------------- DS18B20 SETUP --------------------

OneWire oilWire(OIL_TEMP_PIN);
DallasTemperature oilSensor(&oilWire);

OneWire windingWire(WINDING_TEMP_PIN);
DallasTemperature windingSensor(&windingWire);

// --------------------------------------------------------

void setup()
{
    Serial.begin(115200);

    oilSensor.begin();
    windingSensor.begin();

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    // Normal State
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    Serial.println("Transformer Monitoring System Started...");
}

// -------------------- OIL LEVEL --------------------

float getOilLevel()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);

    float distance = duration * 0.034 / 2.0;

    float levelPercent =
        ((TANK_HEIGHT - distance) / TANK_HEIGHT) * 100.0;

    levelPercent = constrain(levelPercent, 0, 100);

    return levelPercent;
}

// -------------------- CURRENT --------------------

float getCurrent()
{
    long total = 0;

    for (int i = 0; i < 500; i++)
    {
        int value = analogRead(CURRENT_PIN);

        total += value;

        delay(1);
    }

    float avg = total / 500.0;

    float voltage = (avg * 3.3) / 4095.0;

    // ACS712 20A sensitivity ≈ 100 mV/A
    float current = (voltage - 1.65) / 0.1;

    return abs(current);
}

// -------------------- MAIN LOOP --------------------

void loop()
{
    oilSensor.requestTemperatures();
    windingSensor.requestTemperatures();

    float oilTemp = oilSensor.getTempCByIndex(0);
    float windingTemp = windingSensor.getTempCByIndex(0);

    float current = getCurrent();

    float oilLevel = getOilLevel();

    bool fault = false;

    // Fault conditions

    if (oilTemp > MAX_TEMP)
        fault = true;

    if (windingTemp > MAX_TEMP)
        fault = true;

    if (current > MAX_CURRENT)
        fault = true;

    if (oilLevel < MIN_OIL_LEVEL)
        fault = true;

    // Protection logic

    if (fault)
    {
        digitalWrite(RELAY_PIN, LOW);

        digitalWrite(BUZZER_PIN, HIGH);

        digitalWrite(RED_LED, HIGH);

        digitalWrite(GREEN_LED, LOW);
    }
    else
    {
        digitalWrite(RELAY_PIN, HIGH);

        digitalWrite(BUZZER_PIN, LOW);

        digitalWrite(RED_LED, LOW);

        digitalWrite(GREEN_LED, HIGH);
    }

    // Serial Monitor

    Serial.println("================================");

    Serial.print("Oil Temperature: ");
    Serial.print(oilTemp);
    Serial.println(" C");

    Serial.print("Winding Temperature: ");
    Serial.print(windingTemp);
    Serial.println(" C");

    Serial.print("Current: ");
    Serial.print(current);
    Serial.println(" A");

    Serial.print("Oil Level: ");
    Serial.print(oilLevel);
    Serial.println(" %");

    Serial.println(
        fault ? "FAULT DETECTED - TRIPPED"
              : "SYSTEM NORMAL"
    );

    delay(2000);
}